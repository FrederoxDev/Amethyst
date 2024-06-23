#pragma once
#include <vector>
#include <optional>
#include <minecraft/src-deps/core/string/StringHash.hpp>

enum class LogAreaID : unsigned int {LOG_AREA_ALL, LOG_AREA_PLATFORM, LOG_AREA_ENTITY, LOG_AREA_DATABASE, LOG_AREA_GUI, LOG_AREA_SYSTEM, LOG_AREA_NETWORK, LOG_AREA_RENDER, LOG_AREA_MEMORY, LOG_AREA_ANIMATION, LOG_AREA_INPUT, LOG_AREA_LEVEL, LOG_AREA_SERVER, LOG_AREA_DLC, LOG_AREA_PHYSICS, LOG_AREA_FILE, LOG_AREA_STORAGE, LOG_AREA_REALMS, LOG_AREA_REALMSAPI, LOG_AREA_XBOXLIVE, LOG_AREA_USERMANAGER, LOG_AREA_XSAPI, LOG_AREA_PERF, LOG_AREA_TELEMETRY, LOG_AREA_BLOCKS, LOG_AREA_RAKNET, LOG_AREA_GAMEFACE, LOG_AREA_SOUND, LOG_AREA_INTERACTIVE, LOG_AREA_SCRIPTING, LOG_AREA_PLAYFAB, LOG_AREA_AUTOMATION, LOG_AREA_PERSONA, LOG_AREA_TEXTURE, LOG_AREA_ASSETPACKAGES, LOG_AREA_ITEMS, LOG_AREA_SERVICES, LOG_AREA_VOLUMES, LOG_AREA_LOOTTABLE, LOG_AREA_SIDEBAR, LOG_AREA_LOCALIZATION, LOG_AREA_MOVEMENT, LOG_AREA_LIVEEVENTS, LOG_AREA_EDITOR, LOG_AREA_LEVELTRANSITION, LOG_AREA_UNKNOWN, LOG_AREA_STORE, LOG_AREA_WORLD, LOG_AREA_MESSAGING, LOG_AREA_INVALID = 10000, NUM_LOG_AREAS};

namespace Bedrock {
    enum class LogLevel : int {Error = 8, Warning = 4, Info = 2, Verbose = 1};

    class CallStack {
    public:
        #pragma pack(push, 8)
        class Frame {
            HashType64 mFilenameHash;
            std::string_view mFilename;
            uint32_t mLine;
        };
        #pragma pack(pop)

        class Context {
            std::string mValue;
            std::optional<Bedrock::LogLevel> mLogLevel;
            std::optional<LogAreaID> mLogArea;
        };

        class FrameWithContext {
        public:
            Bedrock::CallStack::Frame mFrame;
            std::optional<Bedrock::CallStack::Context> mContext;      
        };

    public:
        std::vector<Bedrock::CallStack::FrameWithContext> mFrames;
    };
}