#include "TestMainModule.h"
#include "System.h"
#include "TickModule.h"
#include "WindowModule.h"
#include "FileModule.h"
#include "RendererModule.h"
#include "Camera.h"
#include "InputModule.h"

namespace Demo18
{
	struct TestMainModuleImp : public TestMainModule, public ITickable
	{
	public:
		TestMainModuleImp()
		{}
		virtual void InitializeModule()
		{
			mCPos = V3F(0, 0, -5);
			mCYaw = 0;
			mCPitch = 0;
		}
		virtual void Start()
		{
			auto tickM = GET_MODULE(Tick);
			tickM->AddTickable(this);
			GET_MODULE(Window)->SetTitle(L"ABCD");

			auto fileM = GET_MODULE(File);
		}
		virtual void Tick()
		{
			{//update camera
				auto inputM = GET_MODULE(Input);
				auto s = inputM->GetInputState();
				if (s.RButtonPressed)
				{
					const float vMove = 5.0f / 60.0f;
					const float vRotate = PI;
					V4F xyz[3];
					BuildAxis(mCPitch, mCYaw, xyz);
					for (int i = 0; i < 3; i++)
					{
						auto a = s.LeftPad.Data()[i];
						mCPos += vMove * a * xyz[i].xyz();
					}
					auto md = s.CurrentMouseCoord - s.LastMouseCoord;
					mCYaw += vRotate * md.x;
					mCPitch += vRotate * md.y;
					//printf("yaw--- radius: %.2f degree: %.2f\n", mCYaw, mCYaw * 180 / PI);
				}
				auto windowM = GET_MODULE(Window);
				auto ws = windowM->GetWindowSize();
				auto aspect = float(ws.x * 1.0 / ws.y);
				mScene.Camera.MWorld2View = CalcViewMatrix(mCPitch, mCYaw, mCPos);
				mScene.Camera.MPerspective = CalcPerspectiveMatrix(float(PI * 90 / 180), aspect, 0.1f, 200.f);
			}

			auto rendererM = GET_MODULE(Renderer);
			rendererM->RunRenderer(&mScene);
		}
	public:
		V3F mCPos;
		float mCYaw;
		float mCPitch;
		RendererScene mScene;

	};
	TestMainModule* CreateTestMainModule()
	{
		return new TestMainModuleImp();
	}
}

