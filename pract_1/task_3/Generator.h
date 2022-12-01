#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <memory>
#include <mutex>
#include <chrono>
#include <thread>
#include <vector>
#include <condition_variable>

#include "File.h"

using namespace std::literals;

class Generator{
public:
    Generator(std::vector<File>& file_pull, std::mutex& mtx, 
    std::condition_variable& cond)
    : file_pull{file_pull}, 
      mtx{mtx}, 
      cond{cond}
    { } 

    void operator()(){   
        while(true){
            int delay = rand() % 900 + 100;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));

            File file(rand()%90 + 10, "XML");
            {
                std::lock_guard lck(mtx);
                file_pull.push_back(file);
                std::cout << "Generated file: " << file.size() << " ." << file.type() << std::endl;
                cond.notify_one();
            }
        }

    }
private:
    std::vector<File>& file_pull;
    std::mutex& mtx;
    std::condition_variable& cond;

};

#endif // GENERATOR_H
