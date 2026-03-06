// #ifdef CLIENT
// #pragma once
// #include <amethyst/runtime/ModContext.hpp>
// #include "amethyst/game/client/ICustomUIRendererRegistry.hpp"

// class CustomUIRendererRegistry : public Amethyst::ICustomUIRendererRegistry {
// private:
// 	std::unordered_map<std::string, std::function<std::shared_ptr<MinecraftUICustomRenderer>()>> mFactories;

// public:
// 	CustomUIRendererRegistry() : Amethyst::ICustomUIRendererRegistry() {}

// 	virtual void registerRenderer(const std::string& id, std::function<std::shared_ptr<MinecraftUICustomRenderer>()> factory) override {
// 		if (mFactories.find(id) != mFactories.end()) {
// 			Log::Warning("Custom UI Renderer with id '{}' is already registered, overwriting.", id);
// 		}
// 		mFactories[id] = std::move(factory);
// 	}

// 	std::shared_ptr<MinecraftUICustomRenderer> tryCreateRenderer(const std::string& id) {
// 		auto it = mFactories.find(id);
// 		if (it == mFactories.end()) return nullptr;
// 		return it->second();
// 	}

// 	static void AddEventListeners();
// };
// #endif