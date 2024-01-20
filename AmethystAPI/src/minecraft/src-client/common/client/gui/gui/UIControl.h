#pragma once
#include <string>

class UIControl {
public:
  std::byte padding[24];
  std::string layerName; // this + 24
};
