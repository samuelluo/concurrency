// g++ -std=c++17 deadlock.cpp

#include <iostream>    // std::cout, std::endl;
#include <mutex>       // std::mutex
#include <thread>      // std::thread

std::mutex m1, m2;

void thread1() {
    m2.lock();
    // m1.lock();    // This does not deadlock
    std::cout << "thread1" << std::endl;
    m1.lock();    // This does deadlock
    m2.unlock();
    m1.unlock();
}

void thread2() {
    m1.lock();
    // m2.lock();    // This does not deadlock
    std::cout << "thread2" << std::endl;
    m2.lock();    // This does deadlock
    m1.unlock();
    m2.unlock();
}

int main() {
    /* - t1 acquires m2
       - t2 acquires m1
       - t1 attempts to acquire m1, sleeps
       - t2 attempts to acquire m2, sleeps
    */
    std::thread t1 (thread1);
    std::thread t2 (thread2);

    t1.join();
    t2.join();

    std::cout << "done" << std::endl;
}