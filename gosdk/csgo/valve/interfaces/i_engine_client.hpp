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
  struct PlayerInfo {
    std::uint64_t version;
    union {
      std::uint64_t xuid;
      struct {
        std::uint32_t xuid_low;
        std::uint32_t xuid_high;
      };
    };
    char name[ 128 ];
    int user_id;
    char guid[ 33 ];
    std::uint32_t friends_id;
    char friends_name[ 128 ];
    bool fake_player;
    bool hltv;
    int custom_files[ 4 ];
    unsigned char files_downloaded;
    int entity_index;
  };

  class CNetChannel;
  class IEngineClient {
  public:
    constexpr auto GetPlayerInfo( int entity_index, const PlayerInfo & p_info ) noexcept {
      return Utils::Memory::CallVirtualMethod<bool, int, const PlayerInfo &>(
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