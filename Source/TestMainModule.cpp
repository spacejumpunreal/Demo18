#include "TestMainModule.h"
#include "System.h"
#include "TickModule.h"
#include "WindowModule.h"

namespace Demo18
{
	struct TestMainModuleImp : public TestMainModule, public ITickable
	{
		TestMainModuleImp()
		{}
		virtual void InitializeModule()
		{
		}
		virtual void Start()
		{
			auto tick = GET_MODULE(Tick);
			tick->AddTickable(this);
			GET_MODULE(Window)->SetTitle(L"ABCD");
		}
		virtual void Tick()
		{
			
		}
	};
	TestMainModule* CreateTestMainModule()
	{
		return new TestMainModuleImp();
	}
}

