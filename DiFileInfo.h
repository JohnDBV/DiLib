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
			DiFileInfo() = default;

			explicit DiFileInfo(const char* filePath) : m_filePath(filePath != nullptr ? filePath : ""), m_path(filePath != nullptr ? filePath : "") {};
			explicit DiFileInfo(std::string filePath) : m_filePath(filePath), m_path(filePath) {};
			explicit DiFileInfo(std::string_view filePath) : m_filePath(filePath), m_path(filePath) {};
			
			//Rule of five : 
			DiFileInfo(const DiFileInfo& other);
			DiFileInfo& operator = (const DiFileInfo& other) = delete;
			DiFileInfo(const DiFileInfo&& other) = delete;
			DiFileInfo& operator = (const DiFileInfo&& other) = delete;
			~DiFileInfo();

			std::string getFileExtension();
			std::string  getFileNameWithExtension();
			std::string  getFileNameWithoutExtension();

			const std::string getFilePath();
			const std::string getFileFolder();

			void setFilePathTo(std::string const& newFilePath);
			void setFileExtensionTo(std::string const& newExtension);
			void setFileNameOnlyTo(std::string const& newFileName);

			bool exists();
			uint64_t getFileSize();

		private :

			std::string m_filePath;
			fs::path m_path;
		};

	}
}

#endif

