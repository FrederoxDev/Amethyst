class LevelRendererPlayer {
public:
    //48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05
    typedef float(__fastcall* _getFov)(LevelRendererPlayer*, float, bool);
};