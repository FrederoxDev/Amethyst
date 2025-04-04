#pragma once
class BlockPos;

class IGameModeMessenger {
public:
    virtual ~IGameModeMessenger() = default;
    virtual void unkn1() = 0;
    virtual void unkn2() = 0;
    virtual void unkn3() = 0;
    virtual void unkn4() = 0;
    virtual void unkn5() = 0;
    virtual void unkn6() = 0;
    virtual void unkn7() = 0;
    virtual void unkn8() = 0;
    virtual void startSendItemUseOn(const BlockPos&, const BlockPos&, int) = 0;
};