#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#include "File.h"


class FileHandler
{
public:
    FileHandler(File f){
        std::this_thread::sleep_for(std::chrono::milliseconds(f.size() * 100));
        if(f.type() == "JSON"){
            json_handler(f);
        }
        if(f.type() == "XLS"){
            xls_handler(f);
        }
        if(f.type() == "XML"){
            xml_handler(f);
        }
    }

    void json_handler(File f){
        std::cout << "json handler: " << f.size() << ", " << f.type() << std::endl;
    }

    void xml_handler(File f){
        std::cout << "xml handler: " << f.size() << ", " << f.type() << std::endl;
    }

    void xls_handler(File f){
        std::cout << "xls handler: " << f.size() << ", " << f.type() << std::endl;
    }

private:

};

#endif // HANDLER_H
