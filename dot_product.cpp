// g++ -std=c++17 dot_product.cpp
/*
Testing mutex & lock_guard.
*/

#include <chrono>      // std::chrono::time_point, std::chrono::steady_clock,
                       // std::chrono::seconds
#include <iostream>    // std::cout, std::endl
#include <mutex>       // std::mutex, std::lock_guard
#include <ratio>       // std::milli (std::ratio<1, 1000>)
#include <thread>      // std::thread, std::this_thread::sleep_for
#include <vector>      // std::vector

std::mutex m;

// L and R need to be pass by value; the left-right limits are changing with 
// each call, so passing by reference returns inconsistent summations
void dot_product(const int& num_elements,
                 const std::vector<int>& v1, const std::vector<int>& v2,
                 int& result, int L, int R) {
    // Each thread builds an intermediary result
    int temp = 0;
    for (int i = L; i < R; ++i) {
        temp += v1[i] * v2[i];
    }

    // lock_guard unlocks mutex at end of scope
    // Equivalent to m.lock(), m.unlock()
    std::lock_guard<std::mutex> l(m);
    // std::cout << L << " " << R << " | ";
    // std::cout << result << " + " << temp << std::endl;
    result += temp;
}

int main() {
    // Set up
    int num_elements = 10000000;    // Speed gains start from 10,000,000+
    int num_threads = 4;
    int result = 0;
    std::vector<int> v1(num_elements, 1);
    std::vector<int> v2(num_elements, 1);
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
    std::chrono::duration<double, std::milli> elapsed;

    // Single-thread
    start = std::chrono::steady_clock::now();
    dot_product(num_elements, v1, v2, result, 0, num_elements);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << result << std::endl;
    std::cout << elapsed.count() << std::endl;
    std::cout << std::endl;

    // Multi-thread
    result = 0;
    std::vector<std::thread> threads;
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < num_threads; ++i) {
        int L = (num_elements/num_threads)*i;
        int R = (num_elements/num_threads)*(i+1);
        threads.push_back(
            // TODO: std::ref() vs &?
            std::thread(dot_product,
                        std::ref(num_elements), std::ref(v1), std::ref(v2),
                        std::ref(result), L, R)
        );
    }
    for (auto& t : threads) {    // threads are not copy-able; make sure pass references
        t.join();
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << result << std::endl;
    std::cout << elapsed.count() << std::endl;
    std::cout << std::endl;
}
