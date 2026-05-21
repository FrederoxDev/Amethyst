#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include <nonstd/expected.hpp>

#include <amethyst/Log.hpp>
#include <amethyst/runtime/HookManager.hpp>
#include <amethyst/runtime/networking/CustomPacket.hpp>

#include <network/Packet.hpp>
#include <network/PacketSender.hpp>

class UserEntityIdentifierComponent;
class NetworkIdentifierWithSubId;

namespace Amethyst {

template<typename T>
concept DerivedFromCustomPacket = std::is_base_of_v<CustomPacket, T>;

/// Wire-level envelope. Carries a typeId + the inner CustomPacket's bytes.
/// Claims MinecraftPacketIds::EndId + 1 as its id so MC's dispatcher ignores it;
/// routing happens via Amethyst::NetworkManager once readNoHeader decodes the typeId.
class CustomPacketInternal final : public ::Packet {
public:
    std::unique_ptr<CustomPacket> mPacket;
    uint64_t mTypeId = 0;

    CustomPacketInternal() = default;

    CustomPacketInternal(std::unique_ptr<CustomPacket> packet, uint64_t typeId)
        : mPacket(std::move(packet)), mTypeId(typeId)
    {
        mReliability  = mPacket->mReliability;
        mPriority     = mPacket->mPriority;
        mCompressible = mPacket->mCompressible;
    }

    CustomPacketInternal(const CustomPacketInternal&) = delete;
    CustomPacketInternal& operator=(const CustomPacketInternal&) = delete;
    CustomPacketInternal(CustomPacketInternal&&) noexcept = default;
    CustomPacketInternal& operator=(CustomPacketInternal&&) noexcept = default;

    void InitPacketFromNetwork(uint64_t typeId);

    MinecraftPacketIds getId() const override
    {
        return static_cast<MinecraftPacketIds>(static_cast<int>(MinecraftPacketIds::EndId) + 1);
    }

    std::string_view getName() const override
    {
        return "Amethyst::CustomPacketInternal";
    }

    void write(BinaryStream& out) const override
    {
        out.writeUnsignedVarInt64(mTypeId, "typeId", "");
        if (mPacket) mPacket->write(out);
    }

    Bedrock::Result<void, std::error_code> read(ReadOnlyBinaryStream& in) override
    {
        auto id = in.getUnsignedVarInt64();
        if (!id.has_value()) return ::nonstd::expected_lite::make_unexpected(id.error());

        InitPacketFromNetwork(*id);
        if (!mPacket) {
            Log::Warning("[CustomPacketInternal] No factory for typeId {}", *id);
            return {};
        }

        return mPacket->read(in);
    }

    Bedrock::Result<void, std::error_code> read(ReadOnlyBinaryStream& in, const ::cereal::ReflectionCtx&) override
    {
        return read(in);
    }

    Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& in) override
    {
        return read(in);
    }

    void handle(const NetworkIdentifier& source, NetEventCallback& callback) const;
};

class NetworkManager {
public:
    NetworkManager() = default;
    NetworkManager(const NetworkManager&) = delete;
    NetworkManager(NetworkManager&&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    NetworkManager& operator=(NetworkManager&&) = delete;

    template<DerivedFromCustomPacket T>
    void RegisterPacketType(std::unique_ptr<CustomPacketHandler> handler)
    {
        constexpr uint64_t typeId = function_id::class_hash<T>();
        Assert(!mPacketHandlers.contains(typeId),
            "[Amethyst] Packet type already registered for typeId {}", typeId);

        mPacketHandlers[typeId] = std::move(handler);
        mPacketFactories[typeId] = []() -> std::unique_ptr<CustomPacket> {
            return std::make_unique<T>();
        };
    }

    template<DerivedFromCustomPacket T>
    void Send(::PacketSender& sender, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.send(wrapped);
    }

    template<DerivedFromCustomPacket T>
    void SendToServer(::PacketSender& sender, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.sendToServer(wrapped);
    }

    template<DerivedFromCustomPacket T>
    void SendToClient(::PacketSender& sender, const UserEntityIdentifierComponent* userIdentifier, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.sendToClient(userIdentifier, wrapped);
    }

    template<DerivedFromCustomPacket T>
    void SendToClient(::PacketSender& sender, const NetworkIdentifier& id, SubClientId subId, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.sendToClient(id, wrapped, subId);
    }

    template<DerivedFromCustomPacket T>
    void SendToClients(::PacketSender& sender, const std::vector<NetworkIdentifierWithSubId>& ids, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.sendToClients(ids, wrapped);
    }

    template<DerivedFromCustomPacket T>
    void SendBroadcast(::PacketSender& sender, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.sendBroadcast(wrapped);
    }

    template<DerivedFromCustomPacket T>
    void SendBroadcast(::PacketSender& sender, const NetworkIdentifier& exceptId, SubClientId exceptSub, std::unique_ptr<T> packet)
    {
        auto wrapped = CreateSendable(std::move(packet));
        sender.sendBroadcast(exceptId, exceptSub, wrapped);
    }

    CustomPacketHandler* GetPacketHandler(uint64_t typeId) const
    {
        auto it = mPacketHandlers.find(typeId);
        if (it != mPacketHandlers.end()) return it->second.get();
        Log::Warning("[NetworkManager] No handler for typeId {}", typeId);
        return nullptr;
    }

    std::unique_ptr<CustomPacket> CreatePacket(uint64_t typeId) const
    {
        auto it = mPacketFactories.find(typeId);
        if (it != mPacketFactories.end()) return it->second();
        Log::Warning("[NetworkManager] No factory for typeId {}", typeId);
        return nullptr;
    }

private:
    template<DerivedFromCustomPacket T>
    CustomPacketInternal CreateSendable(std::unique_ptr<T> packet)
    {
        return CustomPacketInternal(std::move(packet), function_id::class_hash<T>());
    }

    std::unordered_map<uint64_t, std::unique_ptr<CustomPacketHandler>> mPacketHandlers;
    std::unordered_map<uint64_t, std::function<std::unique_ptr<CustomPacket>()>> mPacketFactories;
};

} // namespace Amethyst
