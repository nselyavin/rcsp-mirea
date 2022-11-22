#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <vector>
#include <mutex>


class File{
public:
    File():_size(0), _type("no type"){}
    
    File(int size, std::string type): _size(size), _type(type){}

    uint32_t size(){
        return _size;
    }

    std::string type(){
        return _type;
    }

private:
    uint32_t _size;
    std::string _type;
};

#endif // FILE_H
