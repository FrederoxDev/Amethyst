#pragma once
#include <memory>
class SimpleContainer;

struct ActorEquipmentComponent
{
  std::unique_ptr<SimpleContainer> mHand;
  std::unique_ptr<SimpleContainer> mArmor;
};