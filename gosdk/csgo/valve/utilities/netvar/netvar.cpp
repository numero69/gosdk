#include "netvar.hpp"
#include "../../interfaces.hpp"
#include <fstream>

std::ofstream ofStream( STR( "netvar_dump.dmp" ) );

void DumpRecursive( CS::Classes::CRecvTable * table ) {
  for ( auto i = 0; i < table->PropsCount; ++i ) {
    const auto prop = &table->Props[ i ];

    if ( !prop || std::isdigit( prop->PropName[ 0 ] ) || !std::strcmp( prop->PropName, STR( STR( "baseclass" ) ) ) )
      continue;

    if ( prop->PropType == 6 && prop->DataTable && prop->DataTable->TableName[ 0 ] == 'D' )
      DumpRecursive( prop->DataTable );

    ofStream << table->TableName + std::string( STR( "->" ) ) + prop->PropName << "=" << prop->Offset << '\n';

    CS::Utilities::Netvar::Offsets[ table->TableName + std::string( STR( "->" ) ) + prop->PropName ] = prop->Offset;
  }
}

void CS::Utilities::Netvar::Init( ) {
  for ( auto pclass = CS::Interfaces::g_pClient->GetAllClasses( ); pclass; pclass = pclass->NextPtr ) {
    const auto table = pclass->RecvTablePtr;

    if ( !table )
      continue;

    DumpRecursive( table );
  }
}