// g++ -std=c++17 testing_1.cpp
/*
Testing C++ mutex & thread.
*/

#include <iostream>    // std::cout, std::endl
#include <mutex>       // std::mutex
#include <thread>      // std::thread

// --------------------------------------------------------
void print_1(int n, char c) {
    for (int i = 0; i < n; i++) {
        std::cout << c;
    }
    std::cout << std::endl;
}

std::mutex mtx;
void print_2(int n, char c) {
    mtx.lock();    // If locked, thread will be blocked & go to sleep
    for (int i = 0; i < n; i++) {
        std::cout << c;
    }
    std::cout << std::endl;
    mtx.unlock();

    // This function call is unprotected by the mutex & will compete with another thread
    print_1(n, c);
}

// --------------------------------------------------------
int main () {
    // std::cout << "async" << std::endl;
    // std::thread th1 = std::thread(print_1, 20, '*');
    // std::thread th2 = std::thread(print_1, 20, '$');
    // th1.join();
    // th2.join();    // Join threads before next sections
    // std::cout << std::endl;

    std::cout << "sync" << std::endl;
    std::thread th3 = std::thread(print_2, 20, '*');
    std::thread th4 = std::thread(print_2, 20, '$');
    th3.join();
    th4.join();    // Join threads before next sections
    std::cout << std::endl;

    return 0;
}