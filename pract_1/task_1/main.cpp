#include <chrono>
#include <iostream>

#include <omp.h>
#include <thread>

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

int thread_find_max(int* arr, int n){

}


int omp_find_max(int* arr, int n){
    int max = arr[0];

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

    // std::cout << "thread find max: " << thread_find_max(arr, n) << std::endl;
    // std::cout << "omp find max: " << omp_find_max(arr, n) << std::endl;

    return 0;
}