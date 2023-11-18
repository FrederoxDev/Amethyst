#include "client/common/client/game/ClientInstance.h"

BlockSource* ClientInstance::getRegion() {
    typedef BlockSource* (__thiscall* _getRegion)(ClientInstance* self);
	return reinterpret_cast<_getRegion>(this->vftable[26])(this);
}