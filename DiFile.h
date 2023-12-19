#ifndef __DI_FILE_H__
#define __DI_FILE_H__

#include <string_view>
#include "DiFileInfo.h"
#include "DiFileInternal.h"

using DiFileData = di::file::internal::DiFileData;

namespace di
{
	namespace file
	{
		//RAII abstract base class for text and binary files storage
		class DiFile
		{
		public:
			DiFile() = delete;
			DiFile(std::string filePath, std::ios::openmode openMode= std::ios::in | std::ios::out|std::ios::binary) :
				m_fileInfo(filePath){
				m_fileData.openMode = openMode;
			}

			//Rule of five : 
			DiFile(const DiFile& other) = delete;
			DiFile& operator = (const DiFile& other) = delete;
			DiFile(const DiFile&& other) = delete;
			DiFile& operator = (const DiFile&& other) = delete;
			virtual ~DiFile();

		protected :
			virtual DiFileData getFileContent(void) = 0;
			[[noreturn]] virtual void setFileContent(DiFileData & data) = 0;

			DiFileInfo m_fileInfo;
			DiFileData m_fileData;
		};



	}
}
#endif


