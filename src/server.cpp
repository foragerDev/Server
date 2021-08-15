#include "headers.hpp"
#include "User.hpp"
#include "Group.hpp"
#include <iostream>
#include <unordered_map>
#include "Acceptor.hpp"

int main(){


    net::io_context context;
    Acceptor acceptor(context, ip::tcp::endpoint{ip::address_v4::any(), 80});
    context.run();
    Group cricket("cricket");
    Group football("football");
    std::unordered_map<std::string, Group> groups;

    groups[cricket.get_name()] = cricket;
    groups[football.get_name()] = football;

    std::string user;
    std::cout << "Enter user name" << std::endl;
    std::cin >> user;
    User new_user(user);
    std::cout << "Enter group name: " << std::endl;
    std::string group_name;
    std::cin >> group_name;
    auto g = groups.find(group_name);
    if (g != groups.end()) {
        auto group = g->second;
        
        group.add_user(new_user);
    }
    else {
        std::cout << "group not found" << std::endl;
    }
}