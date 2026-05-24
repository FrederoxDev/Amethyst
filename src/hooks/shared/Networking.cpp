#if defined(CLIENT) || defined(SERVER)
#include "hooks/shared/Networking.hpp"

#include <amethyst/Log.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/networking/NetworkManager.hpp>

#include <network/Packet.hpp>
#include <network/ServerNetworkHandler.hpp>

template <>
class PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, 0> : public IPacketHandlerDispatcher {
public:
	// IPacketHandlerDispatcher base is an empty stub; declare virtuals here in MC's slot order (dtor=0, handle=1).
	virtual ~PacketHandlerDispatcherInstance() = default;

	virtual void handle(const NetworkIdentifier& networkId, NetEventCallback& netEvent, std::shared_ptr<Packet>& _packet) const
	{
		auto& packet = reinterpret_cast<std::shared_ptr<Amethyst::CustomPacketInternal>&>(_packet);
		Amethyst::CustomPacketHandler* handler = Amethyst::GetNetworkManager().GetPacketHandler(packet->mTypeId);

		if (handler == nullptr) {
			Log::Warning("[PacketHandlerDispatcherInstance] No handler for CustomPacketInternal typeId {}, ignoring", packet->mTypeId);
			return;
		}

		handler->handle(networkId, netEvent, *packet->mPacket.get());
	}
};

static PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, 0> AmethystCustomPacketHandler;

namespace Amethyst::SharedHooks::NetworkingHooks {
	Amethyst::InlineHook<decltype(&ServerNetworkHandler::allowIncomingPacketId)> _ServerNetworkHandler_allowIncomingPacketId;
	IncomingPacketFilterResult ServerNetworkHandler_allowIncomingPacketId(ServerNetworkHandler* self, const NetworkIdentifierWithSubId& sender, MinecraftPacketIds packet, uint64_t packetSize)
	{
		if (static_cast<int>(packet) == static_cast<int>(MinecraftPacketIds::EndId) + 1) return IncomingPacketFilterResult::Allowed;
		return _ServerNetworkHandler_allowIncomingPacketId(self, sender, packet, packetSize);
	}

	Amethyst::InlineHook<decltype(&MinecraftPackets::createPacket)> _MinecraftPackets_createPacket;
	std::shared_ptr<Packet> MinecraftPackets_createPacket(MinecraftPacketIds id)
	{
		if (static_cast<int>(id) == static_cast<int>(MinecraftPacketIds::EndId) + 1) {
			auto shared = std::make_shared<Amethyst::CustomPacketInternal>();
			shared->mHandler = &AmethystCustomPacketHandler;
			return shared;
		}
		return _MinecraftPackets_createPacket(id);
	}

	void Initialize()
	{
		auto& hooks = Amethyst::GetHookManager();
		VHOOK(ServerNetworkHandler, allowIncomingPacketId, ServerNetworkHandler::$vtable_for_ServerNetworkHandler$NetEventCallback);
		HOOK(MinecraftPackets, createPacket);
	}
}
#endif
