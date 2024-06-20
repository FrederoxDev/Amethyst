#pragma once
#include <vector>
#include <functional>
#include <minecraft/src/common/CommonTypes.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>

// Auto-generated: Unknown complete types
struct NetworkIdentifierWithSubId {}; 

// Auto-generated: Forward declarations
class Packet; 
class NetworkIdentifier; 
class UserEntityIdentifierComponent; 

#pragma pack(push, 8)
class PacketSender : Bedrock::EnableNonOwnerReferences {
public:
    SubClientId mSenderSubId;

public:
	virtual ~PacketSender() = default;
	virtual void send(Packet& packet) = 0;
	virtual void sendToServer(Packet& packet) = 0;
	virtual void sendToClient(const UserEntityIdentifierComponent* userIdentifier, const Packet& packet) = 0;
	virtual void sendToClient(const NetworkIdentifier& id, const Packet& packet, SubClientId subid) = 0;
	virtual void sendToClients(const std::vector<NetworkIdentifierWithSubId>& ids, const Packet& packet) = 0;
	virtual void sendBroadcast(const Packet& packet) = 0;
	virtual void sendBroadcast(const NetworkIdentifier& exceptId, SubClientId exceptSubid, const Packet& packet) = 0;
	virtual void flush(const NetworkIdentifier& id, std::function<void()>&& callback) = 0;
};
#pragma pack(pop)