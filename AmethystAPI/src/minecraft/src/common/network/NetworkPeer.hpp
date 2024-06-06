#pragma once

class NetworkPeer {
public:
    enum Reliability : int {
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