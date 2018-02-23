#pragma once
#include "Demo18.h"
#include "IModule.h"
#include "Container.h"

namespace Demo18
{
	struct FileModule : public IModule
	{
		virtual void SetBasePath(const char* path) = 0;
		virtual std::string GetNativePath(const char* path) = 0;
		virtual ByteBlob ReadFileContent(const char* path) = 0;
	};
	extern FileModule* CreateFileModule();
}