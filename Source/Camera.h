#pragma once

#include "Math.h"
#include "Utils.h"

namespace Demo18
{
	struct RendererCamera
	{
		M44F MWorld2View;
		M44F MPerspective;
		bool IsPerspecive()
		{
			return
				MPerspective.m[2][2] == 1 &&
				MPerspective.m[2][3] == 0 &&
				MPerspective.m[3][2] == 0 &&
				MPerspective.m[3][3] == 1;
		}
	};
	inline M44F CalcViewMatrix(float pitch, float yaw, V3F pos)
	{
		/*
			Pv * Axisv = Pw * Identity
			=>
			Pv = Pw * inv(Axisv)

			Axisv = RotateX * RotateY * Translation
		*/
		auto m = 
			M44F::Translate(V3F(-pos.x, -pos.y, -pos.z)) *
			M44F::RotateY(-yaw) *
			M44F::RotateX(-pitch);
		return m;
	}
	inline void BuildAxis(float pitch, float yaw, V4F xyz[3])
	{
		auto m = M44F::RotateX(pitch) * M44F::RotateY(yaw);
		Copy(&m, xyz, sizeof(V4F[3]));
	}
	inline M44F CalcPerspectiveMatrix(float fovY, float aspect, float zNear, float zFar)
	{
		auto r = M44F::Identity(0);
		float yScale = Cot(fovY / 2);
		float xScale = yScale / aspect;
		r.m[0][0] = xScale;
		r.m[1][1] = yScale;
		r.m[2][2] = zFar / (zFar - zNear);
		r.m[2][3] = 1.0f;
		r.m[3][2] = -zFar * zNear / (zFar - zNear);
		return r;
	}
}