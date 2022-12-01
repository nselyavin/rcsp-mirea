/*
    2.1.2 Преобразовать поток из 1000 случайных чисел от 0 до 1000 в поток,
    содержащий только числа больше 500.
*/

#include <future>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>

void handle_input(int n){
    int delay = rand()%4+1;
    std::this_thread::sleep_for(std::chrono::seconds(delay));

    std::cout << std::this_thread::get_id() << ": n * 2 = " << pow(n, 2) << std::endl;

    return;
}

int main() {
    std::vector<std::future<void>> tasks;
    
    while(true){
        int n;
        std::cout << "Enter val> ";
        std::cin >> n;
        if(n == -1){
            break;
        }

        std::packaged_task task(handle_input);
        auto fut_1 = task.get_future();
        tasks.push_back(std::move(fut_1));
        std::thread t1(std::move(task), n);
        t1.detach();
    }

    for (auto& fut : tasks){
        fut.get();
    }
    return 0;
}