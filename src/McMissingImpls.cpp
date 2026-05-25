#include <network/Packet.hpp>
Packet::Packet() = default;
Packet::~Packet() = default;

#include <Core/SemVer/SemVersion.hpp>
template class SemVersionBase<Bedrock::StaticOptimizedString>;
template class SemVersionBase<std::string_view>;

#include <Core/Resource/PackIdVersion.hpp>
PackIdVersion::PackIdVersion(PackIdVersion&&) = default;
PackIdVersion& PackIdVersion::operator=(const PackIdVersion&) = default;
PackIdVersion& PackIdVersion::operator=(PackIdVersion&&) = default;
