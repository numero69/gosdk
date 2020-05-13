#pragma once

#include "../../../utilities/global.hpp"

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
      return Utils::Memory::CallVirtualMethod<bool, int, const PlayerInfo &>( this, 8, entity_index, p_info );
    }

    constexpr auto GetPlayerForUID( int user_id ) noexcept {
      return Utils::Memory::CallVirtualMethod<int, int>( this, 9, user_id );
    }

    constexpr auto GetLocalPlayer( ) noexcept { return Utils::Memory::CallVirtualMethod<int>( this, 12 ); }

    constexpr auto GetViewAngles( Utils::Math::Vector & angles ) noexcept {
      Utils::Memory::CallVirtualMethod<void, Utils::Math::Vector &>( this, 18, angles );
    }

    constexpr auto SetViewAngles( const Utils::Math::Vector & angles ) noexcept {
      Utils::Memory::CallVirtualMethod<void, const Utils::Math::Vector &>( this, 19, angles );
    }

    constexpr auto GetMaxClients( ) noexcept { return Utils::Memory::CallVirtualMethod<int>( this, 20 ); }

    constexpr auto IsInGame( ) noexcept { return Utils::Memory::CallVirtualMethod<bool>( this, 26 ); }

    constexpr auto IsConnected( ) noexcept { return Utils::Memory::CallVirtualMethod<bool>( this, 27 ); }

    using matrix = float[ 4 ][ 4 ];

    constexpr auto WorldToScreenMatrix( ) noexcept { return Utils::Memory::CallVirtualMethod<const matrix &>( this, 37 ); }

    constexpr auto GetLevelName( ) noexcept { return Utils::Memory::CallVirtualMethod<const char *>( this, 53 ); }

    constexpr auto GetNetChannel( ) noexcept { return Utils::Memory::CallVirtualMethod<CNetChannel *>( this, 78 ); }

    constexpr auto ClientCmdUnrestricted( const char * cmd ) noexcept {
      Utils::Memory::CallVirtualMethod<void, const char *, bool>( this, 114, cmd, false );
    }
  };
} // namespace CS::Interfaces