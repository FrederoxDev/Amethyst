// #pragma once
// #include <amethyst/runtime/HookManager.hpp>
// #include "amethyst/runtime/networking/CustomPacket.hpp"
// #include <amethyst/Log.hpp>
// #include <common/network/Packet.hpp>
// #include <common/network/PacketSender.hpp>
// #include <common/world/actor/player/Player.hpp>

// class UserEntityIdentifierComponent;

// namespace Amethyst {

// template<typename T>
// concept DerivedFromCustomPacket = std::is_base_of_v<Amethyst::CustomPacket, T>;

// /// @internal
// /// Intended for internal use only, DO NOT USE!
// /// Instead use Amethyst::CustomPacket as the base class for your packets.
// class CustomPacketInternal final : public ::Packet {
// public:
//     std::unique_ptr<Amethyst::CustomPacket> mPacket;
//     uint64_t mTypeId;

//     CustomPacketInternal() 
//         : Packet(), mPacket(nullptr), mTypeId(0) {}

//     CustomPacketInternal(std::unique_ptr<Amethyst::CustomPacket> packet, uint64_t typeId) 
//         : Packet(), mPacket(std::move(packet)), mTypeId(typeId) {
//             mReliability = mPacket->mReliability;
//             mPriority = mPacket->mPriority;
//             mCompressible = mPacket->mCompressible;
//         }

//     // Delete copy semantics
//     CustomPacketInternal(const CustomPacketInternal&) = delete;
//     CustomPacketInternal& operator=(const CustomPacketInternal&) = delete;

//     // Allow move semantics
//     CustomPacketInternal(CustomPacketInternal&&) noexcept = default;
//     CustomPacketInternal& operator=(CustomPacketInternal&&) noexcept = default;

//     void InitPacketFromNetwork(uint64_t typeId);

//     virtual MinecraftPacketIds getId() const override {
//         return (MinecraftPacketIds)((int)MinecraftPacketIds::EndId + 1);
//     }

//     virtual std::string getName() const {
//         Assert(mPacket != nullptr, "Attempted to get the name of a CustomPacketInternal with a null mPacket!");
//         return mPacket->getName();
//     }

//     virtual void write(BinaryStream& out) const override {
//         Assert(mTypeId != 0, "Attempted to write a CustomPacketInternal with a typeId of 0!");
//         out.write<uint64_t>(mTypeId);
//         Assert(mPacket != nullptr, "Attempted to write a CustomPacketInternal with a null mPacket!");
//         mPacket->write(out);
//     }

//     virtual Bedrock::Result<void, std::error_code> read(ReadOnlyBinaryStream& in) override {
//         uint64_t id = in.get<uint64_t>().value();
//         Assert(id != 0, "Received a CustomPacketInternal with a typeId of 0!");
//         InitPacketFromNetwork(id);

// 		if (mPacket == nullptr) {
// 			Log::Warning("[CustomPacketInternal] Failed to create packet for typeId {}", id);
// 			return {};
// 		}

//         return mPacket->read(in);
//     }

//     virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& in) override {
//         return Bedrock::Result<void, std::error_code>();
//     }
// };

// class NetworkManager {
// public:
//     NetworkManager()
//         : mPacketHandlers(), mPacketFactories() {}
//     NetworkManager(const NetworkManager&) = delete;
//     NetworkManager(NetworkManager&&) = delete;
//     NetworkManager& operator=(const NetworkManager&) = delete;
//     NetworkManager& operator=(NetworkManager&&) = delete;

//     template<DerivedFromCustomPacket T>
//     void RegisterPacketType(std::unique_ptr<Amethyst::CustomPacketHandler> handler) {
//         constexpr uint64_t typeId = function_id::class_hash<T>();
//         Assert(!mPacketHandlers.contains(typeId), "[Amethyst] Attempted to register packet when a packet with that name already exists!");
//         mPacketHandlers[typeId] = std::move(handler);

//         mPacketFactories[typeId] = []() -> std::unique_ptr<CustomPacket> {
//             return std::make_unique<T>();
//         };
//     }

//     template <DerivedFromCustomPacket T>
//     void Send(::PacketSender& sender, std::unique_ptr<T> packet) 
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.send(sendable);
//     }

//     template<DerivedFromCustomPacket T>
//     void SendToServer(::PacketSender& sender, std::unique_ptr<T> packet) 
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.sendToServer(sendable);
//     }

// 	template <DerivedFromCustomPacket T>
//     void SendToClient(::PacketSender& sender, const Player& player, std::unique_ptr<T> packet)
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.sendToClient(player.getUserIdentity(), sendable);
//     }

//     template <DerivedFromCustomPacket T>
//     void SendToClient(::PacketSender& sender, const UserEntityIdentifierComponent* userIdentifier, std::unique_ptr<T> packet)
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.sendToClient(userIdentifier, sendable);
//     }

//     template <DerivedFromCustomPacket T>
//     void SendToClient(::PacketSender& sender, const NetworkIdentifier& id, SubClientId subid, std::unique_ptr<T> packet)
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.sendToClient(id, sendable, subid);
//     }

//     template <DerivedFromCustomPacket T>
//     void SendToClients(::PacketSender& sender, const std::vector<NetworkIdentifierWithSubId>& ids, std::unique_ptr<T> packet)
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.sendToClients(ids, sendable);
//     }

//     template <DerivedFromCustomPacket T>
//     void SendBroadcast(::PacketSender& sender, std::unique_ptr<T> packet)
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.sendBroadcast(sendable);
//     }

//     template <DerivedFromCustomPacket T>
//     void SendBroadcast(::PacketSender& sender, const NetworkIdentifier& exceptId, SubClientId exceptSubid, std::unique_ptr<T> packet)
//     {
//         CustomPacketInternal sendable = CreateSendablePacket(std::move(packet));
//         sender.send(exceptId, exceptSubid, sendable);
//     }

//     CustomPacketHandler* GetPacketHandler(uint64_t typeId) {
//         auto it = mPacketHandlers.find(typeId);
//         if (it != mPacketHandlers.end()) {
//             return it->second.get();
//         }

// 		Log::Warning("[NetworkManager] No packet handler found for typeId {}", typeId);
// 		return nullptr;
//     }

//     std::unique_ptr<Amethyst::CustomPacket> CreatePacket(uint64_t typeId) {
//         auto it = mPacketFactories.find(typeId);
//         if (it != mPacketFactories.end()) {
//             return it->second();
//         }
        
// 		Log::Warning("[NetworkManager] No packet factory found for typeId {}", typeId);
// 		return nullptr;
//         // Assert(false, "[NetworkManager] No packet factory found for typeId {}", typeId);
//         // std::unreachable();
//     }

// private:
//     template<DerivedFromCustomPacket T>
//     CustomPacketInternal CreateSendablePacket(std::unique_ptr<T> packet) {
//         return CustomPacketInternal(std::move(packet), function_id::class_hash<T>());
//     }

//     std::unordered_map<uint64_t, std::unique_ptr<CustomPacketHandler>> mPacketHandlers;
//     std::unordered_map<uint64_t, std::function<std::unique_ptr<Amethyst::CustomPacket>()>> mPacketFactories;
// };
// }