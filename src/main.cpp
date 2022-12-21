#include <filesystem>
#include <string_view>
#include <iostream>
#include <vector>
#include <unordered_set>

#define REPO "https://github.com/Spirrwell/Template_CMake.git"
#define VERSION "0.0.1"

int main( int argc, char* argv[] )
{
	std::unordered_set<std::string_view> arguments;

	if ( argc > 1 )
	{
		for ( int i = 1; i < argc; ++i )
			arguments.emplace( argv[i] );
	}

	if ( arguments.contains( "--version" ) )
	{
		std::cout << VERSION << '\n';
		return 0;
	}

	const int result = system( "git clone --depth=1 " REPO " template-cmake" );

	if ( result != 0 )
	{
		std::cout << "Failed to clone repo\n";
		return result;
	}

	const bool should_overwrite = arguments.contains( "--overwrite" );

	std::filesystem::remove_all( "template-cmake/.git" );

	std::vector<std::filesystem::path> files;

	const std::filesystem::recursive_directory_iterator it( "./template-cmake" );
	for ( const std::filesystem::path& path : it )
	{
		if ( std::filesystem::is_directory( path ) )
		{
			const std::filesystem::path dest = path.lexically_relative( "./template-cmake/" );
			std::filesystem::create_directories( dest );
		}
		else if ( path.filename() != ".gitignore" )
			files.emplace_back( path );
	}

	for ( const auto& path: files )
	{
		const std::filesystem::path dest = path.lexically_relative( "./template-cmake/" );
		bool should_move = true;

		if ( std::filesystem::exists( dest ) )
		{
			if ( !should_overwrite )
			{
				std::cout << "Skipping " << path.generic_string() << '\n';
				should_move = false;
			}
			else
				std::cout << "Overwriting " << path.generic_string() << '\n';
		}

		if ( should_move )
			std::filesystem::rename( path, dest );
	}

	std::filesystem::remove_all( "template-cmake/" );
}