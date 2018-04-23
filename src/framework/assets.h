#pragma once

#include "string"
#include "Exception.h"
#include <boost/filesystem.hpp>


namespace file
{
	
	class FileException : public Exception
	{
	public:
		FileException(int code=3, std::string value="FileException Generic") : Exception(3, value)
		{
		}
		
		
	};
	
	
	class MissingFileException : public FileException
	{
	public:
		MissingFileException(int code=4, std::string value="Generic") : FileException(code, "Could not find file: "+value)
		{
			
		}
	};
	
	
	/* Returns the program's current working directory
	 */
	std::string getCurrentWorkingDirectory();
	
	
	boost::filesystem::path getCurrentWorkingDirectoryPath();
	
	
	/* Returns the program's Resource directory, plus the subdirectory argument
	 *
	 * @param subdir The subdirectory within the Resource folder to return. This is appended to the end of the Resource directory path
	 */
	std::string getResourceDirectory(std::string subdir="");
	
	boost::filesystem::path getResourceDirectoryPath(std::string subdir="");
	
	
	/* Returns the program's gfx directory, plus the subdirectory supplied
	 *
	 * @param subdir The subdirectory within the gfx folder to rerturn. This is appended to the end of the gfx directory path
	 */
	std::string getGraphic(std::string subdir="");
	
	boost::filesystem::path getGraphicPath(std::string subdir="");

}
