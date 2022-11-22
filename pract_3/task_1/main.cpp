#include <rxcpp/rx.hpp>
#include <chrono>
#include <exception>
#include <rx-observable.hpp>
#include <rx-observer.hpp>
#include <rx-subscriber.hpp>
#include <rx-subscription.hpp>
#include <thread>

#include <thread>


using ms = std::chrono::milliseconds;

int main()
{
    auto temp_source = rxcpp::observable<>::interval(std::chrono::milliseconds(1000), rxcpp::observe_on_new_thread())
    .map([](int v){return rand() % 6 + 22;})
    .publish();

    auto co2_source = rxcpp::observable<>::interval(std::chrono::milliseconds(1000), rxcpp::observe_on_new_thread())
    .map([](int v){return rand() % 6 + 67;})
    .publish();

    // Subscribe from the beginning
    co2_source.subscribe(
        [](long v){
            if(v > 70){
                printf("ALARM: CO2: %ld > 70\n", v);
            } 
        },
        [](){printf("[1] OnCompleted\n");});

    // Another subscription from the beginning
    decltype(temp_source.subscribe()) sub = temp_source.subscribe(
        [&sub](long v){
            if (v > 25){
                printf("ALARM: temp %ld > 25\n", v);
            }
        },
        [](){printf("[2] OnCompleted\n");});


    co2_source.connect();
    temp_source.connect();

    while(sub.is_subscribed()){

    }
    return 0;
}