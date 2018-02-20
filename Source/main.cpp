#include "Demo18.h"

#include "System.h"



int main()
{
	auto system = new Demo18::System();
	system->Initialize();
	system->SetFPS(30);
	system->Loop();
	return 0;
}