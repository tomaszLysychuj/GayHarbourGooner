#include "RLBotClient.h"
#include <iostream>
#include <signal.h>
#include <thread>

// Global client instance for signal handling
std::unique_ptr<RLBotClient> g_client;

void signalHandler(int signal) {
    std::cout << "\nReceived signal " << signal << ". Shutting down..." << std::endl;
    if (g_client) {
        g_client->Shutdown();
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    // Set up signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    std::cout << "GigaLearn RLBot Client Starting..." << std::endl;
    
    // Create and initialize client
    g_client = std::make_unique<RLBotClient>();
    
    if (!g_client->Initialize()) {
        std::cerr << "Failed to initialize RLBot client!" << std::endl;
        return 1;
    }
    
    std::cout << "RLBot client initialized successfully!" << std::endl;
    std::cout << "Press Ctrl+C to stop the bot." << std::endl;
    
    // Run the client
    g_client->Run();
    
    std::cout << "RLBot client stopped." << std::endl;
    return 0;
}
