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

// Was running into compiler errors when passing references
// Pass by pointer, for now
// TODO: if from.balance >= amount, transfer; change return type to bool
bool transfer(Account* from, Account* to, int amount) {
    bool transferred = false;
    from->withdraw(amount);
    to->deposit(amount);
    return transferred;
}

// --------------------------------------------------------
int main() {
    // Set up
    Account a (100);
    Account b (0);
    std::thread t1;
    std::thread t2;
    std::thread t3, t4;
    a.deposit(200);
    std::cout << a.balance << ", " << b.balance << std::endl;

    // Ending balance: [100, 200]
    t1 = std::thread(transfer, &a, &b, 100);
    t2 = std::thread(transfer, &a, &b, 100);
    t1.join();
    t2.join();
    std::cout << a.balance << ", " << b.balance << std::endl;

    // Ending balance: [100, 200]
    t1 = std::thread(transfer, &a, &b, 100);
    t2 = std::thread(transfer, &b, &a, 100);
    t3 = std::thread(transfer, &a, &b, 200);
    t4 = std::thread(transfer, &b, &a, 200);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    std::cout << a.balance << ", " << b.balance << std::endl;
}