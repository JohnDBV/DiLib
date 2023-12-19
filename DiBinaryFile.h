#ifndef __DI_BINARY_FILE_H__
#define __DI_BINARY_FILE_H__

#include "DiFile.h"

using DiFileData = di::file::internal::DiFileData;

namespace di
{
	namespace file
	{
		//RAII abstract base class for text and binary files storage
		class DiBinaryFile : public DiFile
		{
		public:
			DiBinaryFile() = delete;
			DiBinaryFile(std::string filePath, std::ios::openmode openMode = std::ios::in | std::ios::out | std::ios::binary) :
				DiFile(filePath, openMode) {}

			//Rule of five : 
			DiBinaryFile(const DiFile& other) = delete;
			DiBinaryFile& operator = (const DiFile& other) = delete;
			DiBinaryFile(const DiFile&& other) = delete;
			DiBinaryFile& operator = (const DiFile&& other) = delete;
			~DiBinaryFile();

			DiFileInfo& getFileInfo();

			// Inherited via DiFile
			virtual DiFileData getFileContent() final;
			[[noreturn]] virtual void setFileContent(DiFileData& data) final;

			//This overload gets the file content using a custom open mode. One-time only
			DiFileData getFileContent(std::ios::openmode newOpenMode);
			//This overload writes the file content using a custom open mode. One-time only
			[[noreturn]] void setFileContent(DiFileData& data, std::ios::openmode newOpenMode);
		};



	}
}
#endif

