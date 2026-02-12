#include "src/NetworkManager.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main()
{
    NetworkManager server;

    server.connectToServer("localhost", 12345);
    while(true)
    {}
    // server.sendMessage("MESSAGE");
    // for(int i = 0; i <= 10; i++)
    // {
    //     std::this_thread::sleep_for(3000ms);
    //     server.sendMessage("MESSAGE");
    // }
    
    return 0;
}