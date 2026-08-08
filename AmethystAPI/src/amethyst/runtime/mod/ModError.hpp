#pragma once
#include <string>
#include <unordered_map>
#include <optional>
#include <format>

enum class ModErrorStep {
	Unknown,
	Collecting,
    Resolving,
    Loading
};

enum class ModErrorType {
	Unknown,
    IOError,
    ParseError,
    CircularDependency,
    WrongDependencyVersion,
    MissingDependency,
    IncompatibleGameBuild,
    UnhandledException
};

struct ModError {
    ModErrorStep Step;
    ModErrorType Type;
    std::optional<std::string> UUID = std::nullopt;
    std::string Message;
    std::unordered_map<std::string, std::string> Data = {};

    std::string getFormattedMessage() const {
        std::string message = Message;
        for (const auto& [key, value] : Data) {
            size_t pos = 0;
            while ((pos = message.find(key, pos)) != std::string::npos) {
                message.replace(pos, key.length(), value);
                pos += value.length();
            }
        }
        return message;
    }

    std::string toString() const {
        std::string stepStr;
        switch (Step) {
            case ModErrorStep::Unknown: 
                stepStr = "Unknown"; 
                break;
            case ModErrorStep::Collecting: 
                stepStr = "Collecting"; 
                break;
            case ModErrorStep::Resolving:
                stepStr = "Resolving"; 
                break;
            default: 
                stepStr = "N/A"; 
                break;
        }

        std::string typeStr;
        switch (Type) {
            case ModErrorType::Unknown: 
                typeStr = "Unknown"; 
                break;
            case ModErrorType::IOError:
                typeStr = "IOError"; 
                break;
            case ModErrorType::ParseError:
                typeStr = "ParseError"; 
                break;
            case ModErrorType::CircularDependency:
                typeStr = "CircularDependency"; 
                break;
            case ModErrorType::WrongDependencyVersion:
                typeStr = "WrongDependencyVersion"; 
                break;
            case ModErrorType::MissingDependency:
                typeStr = "MissingDependency";
                break;
            case ModErrorType::IncompatibleGameBuild:
                typeStr = "IncompatibleGameBuild";
                break;
            default: 
                typeStr = "N/A"; 
                break;
        }

        std::string message = std::format("ModError(Step: {}, Type: {}, UUID: {})", 
            stepStr,
            typeStr,
            UUID.value_or("N/A")
        );
        message += "\n  " + getFormattedMessage();
        return message;
    }
};