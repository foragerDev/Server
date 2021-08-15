#pragma once
#include <string>
#include <random>

class User
{
private:
    std::string m_username;
    std::string m_user_id;
    
private:
    std::string generate_user_id(size_t length = 6)
    {
        std::random_device device;
        std::mt19937 engine(device());
        std::uniform_int_distribution<> distribution('a', 'z');
        std::string result{};
        for (size_t i = 0; i < length; i++)
        {
            result += static_cast<char>(distribution(engine));
        }
        return result;
    }


public:
    User() = default;
    explicit User(const std::string &_username) : m_username(_username), m_user_id(generate_user_id()) {}
    const std::string &get_username() const
    {
        return m_username;
    }
    const std::string &get_user_id() const
    {
        return m_user_id;
    }

    void set_username(const std::string &_username)
    {
        m_username = _username;
    }
};