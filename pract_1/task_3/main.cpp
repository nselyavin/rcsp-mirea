#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "File.h"
#include "Generator.h"
#include "Handler.h"

int main() {
    std::condition_variable cond;
    std::mutex file_mtx;
    std::vector<File> file_pull;
    Generator generator(file_pull, file_mtx, cond);

    std::cout << "main: " << std::this_thread::get_id() << std::endl;
    std::thread gen_t(generator);

    std::thread hand_t([&file_mtx, &file_pull, &cond]{
        while(true){
            File file;
            {
                std::unique_lock<std::mutex> lck(file_mtx);
                cond.wait(lck, [&file_pull]{
                    return not file_pull.empty();
                });

                // std::lock_guard lck_2(file_mtx);
                file = file_pull.back();
                file_pull.pop_back();
            }
            FileHandler handler(file);

        };
    });

    hand_t.join();
    gen_t.join();

    return 0;
}