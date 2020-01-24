#ifndef _IMGUIZMO_MANAGER_H
#define _IMGUIZMO_MANAGER_H

#include "..//Dep/Imgui/ImGuizmo.h"

class ImGuizmoManager final
{
private:
	ImGuizmo::OPERATION _mCurrentGizmoOperation;

	size_t _pickUId;

	float _windowWidth;
	float _windowHeight;

	bool _dragCamera;

	Vector3 _prevPos;
	Vector3 _currPos;

public:
	ImGuizmoManager() :_mCurrentGizmoOperation{ImGuizmo::TRANSLATE}, _pickUId{ 0 }, _windowWidth{ 1280 }, _windowHeight{ 1024 }, _dragCamera{ true }, _prevPos{ 0,0,1 }, _currPos{ 0,0,1 } {}
	~ImGuizmoManager() {}

	void Update();
	void Draw();

	void SetPickObjectUId(size_t uId);

	void SetWindowSize(float width, float height);

private:

	void RenderToolBar();

	void EditTransform(const float* cameraView, float* cameraProjection, float* matrix);

	void OrthoGraphic(const float l, float r, float b, const float t, float zn, const float zf, float* m16)
	{
		m16[0] = 2 / (r - l);
		m16[1] = 0.0f;
		m16[2] = 0.0f;
		m16[3] = 0.0f;
		m16[4] = 0.0f;
		m16[5] = 2 / (t - b);
		m16[6] = 0.0f;
		m16[7] = 0.0f;
		m16[8] = 0.0f;
		m16[9] = 0.0f;
		m16[10] = 1.0f / (zf - zn);
		m16[11] = 0.0f;
		m16[12] = (l + r) / (l - r);
		m16[13] = (t + b) / (b - t);
		m16[14] = zn / (zn - zf);
		m16[15] = 1.0f;
	}


	void Cross(const float* a, const float* b, float* r)
	{
		r[0] = a[1] * b[2] - a[2] * b[1];
		r[1] = a[2] * b[0] - a[0] * b[2];
		r[2] = a[0] * b[1] - a[1] * b[0];
	}

	float Dot(const float* a, const float* b)
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	}

	void Normalize(const float* a, float* r)
	{
		float il = 1.f / (sqrtf(Dot(a, a)) + FLT_EPSILON);
		r[0] = a[0] * il;
		r[1] = a[1] * il;
		r[2] = a[2] * il;
	}

	void LookAt(const float* eye, const float* at, const float* up, float* m16)
	{
		float X[3], Y[3], Z[3], tmp[3];

		tmp[0] = eye[0] - at[0];
		tmp[1] = eye[1] - at[1];
		tmp[2] = eye[2] - at[2];
		//Z.normalize(eye - at);
		Normalize(tmp, Z);
		Normalize(up, Y);
		//Y.normalize(up);

		Cross(Y, Z, tmp);
		//tmp.cross(Y, Z);
		Normalize(tmp, X);
		//X.normalize(tmp);

		Cross(Z, X, tmp);
		//tmp.cross(Z, X);
		Normalize(tmp, Y);
		//Y.normalize(tmp);

		m16[0] = X[0];
		m16[1] = Y[0];
		m16[2] = Z[0];
		m16[3] = 0.0f;
		m16[4] = X[1];
		m16[5] = Y[1];
		m16[6] = Z[1];
		m16[7] = 0.0f;
		m16[8] = X[2];
		m16[9] = Y[2];
		m16[10] = Z[2];
		m16[11] = 0.0f;
		m16[12] = -Dot(X, eye);
		m16[13] = -Dot(Y, eye);
		m16[14] = -Dot(Z, eye);
		m16[15] = 1.0f;
	}

};

#endif
