#include "FileModule.h"
#include "Container.h"
#include "Debug.h"

namespace Demo18
{
	class FileModuleImp : public FileModule
	{
	public:
		virtual void SetBasePath(const char* path) override
		{
			mBasePath = path;
			while (
				(mBasePath.back() == '/' || mBasePath.back() == '\\') &&
				(mBasePath.size() > 0))
			{
				mBasePath.pop_back();
			}
			mBasePath.push_back('/');
		}
		virtual void InitializeModule()
		{
			mBasePath = "Resource";
		}
		virtual std::string GetNativePath(const char* path)
		{
			return _GetNativePath(path);
		}
		inline std::string _GetNativePath(const char* path)
		{
			return mBasePath + "/" + path;
		}
		virtual ByteBlob ReadFileContent(const char* path)
		{
			auto pth = GetNativePath(path);
			std::ifstream fs(pth, std::ios::binary | std::ios::ate);
			Check(fs.is_open());
			auto ed = fs.tellg();
			fs.seekg(0, std::ios::beg);
			auto todo = ed - fs.tellg();
			ByteBlob blob(todo);
			auto rp = (char*)&blob[0];
			while (todo > 0)
			{
				fs.read(rp, todo);
				todo -= fs.gcount();
				Check(fs.good());
			}
			return blob;
		}
	protected:
		std::string mBasePath;
	};
	FileModule* CreateFileModule()
	{
		return new FileModuleImp();
	}
}