#include "Mod.h"

struct int128{
    __int64 low;
    __int64 high;
};

// void(__fastcall*** a1)(_QWORD, __int64),
// __int64 a2,
// __int64 a3,
// _QWORD* a4,
// int a5,
// __int64 a6,
// char a7,
// __int128* a8,
// __int64 a9,
// __int64 a10,
// __int64* a11,
// _QWORD* a12

struct Vec3 {
    float x;
    float y;
    float z;
};

struct S_LocalPlayer {
    bool padding[1932];
    Vec3 headPosition;
};

S_LocalPlayer* localPlayer = nullptr;

// LocalPlayer::LocalPlayer(IClientInstance&, Level&, std::string const&, GameType, NetworkIdentifier const&, SubClientId, mce::UUID, std::string const&,std::string const&,std::unique_ptr<Certificate>,EntityContext &)
typedef S_LocalPlayer*(__thiscall* T_LocalPlayer)(void*, void*, void*, const std::string&, int, void*, unsigned char, int128, const std::string&, const std::string&, void*, void*);
T_LocalPlayer _LocalPlayer;

static S_LocalPlayer* LocalPlayer(void* p0, void* p1, void* p2, const std::string& p3, int p4, void* p5, unsigned char p6, int128 p7, const std::string& p8, const std::string& p9, void* p10, void* p11) {
    S_LocalPlayer* self = _LocalPlayer(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    Log::Info("p3: {}\n", p3);
    localPlayer = self;
    return self;
}

void ModInitializeHooks() {
    CreateHook(
        SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 A8 48 81 EC 58 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 4C 89 4D"), 
        LocalPlayer, _LocalPlayer
    );
}


void ModTick() {
    if (localPlayer != nullptr) {
        S_LocalPlayer player = *reinterpret_cast<S_LocalPlayer*>(localPlayer);
        Vec3 position = player.headPosition;

        Log::Info("X: {}, Y: {}, Z: {}\n", position.x, position.y, position.z);
    }
}