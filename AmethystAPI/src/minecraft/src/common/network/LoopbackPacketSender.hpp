#pragma once
#include <minecraft/src/common/network/PacketSender.hpp>

class LoopbackPacketSender : public PacketSender {
public:
	virtual ~LoopbackPacketSender() override;
	virtual void send(Packet& packet) override;
	virtual void sendToServer(Packet& packet) override;
	virtual void sendToClient(const UserEntityIdentifierComponent* userIdentifier, const Packet& packet) override;
	virtual void sendToClient(const NetworkIdentifier& id, const Packet& packet, SubClientId subid) override;
	virtual void sendToClients(const std::vector<NetworkIdentifierWithSubId>& ids, const Packet& packet) override;
	virtual void sendBroadcast(const Packet& packet) override;
	virtual void sendBroadcast(const NetworkIdentifier& exceptId, SubClientId exceptSubid, const Packet& packet) override;
	virtual void flush(const NetworkIdentifier& id, std::function<void()>&& callback) override;
};