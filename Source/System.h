#pragma once

namespace Demo18
{
	class IModule;
	class System
	{
		struct SystemImp;
	public:
		System();
		void Initialize();
		IModule* GetModule(const char* name);
		void SetFPS(float fps);
		void Loop();
	private:
		SystemImp*			mImp;
	};
	extern System* GSystem;

	template<typename ModuleType>
	ModuleType* GetModule(const char* name)
	{
		return dynamic_cast<ModuleType*>(GSystem->GetModule(name));
	}
}
# define GET_MODULE(TYPE) (Demo18::GetModule<TYPE##Module>(#TYPE))