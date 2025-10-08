# GigaLearn RLBot Integration

This folder contains files needed to integrate your trained GigaLearnCPP bot with RLBot framework for playing against humans and other bots.

## Files Included

- **`RLBotClient.h`** - Header file for RLBot client
- **`RLBotClient.cpp`** - Implementation of RLBot client
- **`rlbotmain.cpp`** - Main entry point for RLBot executable
- **`CppPythonAgent.cfg`** - RLBot agent configuration
- **`CMakeLists_RLBot.txt`** - CMake configuration for RLBot build
- **`README_RLBot_Integration.md`** - This file

## Setup Instructions

### Step 1: Replace Files in Your Project

1. **Copy `CMakeLists_RLBot.txt`** → Rename to `CMakeLists.txt` and replace your existing one
2. **Copy source files** → Place `RLBotClient.h`, `RLBotClient.cpp`, and `rlbotmain.cpp` in your `src/` directory
3. **Copy config file** → Place `CppPythonAgent.cfg` in your `rlbot/` directory

### Step 2: Configure Paths

1. **Edit `CppPythonAgent.cfg`**:
   ```
   cpp_executable_path = C:\path\to\your\compiled\rlbot.exe
   ```

2. **Edit `rlbotmain.cpp`** (optional - for specific checkpoint):
   ```cpp
   // Uncomment and modify this line:
   checkpointPath = "C:\\Users\\YourUser\\GigaLearnCPP\\build\\Release\\checkpoints\\14594451456\\POLICY.lt";
   ```

### Step 3: Build and Run

1. **Re-compile your project** using Visual Studio or your build tool
2. **Ensure checkpoint folder** exists in the same directory as your executable
3. **Add agent to RLBot** using the `CppPythonAgent.cfg` file
4. **Launch match** from RLBot GUI

## How It Works

- **Automatic checkpoint detection** - Finds the latest checkpoint automatically
- **RLBot integration** - Connects to RLBot framework for online play
- **Signal handling** - Graceful shutdown with Ctrl+C
- **Error handling** - Robust error handling and logging

## Troubleshooting

### Bot doesn't appear in RLBot?
- Check that `cpp_executable_path` in `CppPythonAgent.cfg` is correct
- Ensure the executable was built successfully

### Could not connect to server?
- Verify port numbers match between `rlbotmain.cpp` and `port.cfg`
- Check that RLBot is running

### Event Loop Stopped?
- Install correct websockets version: `pip install websockets==12.0`
- Check port configuration

## Notes

- **Ball prediction**: Not supported by default (can be added)
- **Padded observations**: Likely supported (modify `obsBuilder` initialization)
- **Checkpoint loading**: Automatically finds latest checkpoint
- **Performance**: Optimized for real-time gameplay

## Usage After Training

Once your bot is trained:

1. **Copy checkpoint** to the executable directory
2. **Build RLBot version** using these files
3. **Configure RLBot** with the agent file
4. **Play against humans** or other bots online!

## Support

This integration is based on the [GigaLearn-RLBot-Example](https://github.com/Kuenec/GigaLearn-RLBot-Example/tree/main) repository.

---

**Ready to play your trained bot against humans!** 🎮⚽
