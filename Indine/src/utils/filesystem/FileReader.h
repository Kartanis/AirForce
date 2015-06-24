#pragma once
#ifdef FILE_READER_DLL_EXPORTS
#define FILE_READER_DLL_API __declspec(dllexport) 
#else
#define FILE_READER_DLL_API __declspec(dllimport) 
#endif

namespace FileSystem {
	class FileReader
	{
	public:
		FileReader();
		~FileReader();
		bool static FILE_READER_DLL_API read();
	};

}