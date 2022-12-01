#include <chrono>
#include <iostream>
#include <future>
#include <thread>
#include <omp.h>

using namespace std::literals::chrono_literals;

int find_max(int* arr, int n){
    int max = arr[0];

    for(int i = 0; i < n; i++){
        std::this_thread::sleep_for(1ms);
        if (max < arr[i]){
            std::this_thread::sleep_for(1ms);
            max = arr[i];
        }
    }

    return max;
}

int async_find_max(int* arr, int n){
    auto fut1 = std::async(std::launch::async, 
    [n, arr]{
        int max = arr[0];
        for (int i = 0; i < n / 2; i++){
            std::this_thread::sleep_for(1ms);
            if (max < arr[i]){
                std::this_thread::sleep_for(1ms);
                max = arr[i];
            }
        }

        return max;
    });

    auto fut2 = std::async(std::launch::async, 
    [n, arr]{
        int max = arr[n/2];
        for (int i = n/2; i < n; i++){
            std::this_thread::sleep_for(1ms);
            if (max < arr[i]){
                std::this_thread::sleep_for(1ms);
                max = arr[i];
            }
        }

        return max;
    });

    return std::max(fut1.get(), fut2.get());
}


int omp_find_max(int* arr, int n){
    omp_set_num_threads(4);
    int max = arr[0];
    int i = 0;

    #pragma omp parallel for private(i) shared(arr) reduction(max: max)
    for (i = 0; i < n; i++){
        std::this_thread::sleep_for(1ms);
        if(max < arr[i]){
            std::this_thread::sleep_for(1ms);
            max = arr[i];
        }
    }

    return max;
}


int main()
{
    const int n = 500;
    int arr[n];

    for(int i = 0; i < n; i++){
        arr[i] = rand() % 200;
    }

    auto start = std::chrono::system_clock::now();
    std::cout << "simple find max: " << find_max(arr, n) << std::endl;
    auto end = std::chrono::system_clock::now();
    std::cout << "duration: " << std::chrono::duration<double>(end-start).count() << " ms\n";

    start = std::chrono::system_clock::now();
    std::cout << "thread find max: " << async_find_max(arr, n) << std::endl;
    end = std::chrono::system_clock::now();
    std::cout << "duration: " << std::chrono::duration<double>(end-start).count() << " ms\n";

    start = std::chrono::system_clock::now();
    std::cout << "omp find max: " << omp_find_max(arr, n) << std::endl;
    end = std::chrono::system_clock::now();
    std::cout << "duration: " << std::chrono::duration<double>(end-start).count() << " ms\n";

    return 0;
}