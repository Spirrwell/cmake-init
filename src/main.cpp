#include <filesystem>
#include <string_view>
#include <iostream>

#define REPO "https://github.com/Spirrwell/Template_CMake.git"

int main( int argc, char* argv[] )
{
	if ( argc > 1 )
	{
		for ( int i = 1; i < argc; ++i )
		{
			if ( std::string_view( argv[i] ) == "--version" )
			{
				std::cout << "0.0.1\n";
				return 0;
			}
		}
	}

	system( "git clone --depth=1 " REPO " template-cmake" );

	std::filesystem::remove_all( "template-cmake/.git" );
	const std::filesystem::directory_iterator it( "./template-cmake" );

	for ( const std::filesystem::path& p : it )
	{
		if ( p.filename() == ".gitignore" )
			continue;

		const std::filesystem::path dest = "." / p.filename();
		std::filesystem::rename( p, dest );
	}

	std::filesystem::remove_all( "template-cmake/" );
}