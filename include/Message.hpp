#include <chrono>
#include <string>

class Message{
public:
    Message(const std::string& _message): m_message(_message), m_timestamp(std::chrono::system_clock::now()){}
private:
    std::string m_message;
    std::chrono::time_point<std::chrono::system_clock> m_timestamp;
};