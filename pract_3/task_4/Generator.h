#ifndef GENERATOR_H
#define GENERATOR_H

#include <mutex>
#include <rxcpp/rx.hpp>
#include <rx-observable.hpp>
#include <rx-observer.hpp>
#include <chrono>
#include <thread>

#include "File.h"

class Generator{
public:
    auto get_generator(){
            auto newthread = rxcpp::observe_on_new_thread();
            auto source = rxcpp::observable<>::create<File>([](rxcpp::subscriber<File> s){
                while(true){
                    auto delay = std::chrono::milliseconds(random() % 900 + 100);
                    std::string type;
                    switch (rand()%3){
                        case(0):{
                            type = "XML";
                            break;
                        }
                        case(1):{
                            type = "JSON";
                            break;
                        }
                        case(2):{
                            type = "XLS";
                            break;
                        }
                    };

                    File file(rand()%90+10, type);
                    std::this_thread::sleep_for(delay);
                    std::cout << "Generated: " << file.size() << ", " << file.type() << " delay: " << delay << std::endl;
                    s.on_next(file);
                }

                s.on_completed();
            }).observe_on(newthread);

            return source;
    }
private:

};

#endif // GENERATOR_H
