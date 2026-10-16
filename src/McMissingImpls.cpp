#include <network/Packet.hpp>
Packet::Packet() = default;
Packet::~Packet() = default;

#include <resources/Pack.hpp>
#include <resources/PackSource.hpp>

void CompositePackSource::addPackSource(PackSource* packSource)
{
	mPackSources.emplace_back(packSource);
}

#include <Core/SemVer/SemVersion.hpp>
template class SemVersionBase<Bedrock::StaticOptimizedString>;
template class SemVersionBase<std::string_view>;
