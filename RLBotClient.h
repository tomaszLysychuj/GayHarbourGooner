#pragma once

#include <RLBotCPP/inc/rlbot/rlbot.h>
#include <RLBotCPP/inc/rlbot/interface.h>
#include <RLBotCPP/inc/rlbot/state.h>
#include <RLBotCPP/inc/rlbot/rendering.h>
#include <RLBotCPP/inc/rlbot/match.h>
#include <RLBotCPP/inc/rlbot/player.h>
#include <RLBotCPP/inc/rlbot/ball.h>
#include <RLBotCPP/inc/rlbot/car.h>
#include <RLBotCPP/inc/rlbot/vector3.h>
#include <RLBotCPP/inc/rlbot/rotator.h>
#include <RLBotCPP/inc/rlbot/controller.h>
#include <RLBotCPP/inc/rlbot/gameinfo.h>
#include <RLBotCPP/inc/rlbot/team.h>
#include <RLBotCPP/inc/rlbot/colors.h>
#include <RLBotCPP/inc/rlbot/constants.h>
#include <RLBotCPP/inc/rlbot/input.h>
#include <RLBotCPP/inc/rlbot/fieldinfo.h>
#include <RLBotCPP/inc/rlbot/boostpad.h>
#include <RLBotCPP/inc/rlbot/goal.h>
#include <RLBotCPP/inc/rlbot/boostpadstate.h>
#include <RLBotCPP/inc/rlbot/playerinfo.h>
#include <RLBotCPP/inc/rlbot/physics.h>
#include <RLBotCPP/inc/rlbot/score.h>
#include <RLBotCPP/inc/rlbot/ballinfo.h>
#include <RLBotCPP/inc/rlbot/carinfo.h>
#include <RLBotCPP/inc/rlbot/gameinfo.h>
#include <RLBotCPP/inc/rlbot/matchinfo.h>
#include <RLBotCPP/inc/rlbot/playerinfo.h>
#include <RLBotCPP/inc/rlbot/boostpadinfo.h>
#include <RLBotCPP/inc/rlbot/goalinfo.h>
#include <RLBotCPP/inc/rlbot/fieldinfo.h>
#include <RLBotCPP/inc/rlbot/constants.h>
#include <RLBotCPP/inc/rlbot/colors.h>
#include <RLBotCPP/inc/rlbot/team.h>
#include <RLBotCPP/inc/rlbot/input.h>
#include <RLBotCPP/inc/rlbot/controller.h>
#include <RLBotCPP/inc/rlbot/rotator.h>
#include <RLBotCPP/inc/rlbot/vector3.h>
#include <RLBotCPP/inc/rlbot/car.h>
#include <RLBotCPP/inc/rlbot/ball.h>
#include <RLBotCPP/inc/rlbot/player.h>
#include <RLBotCPP/inc/rlbot/match.h>
#include <RLBotCPP/inc/rlbot/rendering.h>
#include <RLBotCPP/inc/rlbot/state.h>
#include <RLBotCPP/inc/rlbot/interface.h>
#include <RLBotCPP/inc/rlbot/rlbot.h>

#include <GigaLearnCPP/Learner.h>
#include <RLGymCPP/OBSBuilders/AdvancedObs.h>
#include <RLGymCPP/ActionParsers/DefaultAction.h>

#include <memory>
#include <vector>
#include <string>

class RLBotClient {
public:
    RLBotClient();
    ~RLBotClient();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    void ProcessGameTick(const rlbot::GameTickPacket& packet);
    rlbot::Controller GetControllerOutput(const rlbot::GameTickPacket& packet);
    
    // GigaLearn components
    std::unique_ptr<GGL::Learner> learner;
    std::unique_ptr<RLGC::AdvancedObs> obsBuilder;
    std::unique_ptr<RLGC::DefaultAction> actionParser;
    
    // RLBot components
    rlbot::Interface rlbotInterface;
    int botIndex;
    std::string checkpointPath;
    
    // Game state
    bool isInitialized;
    bool shouldRun;
};
