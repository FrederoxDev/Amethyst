#include <minecraft/src/common/Minecraft.hpp>

Level* Minecraft::getLevel() const
{
    return mGameSession->mLevel.get();
}