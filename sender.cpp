#include "src/Sender.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main()
{
    Sender sender;
    sender.connectToServer("localhost", 12345);
    sender.sendMessage("MESSAGE");
    // for(int i = 0; i <= 10; i++)
    // {
    //     std::this_thread::sleep_for(3000ms);
    //     server.sendMessage("MESSAGE");
    // }
    while(true)
    {}
    
    return 0;
}