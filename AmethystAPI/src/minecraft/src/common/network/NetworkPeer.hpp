#pragma once

class NetworkPeer {
public:
    enum class Reliability : int {
        Reliable, 
        ReliableOrdered, 
        Unreliable, 
        UnreliableSequenced
    };
};

enum class Compressibility : int {
    Compressible, 
    Incompressible
};