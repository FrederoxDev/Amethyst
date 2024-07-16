#pragma once
#include <minecraft/src/common/network/packet/Packet.hpp>
#include <minecraft/src-deps/core/utility/UUID.hpp>

struct CommandOriginData {
public:
	int			mType;
	mce::UUID	mUuid;
	std::string	mRequestId;
	int64_t		mPlayerId;

	CommandOriginData() : mType(0), mUuid(), mRequestId(""), mPlayerId(0) {};
	CommandOriginData(struct CommandOriginData const& other) {
		mType = other.mType;
		mUuid = other.mUuid;
		mRequestId = other.mRequestId;
		mPlayerId = other.mPlayerId;
	};
	struct CommandOriginData& operator=(struct CommandOriginData const& rhs) {
		CommandOriginData origin(rhs);
		return origin;
	};
};

class CommandRequestPacket : public Packet {
public:
	std::string			mCommand;
	CommandOriginData	mOrigin;
	bool				mIsInternal;
	int					mVersion;

public:
	~CommandRequestPacket() {};
	CommandRequestPacket() : mCommand(""), mOrigin(), mIsInternal(false), mVersion(0) {};

	virtual MinecraftPacketIds getId() const override { return MinecraftPacketIds::CommandRequest; };
	virtual std::string getName() const override { return "CommandRequestPacket"; };
	virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& stream) override { Assert("Unimplemented"); };
	virtual void write(BinaryStream& stream) override {
		stream.writeString(mCommand);
		stream.writeUnsignedVarInt32(mOrigin.mType);
		stream.write(mOrigin.mUuid);
		stream.writeString(mOrigin.mRequestId);
		stream.write(mIsInternal);
		stream.writeUnsignedVarInt32(mVersion);
	};
};
