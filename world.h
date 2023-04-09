#pragma once

FTransform boneid(DWORD_PTR mesh, int index)
{
	DWORD_PTR bonearray;

	bonearray = driver::read<DWORD_PTR>(mesh + 0x5C0);
	if (bonearray == NULL)
	{
		bonearray = driver::read<DWORD_PTR>(mesh + 0x5C0 + 0x10);
	}

	return driver::read<FTransform>(bonearray + (index * 0x60));

}
Vector3 bonerota(DWORD_PTR mesh, int id)
{
	FTransform bone = boneid(mesh, id);
	FTransform ComponentToWorld = driver::read<FTransform>(mesh + 0x240);
	D3DMATRIX Matrix;

	Matrix = matrixx(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}


static D3DMATRIX matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0)) {
	double radPitch = (rot.x * double(M_PI) / 180.f);
	double radYaw = (rot.y * double(M_PI) / 180.f);
	double radRoll = (rot.z * double(M_PI) / 180.f);

	double SP = sinf(radPitch);
	double CP = cosf(radPitch);
	double SY = sinf(radYaw);
	double CY = cosf(radYaw);
	double SR = sinf(radRoll);
	double CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}





//CamewaDescwipsion
struct Camera
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
};


struct FMinimalViewInfo
{
	Vector3 Location;//[Offset: 0x0, Size: 0xc]
	Vector3 Rotation;//[Offset: 0xc, Size: 0xc]
	float FOV;//[Offset: 0x18, Size: 0x4]
	float DesiredFOV;//[Offset: 0x1c, Size: 0x4]
	float OrthoWidth;//[Offset: 0x20, Size: 0x4]
	float OrthoNearClipPlane;//[Offset: 0x24, Size: 0x4]
	float OrthoFarClipPlane;//[Offset: 0x28, Size: 0x4]
	float AspectRatio;//[Offset: 0x2c, Size: 0x4]
	bool bConstrainAspectRatio;//(ByteOffset: 0, ByteMask: 1, FieldMask: 1)[Offset: 0x30, Size: 0x1]
	bool bUseFieldOfViewForLOD;//(ByteOffset: 0, ByteMask: 2, FieldMask: 2)[Offset: 0x30, Size: 0x1]
	float PostProcessBlendWeight;//[Offset: 0x38, Size: 0x4]
};


FMinimalViewInfo GetCamera(__int64 a1)
{
	FMinimalViewInfo FGC_Camera;
	__int64 v1;
	__int64 v6;
	__int64 v7;
	__int64 v8;
	v1 = driver::read<__int64>(offname::localactor + 0xd0);
	__int64 v9 = driver::read<__int64>(v1 + 0x8); // 0x10

	FGC_Camera.FOV = driver::read<float>(offname::controlactor + 0x38C) * 90.f;

	FGC_Camera.Rotation.x = driver::read<double>(v9 + 0x9C0);
	FGC_Camera.Rotation.y = driver::read<double>(a1 + 0x148);
	uint64_t FGC_Pointerloc = driver::read<uint64_t>(offname::uworld + 0x110);
	FGC_Camera.Location = driver::read<Vector3>(FGC_Pointerloc);

	return FGC_Camera;
}




Vector3 w2s(Vector3 WorldLocation)
{
	FMinimalViewInfo vCamera = GetCamera(offname::rootcomp);
	vCamera.Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / M_PI);

	D3DMATRIX tempMatrix = matrix(vCamera.Rotation);

	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FOV * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FOV * (float)M_PI / 360.f))) / vTransformed.z, 0);
}









void SetMouseAbsPosition(DWORD x, DWORD y)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = x;
	input.mi.dy = y;
	SendInput(1, &input, sizeof(input));
}




void aimbotaim(float x, float y)
{
	float center_x = (Width / 2);
	float center_y = (Height / 2);
	float smooth = features::aimspeed;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	SonyDriverHelper::api::MouseMove(target_x , target_y);


	return;
}


