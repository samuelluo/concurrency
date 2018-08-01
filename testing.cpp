// g++ -std=c++17 testing.cpp
/*
Playing around with threads.
*/

#include <iostream>    // std::cout, std::endl
#include <thread>      // std::thread

void function(int id) {
    std::cout << "thread " << id << std::endl;
}

int main() {
    // Set up
    int num_threads = 10;
    std::thread thread_array[num_threads];

    // Launch threads
    for (int i = 0; i < num_threads; ++i) {
        // Threads will compete to use output stream
        thread_array[i] = std::thread(function, i);
    }
    std::cout << "main thread" << std::endl;

    // Join threads
    for (int i = 0; i < num_threads; ++i) {
        thread_array[i].join();
    }
}