#ifndef __DI_FILE_INFO_H__
#define __DI_FILE_INFO_H__

#include <string>
#include <string_view>
#include <stdint.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace di
{
	namespace file
	{
		//std::filesystem utilities used here, when possible.
		class DiFileInfo
		{
		public :
			DiFileInfo() = delete;//no copy & move semantics also *

			explicit DiFileInfo(const char* filePath) : m_filePath(filePath != nullptr ? filePath : ""), m_path(filePath != nullptr ? filePath : "") {};
			explicit DiFileInfo(std::string filePath) : m_filePath(filePath), m_path(filePath) {};
			explicit DiFileInfo(std::string_view filePath) : m_filePath(filePath), m_path(filePath) {};
			
			//Rule of five : 
			DiFileInfo(const DiFileInfo& other) = delete;
			DiFileInfo& operator = (const DiFileInfo& other) = delete;
			DiFileInfo(const DiFileInfo&& other) = delete;
			DiFileInfo& operator = (const DiFileInfo&& other) = delete;
			~DiFileInfo();

			//must apply transform(), so we pass a copy of the transformed local object :
			std::string getFileExtension();
			//must return a copy of a substring, so we pass a copy of the object :
			std::string  getFileNameWithExtension();
			//must return a copy of a substring, so we pass a copy of the object :
			std::string  getFileNameWithoutExtension();

			//'views' m_filePath -> no memory copy
			std::string_view getFilePath();
			//views data from the member std::filesystem::path -> no memory copy
			std::string_view getFileFolder();

			void setFilePathTo(std::string_view newFilePath);

			bool exists();
			uint64_t getFileSize();

		private :

			std::string m_filePath;
			fs::path m_path;
		};

	}
}

#endif

