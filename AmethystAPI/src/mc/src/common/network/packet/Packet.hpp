/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-deps/raknet/raknet/PacketPriority.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/network/NetworkPeer.hpp>
#include <mc/src-deps/core/utility/Result.hpp>
#include <mc/src-deps/core/utility/ErrorInfo.hpp>
#include <amethyst/Log.hpp>
#include <mc/src-deps/core/utility/BinaryStream.hpp>

class IPacketHandlerDispatcher;
class BinaryStream;

enum class MinecraftPacketIds {
    KeepAlive = 0,
    Login = 1,
    PlayStatus = 2,
    ServerToClientHandshake = 3,
    ClientToServerHandshake = 4,
    Disconnect = 5,
    ResourcePacksInfo = 6,
    ResourcePackStack = 7,
    ResourcePackClientResponse = 8,
    Text = 9,
    SetTime = 10,
    StartGame = 11,
    AddPlayer = 12,
    AddActor = 13,
    RemoveActor = 14,
    AddItemActor = 15,
    ServerPlayerPostMovePosition = 16,
    TakeItemActor = 17,
    MoveAbsoluteActor = 18,
    MovePlayer = 19,
    PassengerJump = 20,
    UpdateBlock = 21,
    AddPainting = 22,
    TickSync = 23,
    LevelSoundEventV1 = 24,
    LevelEvent = 25,
    TileEvent = 26,
    ActorEvent = 27,
    MobEffect = 28,
    UpdateAttributes = 29,
    InventoryTransaction = 30,
    PlayerEquipment = 31,
    MobArmorEquipment = 32,
    Interact = 33,
    BlockPickRequest = 34,
    ActorPickRequest = 35,
    PlayerAction = 36,
    ActorFall_deprecated = 37,
    HurtArmor = 38,
    SetActorData = 39,
    SetActorMotion = 40,
    SetActorLink = 41,
    SetHealth = 42,
    SetSpawnPosition = 43,
    Animate = 44,
    Respawn = 45,
    ContainerOpen = 46,
    ContainerClose = 47,
    PlayerHotbar = 48,
    InventoryContent = 49,
    InventorySlot = 50,
    ContainerSetData = 51,
    CraftingData = 52,
    CraftingEvent_Deprecated = 53,
    GuiDataPickItem = 54,
    AdventureSettings_Deprecated = 55,
    BlockActorData = 56,
    PlayerInput = 57,
    FullChunkData = 58,
    SetCommandsEnabled = 59,
    SetDifficulty = 60,
    ChangeDimension = 61,
    SetPlayerGameType = 62,
    PlayerList = 63,
    SimpleEvent = 64,
    LegacyTelemetryEvent = 65,
    SpawnExperienceOrb = 66,
    MapData = 67,
    MapInfoRequest = 68,
    RequestChunkRadius = 69,
    ChunkRadiusUpdated = 70,
    ItemFrameDropItem_Deprecated = 71,
    GameRulesChanged = 72,
    Camera = 73,
    BossEvent = 74,
    ShowCredits = 75,
    AvailableCommands = 76,
    CommandRequest = 77,
    CommandBlockUpdate = 78,
    CommandOutput = 79,
    UpdateTrade = 80,
    UpdateEquip = 81,
    ResourcePackDataInfo = 82,
    ResourcePackChunkData = 83,
    ResourcePackChunkRequest = 84,
    Transfer = 85,
    PlaySound = 86,
    StopSound = 87,
    SetTitle = 88,
    AddBehaviorTree = 89,
    StructureBlockUpdate = 90,
    ShowStoreOffer = 91,
    PurchaseReceipt = 92,
    PlayerSkin = 93,
    SubclientLogin = 94,
    AutomationClientConnect = 95,
    SetLastHurtBy = 96,
    BookEdit = 97,
    NPCRequest = 98,
    PhotoTransfer = 99,
    ShowModalForm = 100,
    ModalFormResponse = 101,
    ServerSettingsRequest = 102,
    ServerSettingsResponse = 103,
    ShowProfile = 104,
    SetDefaultGameType = 105,
    RemoveObjective = 106,
    SetDisplayObjective = 107,
    SetScore = 108,
    LabTable = 109,
    UpdateBlockSynced = 110,
    MoveDeltaActor = 111,
    SetScoreboardIdentity = 112,
    SetLocalPlayerAsInit = 113,
    UpdateSoftEnum = 114,
    Ping = 115,
    BlockPalette = 116,
    ScriptCustomEvent = 117,
    SpawnParticleEffect = 118,
    AvailableActorIDList = 119,
    LevelSoundEventV2 = 120,
    NetworkChunkPublisherUpdate = 121,
    BiomeDefinitionList = 122,
    LevelSoundEvent = 123,
    LevelEventGeneric = 124,
    LecternUpdate = 125,
    VideoStreamConnect_DEPRECATED = 126,
    AddEntity_DEPRECATED = 127,
    RemoveEntity_DEPRECATED = 128,
    ClientCacheStatus = 129,
    OnScreenTextureAnimation = 130,
    MapCreateLockedCopy = 131,
    StructureTemplateDataExportRequest = 132,
    StructureTemplateDataExportResponse = 133,
    UNUSED_PLS_USE_ME = 134,
    ClientCacheBlobStatusPacket = 135,
    ClientCacheMissResponsePacket = 136,
    EducationSettingsPacket = 137,
    Emote = 138,
    MultiplayerSettingsPacket = 139,
    SettingsCommandPacket = 140,
    AnvilDamage = 141,
    CompletedUsingItem = 142,
    NetworkSettings = 143,
    PlayerAuthInputPacket = 144,
    CreativeContent = 145,
    PlayerEnchantOptions = 146,
    ItemStackRequest = 147,
    ItemStackResponse = 148,
    PlayerArmorDamage = 149,
    CodeBuilderPacket = 150,
    UpdatePlayerGameType = 151,
    EmoteList = 152,
    PositionTrackingDBServerBroadcast = 153,
    PositionTrackingDBClientRequest = 154,
    DebugInfoPacket = 155,
    PacketViolationWarning = 156,
    MotionPredictionHints = 157,
    TriggerAnimation = 158,
    CameraShake = 159,
    PlayerFogSetting = 160,
    CorrectPlayerMovePredictionPacket = 161,
    ItemComponentPacket = 162,
    FilterTextPacket_DEPRECATED = 163,
    ClientBoundDebugRendererPacket = 164,
    SyncActorProperty = 165,
    AddVolumeEntityPacket = 166,
    RemoveVolumeEntityPacket = 167,
    SimulationTypePacket = 168,
    NpcDialoguePacket = 169,
    EduUriResourcePacket = 170,
    CreatePhotoPacket = 171,
    UpdateSubChunkBlocks = 172,
    PhotoInfoRequest_DEPRECATED = 173,
    SubChunkPacket = 174,
    SubChunkRequestPacket = 175,
    PlayerStartItemCooldown = 176,
    ScriptMessagePacket = 177,
    CodeBuilderSourcePacket = 178,
    TickingAreasLoadStatus = 179,
    DimensionDataPacket = 180,
    AgentAction = 181,
    ChangeMobProperty = 182,
    LessonProgressPacket = 183,
    RequestAbilityPacket = 184,
    RequestPermissionsPacket = 185,
    ToastRequest = 186,
    UpdateAbilitiesPacket = 187,
    UpdateAdventureSettingsPacket = 188,
    DeathInfo = 189,
    EditorNetworkPacket = 190,
    FeatureRegistryPacket = 191,
    ServerStats = 192,
    RequestNetworkSettings = 193,
    GameTestRequestPacket = 194,
    GameTestResultsPacket = 195,
    PlayerClientInputPermissions = 196,
    ClientCheatAbilityPacket_Deprecated = 197,
    CameraPresets = 198,
    UnlockedRecipes = 199,
    CameraInstruction = 300,
    CompressedBiomeDefinitionList = 301,
    TrimData = 302,
    OpenSign = 303,
    AgentAnimation = 304,
    RefreshEntitlementsPacket = 305,
    PlayerToggleCrafterSlotRequestPacket = 306,
    SetPlayerInventoryOptions = 307,
    SetHudPacket = 308,
    EndId = 309
};

