#include "amethyst/runtime/networking/NetworkManager.hpp"
#include "amethyst/runtime/ModContext.hpp"

namespace Amethyst {

void CustomPacketInternal::InitPacketFromNetwork(uint64_t typeId)
{
    mTypeId = typeId;
    mPacket = GetNetworkManager().CreatePacket(typeId);
}

void CustomPacketInternal::handle(const NetworkIdentifier& source, NetEventCallback& callback) const
{
    if (!mPacket) {
        Log::Warning("[CustomPacketInternal] handle called with null inner packet (typeId {})", mTypeId);
        return;
    }

    CustomPacketHandler* handler = GetNetworkManager().GetPacketHandler(mTypeId);
    if (!handler) return;

    handler->handle(source, callback, *mPacket);
}

} // namespace Amethyst
