#include <iostream>
#include <thread> 
#include "mingw.thread.h"

// Function that each thread will run
void print_numbers(int thread_id) {
    for (int i = 1; i <= 5; ++i) {
        std::cout << "Thread " << thread_id << ": " << i << std::endl;
    }
}

int main() {
    // // Create and start 4 threads
    std::thread t1(print_numbers, 1);
    std::thread t2(print_numbers, 2);
    std::thread t3(print_numbers, 3);
    std::thread t4(print_numbers, 4);

    // Join all threads with the main thread to ensure they complete execution
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
