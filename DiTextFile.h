#ifndef __DI_TEXT_FILE_H__
#define __DI_TEXT_FILE_H__

#include "DiFile.h"

using DiFileData = di::file::internal::DiFileData;

namespace di
{
	namespace file
	{
		//RAII abstract base class for text and binary files storage
		class DiTextFile : public DiFile
		{
		public:
			DiTextFile() = delete;
			DiTextFile(std::string filePath, std::ios::openmode openMode = std::ios::in | std::ios::out) :
				DiFile(filePath, openMode) {}

			//Rule of five : 
			DiTextFile(const DiFile& other) = delete;
			DiTextFile& operator = (const DiFile& other) = delete;
			DiTextFile(const DiFile&& other) = delete;
			DiTextFile& operator = (const DiFile&& other) = delete;
			~DiTextFile();

			DiFileInfo & getFileInfo();

			// Inherited via DiFile
			[[nodiscard]] virtual DiFileData getFileContent() final;
			[[noreturn]]  virtual void setFileContent(DiFileData& data) final;

			//This overload gets the file content using a custom open mode. One-time only
			[[nodiscard]] DiFileData getFileContent(std::ios::openmode newOpenMode);
			//This overload writes the file content using a custom open mode. One-time only
			[[noreturn]]  void setFileContent(DiFileData& data, std::ios::openmode newOpenMode);
		};



	}
}
#endif

