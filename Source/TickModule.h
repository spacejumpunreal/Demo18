#pragma once
#include "Demo18.h"
#include "IModule.h"

namespace Demo18
{
	struct ITickable
	{
		virtual void Tick() = 0;
	};
	struct TickModule : public IModule
	{
	public:
		virtual void AddTickable(ITickable* tickable) = 0;
		virtual void DelTickable(ITickable* tickable) = 0;
		template<typename Functor, typename... Args>
		inline void AddCallback(float delay, Args&&... args)
		{
			_AddCallback(delay, std::bind(std::forward<Args>(args)...));
		}
		virtual void Execute() = 0;
	private:
		virtual void _AddCallback(float delay, std::function<void()>&& f) = 0;
	};
	extern TickModule* CreateTickModule();
}
