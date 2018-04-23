#include "assets.h"
#include <iostream>

/*

To improve portability and convienence, this file contains three different implementations of accessing the Resource
folder, depending on platform and whether or not we are testing the code rather than building it for release.

The filesystem structure will change depending on where and how this is being compiled. In testing, we will see a structure such as:

MAINDIR
-/bin/
--etc
---/program
-/resources/
--/gfx/
--/sound/
--etc


While on MacOS, it will be like:

MAINDIR.app
-/Contents/
--/MacOS/
---/program
--/Resources/
---etc

And on windows, it might simply be

MAINDIR
-/program.exe
-/resources/
--etc

While on Windows and MacOS the structures will be the same each time, on testing the file structure relative to the
executable will be unpredictable, being highly dependent on the compiler. For this reason, we will dynamically
locate the location of the resources folder while in debug schemes.


*/

#define DEBUG //TODO: Remove this on release

namespace file
{
	std::string getCurrentWorkingDirectory()
	{
		return boost::filesystem::current_path().string();
	}

	boost::filesystem::path getCurrentWorkingDirectoryPath()
	{
		return boost::filesystem::current_path();
	}


	std::string getGraphic(std::string subdir)
	{
		return getResourceDirectory(boost::filesystem::path::preferred_separator + "gfx" + subdir);
	}

	boost::filesystem::path getGraphicPath(std::string subdir)
	{
		return getResourceDirectoryPath(boost::filesystem::path::preferred_separator + "gfx" + subdir);
	}


#ifdef DEBUG

	std::string getResourceDirectory(std::string subdir)
	{
		using namespace boost::filesystem;

		path current = getCurrentWorkingDirectoryPath();

		while (current.has_parent_path())
		{
			path resources = current / "resources";
			if (exists(resources))
			{
				return (resources / subdir).string();
			}

			current = current.parent_path();
		}
		throw MissingFileException();
	}

	boost::filesystem::path getResourceDirectoryPath(std::string subdir)
	{
		using namespace boost::filesystem;

		path current = getCurrentWorkingDirectoryPath();

		while (current.has_parent_path())
		{
			path resources = current / "resources" / subdir;
			if (exists(resources))
				return resources;

			current = current.parent_path();
		}
		throw MissingFileException();
	}

#elif WIN32

	std::string getResourceDirectory(std::string subdir)
	{
		return (getCurrentWorkingDirectoryPath() / "resources").string() + subdir;
	}

	boost::filesystem::path getResourceDirectoryPath(std::string subdir)
	{
		return getCurrentWorkingDirectoryPath() / "resources" + subdir;
	}


#elif __APPLE__

	std::string getResourceDirectory(std::string subdir)
	{
		using namespace boost::filesystem;

		path cwd = getCurrentWorkingDirectoryPath();

		path current = cwd.parent_path().parent_path();

		current /= "Resources";

		if (exists(current))
		{
			return current.string() + subdir;
		}
		throw MissingFileException();
	}

	boost::filesystem::path getResourceDirectoryPath(std::string subdir)
	{
		using namespace boost::filesystem;

		path cwd = getCurrentWorkingDirectoryPath();

		path current = cwd.parent_path().parent_path();

		current /= "Resources";

		if (exists(current))
		{
			return current + subdir;
		}
		throw MissingFileException();
	}

#endif

}
