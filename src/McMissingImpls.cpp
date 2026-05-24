// Definitions for MC symbols that the binary doesn't export directly. Each
// translation-unit that constructs a Packet-derived type on the stack needs
// this dtor visible to its linker — the MC header only declares it.
#include <network/Packet.hpp>

Packet::Packet() = default;
Packet::~Packet() = default;

// SemVersion uses `extern template class SemVersionBase<...>` in its header
// (SemVersion.hpp:109-110), which suppresses implicit instantiation. MC's
// binary doesn't export the explicit instantiation. Force it here so users
// (e.g. PackManager constructing a SemVersion from int args) link cleanly.
#include <Core/SemVer/SemVersion.hpp>
template class SemVersionBase<Bedrock::StaticOptimizedString>;
template class SemVersionBase<std::string_view>;

// PackIdVersion move/assign are `[inlined]` in MC — no exported symbol. Provide
// them so users that move a PackInstance (which has a PackIdVersion member)
// link cleanly.
#include <Core/Resource/PackIdVersion.hpp>
PackIdVersion::PackIdVersion(PackIdVersion&&) = default;
PackIdVersion& PackIdVersion::operator=(const PackIdVersion&) = default;
PackIdVersion& PackIdVersion::operator=(PackIdVersion&&) = default;
