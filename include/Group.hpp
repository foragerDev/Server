#pragma once

#include "User.hpp"
#include <unordered_map>
#include <string>
#include <optional>

class Group
{
private:
    std::string m_group_name;
    std::unordered_map<std::string, User> m_users;

public:
    Group() = default;
    explicit Group(const std::string &group_name) : m_group_name(group_name)
    {
    }

    bool is_empty() const
    {
        return m_users.empty();
    }

    void remove_user(const std::string &user_id)
    {
        auto user = m_users.find(user_id);
        if (user != m_users.end())
        {
            m_users.erase(user);
        }
    }

    const std::string &get_name() const { return m_group_name; }

    void add_user(const User &user)
    {
        m_users[user.get_user_id()] = user;
    }

    std::optional<User> get_user(const std::string &user_id)
    {
        auto user = m_users.find(user_id);
        if (user == m_users.end())
        {
            return user->second;
        }
        return std::nullopt;
    }
};