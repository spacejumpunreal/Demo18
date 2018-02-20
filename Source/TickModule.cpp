#include "Demo18.h"
#include "TickModule.h"
#include "System.h"
#include "Debug.h"

namespace Demo18
{
	struct TickModuleImp : public TickModule
	{
		TickModuleImp()
		{}
		virtual void AddTickable(ITickable* tickable)
		{
			DelTickable(tickable);
			mTickables.emplace_back(tickable);
		}
		virtual void DelTickable(ITickable* tickable)
		{
			mTickables.remove(tickable);
		}
		virtual void Execute()
		{
			for (auto i = mTickables.begin(); i != mTickables.end(); ++i)
			{
				(**i).Tick();
			}
		}
		virtual void _AddCallback(float delay, std::function<void()>&& f)
		{
			Check(false, "not implemented yet");
		}
	private:
		std::list<ITickable*> mTickables;
		std::map<float, std::function<void()>> mCallbacks;
	};

	TickModule* CreateTickModule()
	{
		return new TickModuleImp();
	}
}
