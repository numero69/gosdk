#pragma once

#include "../../../utilities/global.hpp"

/* Indexes */
enum EEngineClientIndexes : short {
  GetPlayerInfo_index = 8,
  GetPlayerForUID_index = 9,
  GetLocalPlayer_index = 12,
  GetViewAngles_index = 18,
  SetViewAngles_index = 19,
  GetMaxClients_index = 20,
  IsInGame_index = 26,
  IsConnected_index = 27,
  WorldToScreenMatrix_index = 37,
  GetLevelName_index = 53,
  GetNetChannel_index = 78,
  ClientCmdUnrestricted_index = 114
};

namespace CS::Interfaces {
  using PlayerInfo_t = struct SPlayerInfo {
    std::uint64_t m_Version;
    union {
      std::uint64_t m_XUid;
      struct {
        std::uint32_t m_XUidLow;
        std::uint32_t m_XUidHigh;
      };
    };
    char m_Name[ 128 ];
    int m_UserId;
    char m_GUid[ 33 ];
    std::uint32_t m_FriendsId;
    char m_FriendsName[ 128 ];
    bool m_FakePlayer;
    bool m_HLTV;
    int m_CustomFiles[ 4 ];
    unsigned char m_FilesDownloaded;
    int m_EntityIndex;
  };

  class CNetChannel;
  class IEngineClient {
  public:
    constexpr auto GetPlayerInfo( int entity_index, const PlayerInfo_t * p_info ) noexcept {
      return Utils::Memory::CallVirtualMethod<bool, int, const PlayerInfo_t *>(
          this, EEngineClientIndexes::GetPlayerInfo_index, entity_index, p_info );
    }

    constexpr auto GetPlayerForUID( int user_id ) noexcept {
      return Utils::Memory::CallVirtualMethod<int, int>( this, EEngineClientIndexes::GetPlayerForUID_index, user_id );
    }

    constexpr auto GetLocalPlayer( ) noexcept {
      return Utils::Memory::CallVirtualMethod<int>( this, EEngineClientIndexes::GetLocalPlayer_index );
    }

    constexpr auto GetViewAngles( Utils::Math::Vector & angles ) noexcept {
      Utils::Memory::CallVirtualMethod<void, Utils::Math::Vector &>( this, EEngineClientIndexes::GetViewAngles_index, angles );
    }

    constexpr auto SetViewAngles( const Utils::Math::Vector & angles ) noexcept {
      Utils::Memory::CallVirtualMethod<void, const Utils::Math::Vector &>(
          this, EEngineClientIndexes::SetViewAngles_index, angles );
    }

    constexpr auto GetMaxClients( ) noexcept {
      return Utils::Memory::CallVirtualMethod<int>( this, EEngineClientIndexes::GetMaxClients_index );
    }

    constexpr auto IsInGame( ) noexcept {
      return Utils::Memory::CallVirtualMethod<bool>( this, EEngineClientIndexes::IsInGame_index );
    }

    constexpr auto IsConnected( ) noexcept {
      return Utils::Memory::CallVirtualMethod<bool>( this, EEngineClientIndexes::IsConnected_index );
    }

    using matrix = float[ 4 ][ 4 ];

    constexpr auto WorldToScreenMatrix( ) noexcept {
      return Utils::Memory::CallVirtualMethod<const matrix &>( this, EEngineClientIndexes::WorldToScreenMatrix_index );
    }

    constexpr auto GetLevelName( ) noexcept {
      return Utils::Memory::CallVirtualMethod<const char *>( this, EEngineClientIndexes::GetLevelName_index );
    }

    constexpr auto GetNetChannel( ) noexcept {
      return Utils::Memory::CallVirtualMethod<CNetChannel *>( this, EEngineClientIndexes::GetNetChannel_index );
    }

    constexpr auto ClientCmdUnrestricted( const char * cmd ) noexcept {
      Utils::Memory::CallVirtualMethod<void, const char *, bool>(
          this, EEngineClientIndexes::ClientCmdUnrestricted_index, cmd, false );
    }
  };
} // namespace CS::Interfaces