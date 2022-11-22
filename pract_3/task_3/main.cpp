#include <iostream>
#include <rxcpp/rx.hpp>
#include <rx-observable.hpp>
#include <rx-observer.hpp>
#include <vector>

class UserFriend{
public:
    UserFriend(int user_id, int friend_id): user_id(user_id), friend_id(friend_id){}
    UserFriend(const UserFriend& other) = default;
    
    int get_user_id(){
        return user_id;
    }

    int get_friend_id(){
        return friend_id;
    }

private:
    int user_id;
    int friend_id;
};


auto get_friends(std::vector<UserFriend> arr, int user_id)
{

    rxcpp::observable source = rxcpp::observable<>::iterate(arr).filter([user_id](UserFriend user_friend){
        return user_friend.get_user_id() == user_id; });
    return std::move(source);
}

int main(){

    std::vector<UserFriend> user_friends = {
        {11, 12},
        {11, 13},
        {1312, 132},
        {11, 1},
        {3, 11}
    };


    std::cout << "User 11 friends: \n";
    get_friends(user_friends, 11).subscribe([](UserFriend v){
        std::cout << v.get_user_id() << " " << v.get_friend_id() << std::endl;
    });


    std::vector<int> rand_user_id = {11, 12, 1, 5, 6, 3};
    auto rand_user_id_source = rxcpp::observable<>::iterate(rand_user_id);

    auto rand_user_id_friends = rand_user_id_source.concat_map([user_friends](int user_id){
        return get_friends(user_friends, user_id);
    });

    std::cout << "Random user friends: \n";
    rand_user_id_friends.subscribe([](UserFriend v){
        std::cout << v.get_user_id() << " " << v.get_friend_id() << std::endl;
    });

    return 0;
}