/// @vptr { 0x2BCFDA8, this, win-server }
/// @vptr { 0x4CB18D0 }
class Packet {
public:
    PacketPriority mPriority;
    NetworkPeer::Reliability mReliability;
    SubClientId mClientSubId;
    bool mIsHandled;
    std::chrono::steady_clock::time_point mReceiveTimepoint;
    const IPacketHandlerDispatcher* mHandler;
    Compressibility mCompressible;

public:
	/// @vidx {0, this, win-server}
    /// @vidx {0}
    MC virtual ~Packet();

	/// @vidx {1, this, win-server}
	/// @vidx {1}
	MC virtual MinecraftPacketIds getId() const = 0;

	/// @vidx {2, this, win-server}
	/// @vidx {2}
	MC virtual std::string getName() const = 0;

	/// @vidx {3, this, win-server}
	/// @vidx {3}
	MC virtual Bedrock::Result<void, std::error_code> checkSize(uint64_t unk0, bool unk1) const;

	/// @vidx {4, this, win-server}
	/// @vidx {4}
	MC virtual void write(BinaryStream& unk0) const = 0;

	/// @vidx {5, this, win-server}
	/// @vidx {5}
	MC virtual Bedrock::Result<void, std::error_code> read(ReadOnlyBinaryStream& unk0);

	/// @vidx {6, this, win-server}
	/// @vidx {6}
	MC virtual bool disallowBatching() const;

	/// @vidx {7, this, win-server}
	/// @vidx {7}
	MC virtual bool isValid() const;

	/// @vidx {8, this, win-server}
	/// @vidx {8}
	MC virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& unk0) = 0;

public:
    Packet();
};

class MinecraftPackets {
public:
	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F9, win-server}
	/// @signature {40 53 48 83 EC ? 45 33 C0 48 8B D9 FF CA 81 FA}
	MC static std::shared_ptr<Packet> createPacket(MinecraftPacketIds id);
};