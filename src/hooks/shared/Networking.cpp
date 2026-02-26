#if defined(CLIENT) || defined(SERVER)
#include "hooks/shared/Networking.hpp"

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>

// #include <mc/src/common/network/PacketHandlerDispatcherInstance.hpp>
// #include <mc/src/common/network/ServerNetworkHandler.hpp>
// #include <mc/src/common/network/packet/Packet.hpp>

// template <>
// class PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, false> : public IPacketHandlerDispatcher {
// public:
// 	virtual void handle(const NetworkIdentifier& networkId, NetEventCallback& netEvent, std::shared_ptr<Packet>& _packet) const override {
// 		std::shared_ptr<Amethyst::CustomPacketInternal>& packet = (std::shared_ptr<Amethyst::CustomPacketInternal>&)_packet;
// 		Amethyst::CustomPacketHandler* handler = Amethyst::GetNetworkManager().GetPacketHandler(packet->mTypeId);

// 		if (handler == nullptr) {
// 			Log::Warning("[PacketHandlerDispatcherInstance] No handler found for CustomPacketInternal with typeId {}, ignoring packet", packet->mTypeId);
// 			return;
// 		}

// 		handler->handle(networkId, netEvent, *packet->mPacket.get());
// 	}
// };

// static PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, false> AmethystCustomPacketHandler;

namespace Amethyst::SharedHooks::NetworkingHooks {
	// Amethyst::InlineHook<decltype(&ServerNetworkHandler::allowIncomingPacketId)> _ServerNetworkHandler_allowIncomingPacketId;
	// bool ServerNetworkHandler_allowIncomingPacketId(ServerNetworkHandler* self, const NetworkIdentifier& networkId, MinecraftPacketIds packet) {
	// 	if ((int)packet == (int)MinecraftPacketIds::EndId + 1) {
	// 		return true;
	// 	}
	// 	return _ServerNetworkHandler_allowIncomingPacketId(self, networkId, packet);
	// }

	// Amethyst::InlineHook<decltype(&MinecraftPackets::createPacket)> _MinecraftPackets_createPacket;
	// std::shared_ptr<Packet> MinecraftPackets_createPacket(MinecraftPacketIds id) {
	// 	// Vanilla packets.
	// 	if (id <= MinecraftPacketIds::EndId) {
	// 		std::shared_ptr<Packet> packet = _MinecraftPackets_createPacket(id);
	// 		return packet;
	// 	}
	// 	// Custom packets
	// 	if ((int)id == (int)MinecraftPacketIds::EndId + 1) {
	// 		auto shared = std::make_shared<Amethyst::CustomPacketInternal>();
	// 		shared->mHandler = &AmethystCustomPacketHandler;
	// 		return shared;
	// 	}
	// 	AssertFail("MinecraftPackets::createPacket called with invalid packet id {}", (int)id);
	// }

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		// HOOK(ServerNetworkHandler, allowIncomingPacketId);
		// HOOK(MinecraftPackets, createPacket);
	}
}
#endif