void aimbotaimrand(float x, float y)
{
	float center_x = (Width / 2);
	float center_y = (Height / 2);
	float smooth = features::aimspeed;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;

	float dx;
	float dy;

	dx = target_x / features::aimspeed;
	if (dx > 0.24 && dx < 1) dx = 1;
	if (dx < -0.24 && dx > -1) dx = -1;
	dy = target_y / features::aimspeed;
	if (dy > 0.24 && dy < 1) dy = 1;
	if (dy < -0.24 && dy > -1) dy = -1;

	Input.mi.dx = (LONG)dx;
	Input.mi.dy = (LONG)dy;


	if (PositiveCurve)
	{
		int absvalx = abs(Input.mi.dx);
		int absvaly = abs(Input.mi.dy);

		if (absvalx >= 32)
		{
			Input.mi.dx = Input.mi.dx + rand() % 31;
		}
		else if (absvalx > 16)
		{
			Input.mi.dx = Input.mi.dx + rand() % 18;
		}
		else if (absvalx > 8)
		{
			Input.mi.dx = Input.mi.dx + rand() % 14;
		}
		else if (absvalx > 3)
		{
			Input.mi.dx = Input.mi.dx + rand() % 12;
		}
		else if (absvalx > 1)
		{
			Input.mi.dx = Input.mi.dx + rand() % 11;
		}

		if (absvaly >= 32)
		{
			Input.mi.dy = Input.mi.dy + rand() % 31;
		}
		else if (absvaly > 16)
		{
			Input.mi.dy = Input.mi.dy + rand() % 18;
		}
		else if (absvaly > 8)
		{
			Input.mi.dy = Input.mi.dy + rand() % 14;
		}
		else if (absvaly > 3)
		{
			Input.mi.dy = Input.mi.dy + rand() % 12;
		}
		else if (absvaly > 1)
		{
			Input.mi.dy = Input.mi.dy + rand() % 11;
		}
	}
	else
	{
		int absvalx = abs(Input.mi.dx);
		int absvaly = abs(Input.mi.dy);

		if (absvalx >= 32)
		{
			Input.mi.dx = Input.mi.dx - rand() % 31;
		}
		else if (absvalx > 16)
		{
			Input.mi.dx = Input.mi.dx - rand() % 18;
		}
		else if (absvalx > 8)
		{
			Input.mi.dx = Input.mi.dx - rand() % 14;
		}
		else if (absvalx > 3)
		{
			Input.mi.dx = Input.mi.dx - rand() % 12;
		}
		else if (absvalx > 1)
		{
			Input.mi.dx = Input.mi.dx - rand() % 11;
		}

		if (absvaly >= 32)
		{
			Input.mi.dy = Input.mi.dy - rand() % 31;
		}
		else if (absvaly > 16)
		{
			Input.mi.dy = Input.mi.dy - rand() % 18;
		}
		else if (absvaly > 8)
		{
			Input.mi.dy = Input.mi.dy - rand() % 14;
		}
		else if (absvaly > 3)
		{
			Input.mi.dy = Input.mi.dy - rand() % 12;
		}
		else if (absvaly > 1)
		{
			Input.mi.dy = Input.mi.dy - rand() % 11;
		}
	}

	SonyDriverHelper::api::MouseMove(Input.mi.dx, Input.mi.dy);


	return;
}

void aimbotaim1(float x, float y)
{
	float center_x = (Width / 2);
	float center_y = (Height / 2);
	float smooth = aimbot1::aimspeed;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	SonyDriverHelper::api::MouseMove(target_x, target_y);

	return;
}


void aimbotaim2(float x, float y)
{
	float center_x = (Width / 2);
	float center_y = (Height / 2);

	float smooth = aimbot2::aimspeed;


	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	SonyDriverHelper::api::MouseMove(target_x, target_y);

	return;
}


void aimbotaim3(float x, float y)
{
	float center_x = (Width / 2);
	float center_y = (Height / 2);
	float smooth = aimbot3::aimspeed;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	SonyDriverHelper::api::MouseMove(target_x, target_y);
	return;
}


void aimbotaim4(float x, float y)
{
	float center_x = (Width / 2);
	float center_y = (Height / 2);
	float smooth = aimbot4::aimspeed;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	SonyDriverHelper::api::MouseMove(target_x, target_y);
	return;
}


Vector3 AimbotCorrection(float bulletVelocity, float bulletGravity, float targetDistance, Vector3 targetPosition, Vector3 targetVelocity) {
	Vector3 recalculated = targetPosition;
	float gravity = fabs(bulletGravity);
	float time = targetDistance / fabs(bulletVelocity);
	float bulletDrop = (gravity / 250) * time * time;
	recalculated.z += bulletDrop * 120;
	recalculated.x += time * (targetVelocity.x);
	recalculated.y += time * (targetVelocity.y);
	recalculated.z += time * (targetVelocity.z);
	return recalculated;
}


double GetCrossDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}


void targetbone(DWORD_PTR entity)
{
	uint64_t currentactormesh = driver::read<uint64_t>(entity + Offsets::External::MESH);
	auto rootHead = bonerota(currentactormesh, features::hitbox);
	auto CurrentWeapon = driver::read<uintptr_t>(offname::localactorpawn + Offsets::External::CURRWEAPON);
	auto pawnWeaponID = driver::read<uint32_t>(CurrentWeapon + 0x18);
	Vector3 rootHeadOut = w2s(rootHead);
	if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
		    if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= features::fov * 1)) {

			if (features::univaimbot) {
						aimbotaim(rootHeadOut.x, rootHeadOut.y);
			}
			else
			{
				if (features::weaponaimbot)
				{
				}
				if (features::rifleaiming) {
					aimbotaim1(rootHeadOut.x, rootHeadOut.y);
				}
				if (features::shotgunaiming)
				{
					aimbotaim2(rootHeadOut.x, rootHeadOut.y);
				}
				if (features::smgaiming)
				{
					aimbotaim3(rootHeadOut.x, rootHeadOut.y);
				}
				if (features::sniperaiming)
				{
					aimbotaim4(rootHeadOut.x, rootHeadOut.y);
				}
			}
		}
	}
}

