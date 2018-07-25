// g++ -std=c++17 money_transfer.cpp
/*
Design a class Account that allows multiple concurrent clients to deposit or
withdraw money to an account.
Implement a function to transfer money from one account to another.
*/

#include <iostream>    // std::cout, std::endl;
#include <mutex>       // std::mutex
#include <thread>      // std::thread

// --------------------------------------------------------
class Account {
    public:
        int balance;
        std::mutex mutex;

        // Constructor
        Account(int balance) {
            this->balance = balance;
        }

        // Copy constructor
        Account(Account const& account) {
            // mutexes are not copyable
            balance = account.balance;
        }

    void deposit(int amount) {
        mutex.lock();
        balance = balance + amount;
        mutex.unlock();
    }

    void withdraw(int amount) {
        mutex.lock();
        balance = balance - amount;
        mutex.unlock();
    }
};

void transfer(Account* from, Account* to, int amount) {
    from->withdraw(amount);
    to->deposit(amount);
}

// --------------------------------------------------------
int main() {
    Account a (100);
    Account b (0);
    a.deposit(200);
    std::cout << a.balance << ", " << b.balance << std::endl;

    std::thread t1 (transfer, &a, &b, 100);
    std::thread t2 (transfer, &a, &b, 100);
    t1.join();
    t2.join();
    std::cout << a.balance << ", " << b.balance << std::endl;

    std::thread t3 (transfer, &a, &b, 200);
    std::thread t4 (transfer, &b, &a, 200);
    t3.join();
    t4.join();
    std::cout << a.balance << ", " << b.balance << std::endl;
}