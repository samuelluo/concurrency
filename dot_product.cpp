// g++ -std=c++17 dot_product.cpp
/*
Testing mutexes & barriers.
*/

#include <chrono>      // std::chrono
#include <iostream>    // std::cout, std::endl
#include <mutex>       // std::mutex, std::lock_guard
#include <ratio>       // std::milli (std::ratio<1, 1000>)
#include <thread>      // std::thread
#include <vector>      // std::vector

void dot_product(const int& num_elements,
                 const std::vector<int>& v1, const std::vector<int>& v2,
                 int& result) {
    for (int i = 0; i < num_elements; i++) {
        result += v1[i] * v2[i];
    }
}

int main() {
    // Set up
    int num_elements = 100000;
    int num_threads = 2;
    int result = 0;
    std::vector<int> v1(num_elements, 2);
    std::vector<int> v2(num_elements, 2);
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
    std::chrono::duration<double, std::milli> elapsed;

    start = std::chrono::steady_clock::now();
    dot_product(num_elements, v1, v2, result);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << result << std::endl;
    std::cout << elapsed.count() << std::endl;
    std::cout << std::endl;

    result = 0;
    std::vector<std::thread> threads;
    start = std::chrono::steady_clock::now();
    // for (int i = 0; i < num_threads; ++i) {
    //     threads.push_back(
    //         std::thread(dot_product, &num_elements, &v1, &v2, &result)
    //     );
    // }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << result << std::endl;
    std::cout << elapsed.count() << std::endl;
    std::cout << std::endl;
}
