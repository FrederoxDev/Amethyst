#pragma once

class BaseOptions {
public:
    virtual ~BaseOptions();

    float getSensitivity(unsigned int inputMode);
};