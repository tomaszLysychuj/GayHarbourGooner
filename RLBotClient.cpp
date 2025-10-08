#include "RLBotClient.h"
#include <iostream>
#include <filesystem>
#include <algorithm>

RLBotClient::RLBotClient() : isInitialized(false), shouldRun(true), botIndex(-1) {
}

RLBotClient::~RLBotClient() {
    Shutdown();
}

bool RLBotClient::Initialize() {
    try {
        // Initialize RLBot interface
        rlbotInterface = rlbot::Interface();
        
        // Initialize GigaLearn components
        obsBuilder = std::make_unique<RLGC::AdvancedObs>();
        actionParser = std::make_unique<RLGC::DefaultAction>();
        
        // Try to find the latest checkpoint
        std::string checkpointsDir = "checkpoints";
        if (std::filesystem::exists(checkpointsDir)) {
            std::string latestCheckpoint;
            uint64_t latestTimestamp = 0;
            
            for (const auto& entry : std::filesystem::directory_iterator(checkpointsDir)) {
                if (entry.is_directory()) {
                    std::string dirName = entry.path().filename().string();
                    try {
                        uint64_t timestamp = std::stoull(dirName);
                        if (timestamp > latestTimestamp) {
                            latestTimestamp = timestamp;
                            latestCheckpoint = entry.path().string();
                        }
                    } catch (...) {
                        // Skip non-numeric directories
                    }
                }
            }
            
            if (!latestCheckpoint.empty()) {
                checkpointPath = latestCheckpoint + "/POLICY.lt";
                std::cout << "Found checkpoint: " << checkpointPath << std::endl;
            }
        }
        
        // If no checkpoint found, use hardcoded path (uncomment and modify as needed)
        // checkpointPath = "C:\\Users\\YourUser\\GigaLearnCPP\\build\\Release\\checkpoints\\14594451456\\POLICY.lt";
        
        if (checkpointPath.empty()) {
            std::cout << "Warning: No checkpoint found. Bot will use random actions." << std::endl;
        }
        
        isInitialized = true;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialize RLBot client: " << e.what() << std::endl;
        return false;
    }
}

void RLBotClient::Run() {
    if (!isInitialized) {
        std::cerr << "RLBot client not initialized!" << std::endl;
        return;
    }
    
    std::cout << "Starting RLBot client..." << std::endl;
    
    while (shouldRun) {
        try {
            // Get game state
            auto packet = rlbotInterface.GetGameTickPacket();
            
            if (packet.has_value()) {
                ProcessGameTick(packet.value());
            }
            
            // Small delay to prevent excessive CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            
        } catch (const std::exception& e) {
            std::cerr << "Error in main loop: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void RLBotClient::ProcessGameTick(const rlbot::GameTickPacket& packet) {
    // Find our bot's index
    if (botIndex == -1) {
        for (int i = 0; i < packet.players.size(); i++) {
            if (packet.players[i].isBot) {
                botIndex = i;
                break;
            }
        }
    }
    
    if (botIndex == -1 || botIndex >= packet.players.size()) {
        return;
    }
    
    // Get controller output
    auto controller = GetControllerOutput(packet);
    
    // Send input to game
    rlbotInterface.SetBotInput(controller, botIndex);
}

rlbot::Controller RLBotClient::GetControllerOutput(const rlbot::GameTickPacket& packet) {
    rlbot::Controller controller;
    
    // For now, return neutral controller
    // TODO: Implement GigaLearn inference here
    controller.throttle = 0.0f;
    controller.steer = 0.0f;
    controller.pitch = 0.0f;
    controller.yaw = 0.0f;
    controller.roll = 0.0f;
    controller.jump = false;
    controller.boost = false;
    controller.handbrake = false;
    
    return controller;
}

void RLBotClient::Shutdown() {
    shouldRun = false;
    isInitialized = false;
    std::cout << "RLBot client shutdown." << std::endl;
}
