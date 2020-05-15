#include "config.hpp"
#include <Windows.h>
#include <sstream>

#pragma warning( disable : 4244 )

namespace Config {
  bool SSettings::bSave( const std::string & config_file_name ) {
    nlohmann::json config;
    for ( const auto & [ setting, value ] : mSettings ) {
      if ( std::holds_alternative<int>( value ) )
        config[ setting ] = { { STR( "identifier" ), value.index( ) }, { STR( "value" ), this->get<int>( setting ) } };
      else if ( std::holds_alternative<bool>( value ) )
        config[ setting ] = { { STR( "identifier" ), value.index( ) }, { STR( "value" ), this->get<bool>( setting ) } };
      else if ( std::holds_alternative<float>( value ) )
        config[ setting ] = { { STR( "identifier" ), value.index( ) }, { STR( "value" ), this->get<float>( setting ) } };
      else if ( std::holds_alternative<std::string>( value ) )
        config[ setting ] = { { STR( "identifier" ), value.index( ) }, { STR( "value" ), this->get<std::string>( setting ) } };
      else if ( std::holds_alternative<Utils::Color>( value ) )
        config[ setting ] = { { STR( "identifier" ), value.index( ) },
                              { STR( "value_r" ), this->get<Utils::Color>( setting ).uRed },
                              { STR( "value_g" ), this->get<Utils::Color>( setting ).uGreen },
                              { STR( "value_b" ), this->get<Utils::Color>( setting ).uBlue }

        };
    }
    std::ofstream ofConfig( config_file_name );
#ifdef _DEBUG
    ofConfig << std::setw( 2 ) << config << std::endl;
#else
    // Reduce configs file size in release mode.
    ofConfig << config << std::endl;
#endif
    ofConfig.close( );
    return true;
  }

  bool SSettings::bLoad( const std::string & config_file_name ) {
    if ( !std::filesystem::exists( std::filesystem::current_path( ) / config_file_name ) )
      return false;

    std::ifstream ifConfig( config_file_name );
    nlohmann::json config = nlohmann::json::parse( ifConfig );
    for ( const auto & [ setting, value ] : config.items( ) ) {
      switch ( value[ STR( "identifier" ) ].get<int>( ) ) {
        case 0:
          mSettings[ setting ] = value[ STR( "value" ) ].get<int>( );
          break;
        case 1:
          mSettings[ setting ] = value[ STR( "value" ) ].get<bool>( );
          break;
        case 2:
          mSettings[ setting ] = value[ STR( "value" ) ].get<float>( );
          break;
        case 3:
          mSettings[ setting ] = value[ STR( "value" ) ].get<std::string>( );
          break;
        case 4:
          this->get<Utils::Color>( setting ).uRed = value[ STR( "value_r" ) ].get<float>( );
          this->get<Utils::Color>( setting ).uGreen = value[ STR( "value_g" ) ].get<float>( );
          this->get<Utils::Color>( setting ).uBlue = value[ STR( "value_b" ) ].get<float>( );
          break;
      }
    }
    ifConfig.close( );
    return true;
  }

  bool SSettings::bLoadClip( const std::string & data ) {
    nlohmann::json config = nlohmann::json::parse( data );
    for ( const auto & [ setting, value ] : config.items( ) ) {
      switch ( value[ STR( "identifier" ) ].get<int>( ) ) {
        case 0:
          mSettings[ setting ] = value[ STR( "value" ) ].get<int>( );
          break;
        case 1:
          mSettings[ setting ] = value[ STR( "value" ) ].get<bool>( );
          break;
        case 2:
          mSettings[ setting ] = value[ STR( "value" ) ].get<float>( );
          break;
        case 3:
          mSettings[ setting ] = value[ STR( "value" ) ].get<std::string>( );
          break;
        case 4:
          this->get<Utils::Color>( setting ).uRed = value[ STR( "value_r" ) ].get<float>( );
          this->get<Utils::Color>( setting ).uGreen = value[ STR( "value_g" ) ].get<float>( );
          this->get<Utils::Color>( setting ).uBlue = value[ STR( "value_b" ) ].get<float>( );
          break;
      }
    }
    return true;
  }
} // namespace Config