#pragma once

#include "IModule.h"

namespace Demo18
{
	struct TestMainModule : public IModule
	{
	};
	extern TestMainModule* CreateTestMainModule();
}
