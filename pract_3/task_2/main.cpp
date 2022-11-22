/*
    2.1.2 Преобразовать поток из 1000 случайных чисел от 0 до 1000 в поток,
    содержащий только числа больше 500.
*/

#include <rxcpp/rx.hpp>
#include <iostream>
#include <rx-observable.hpp>
#include <rx-observer.hpp>


void part_1(){
    std::cout << "\n==== Part 1 ====\n";
    auto grand_stream = rxcpp::observable<>::range(0, 1000)
    .map([](int v){return rand() % 1000;}).publish();


    grand_stream.take(35)
    .subscribe([](int v){
        std::cout << "Original: " << v << " ";
    });

    auto half_grand_stream = grand_stream.filter([](int v){return v > 500;});
    half_grand_stream.take(30).subscribe(
        [](int v){
            std::cout << "Filtered: " << v << " ";
        }
    );

    grand_stream.connect();
}

void part_2(){
    std::cout << "\n==== Part 2 ====\n";
    auto source_1 = rxcpp::observable<>::range<int>(1, 6);


    auto source_2 = rxcpp::observable<>::range<int>(7, 12);

    source_1.concat(source_2).subscribe(
        [](int v){
            std::cout << v << " ";
        }
    );

}


void part_3(){
    std::cout << "\n==== Part 3 ====\n";
    auto source_1 = rxcpp::observable<>::range<int>(1, 10);


    source_1.subscribe(
        [](int v){
            std::cout << "Source 1 " << v << " ";
        }
    );

    auto source_2 = source_1.take(5);

    std::cout << std::endl;
    source_2.subscribe(
        [](int v){
            std::cout << "Source 2 " << v << " ";
        }
    );


}



int main() {

    part_3();
    return 0;
}