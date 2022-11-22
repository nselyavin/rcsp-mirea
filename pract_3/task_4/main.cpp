#include <iostream>
#include <mutex>
#include <queue>
#include <rxcpp/rx.hpp>
#include <rx-observable.hpp>
#include <rx-observer.hpp>
#include <rx-subscriber.hpp>
#include <vector>
#include <thread>

#include "File.h"
#include "Generator.h"
#include "Handler.h"

int main(){
    std::mutex queue_mut;
    std::queue<File> files;
    Generator generator;

    auto source = generator.get_generator().publish();

    std::cout << "main: " << std::this_thread::get_id() << std::endl;
    source.subscribe([&files, &queue_mut](File file){
        std::lock_guard lck(queue_mut);
        if(files.size() < 5){
            files.push(file);
        } else {
            std::cout << "Queue is overflow" << std::endl;
        }
    });

    source.subscribe([&queue_mut, &files](auto){
        File f;
        {
            std::lock_guard lck(queue_mut);
            f = files.front();
            files.pop();
        }

        FileHandler h(f);
    });

    source.connect();
    

    // Generator generator;

    // generator.get_generator(); 
    
    // file_source.subscribe(
    //     [&files, &queue_mut](File v){
    //         std::lock_guard lck(queue_mut);
    //         files.push_back(v);
    //     }
    // );


    // file_source.connect();

    return 0;
}