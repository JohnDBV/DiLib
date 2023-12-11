#ifndef __DI_FILE_INTERNAL_H__
#define __DI_FILE_INTERNAL_H__

#include <memory>
#include <fstream>
#include <vector>

namespace di
{
	namespace file
	{
		namespace internal
		{
			using BinaryDataPair = std::pair<uint64_t, std::unique_ptr<uint8_t[]>>;

			//Generic data storage class for file data
			struct DiFileData
			{
				DiFileData();

				DiFileData(const DiFileData& other);
				const DiFileData& operator = (const DiFileData& other);//rvalue
				DiFileData(const DiFileData&& other) = delete;
				DiFileData& operator = (const DiFileData&& other) = delete;
				~DiFileData();


				bool isBinaryModeOpened() const;
				bool canRead() const;
				bool canWrite() const;

				//Stores the OpenMode
				std::ios::openmode openMode;

				//Stores an ASCII vector of data
				std::vector<uint8_t> textData;
				
				//Stores binary data in a pair of <size,bytes>
				BinaryDataPair binaryData;
			};

			//another class/struct/definition here...
		}

	}
}
#endif


