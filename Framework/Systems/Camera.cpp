#include "Framework.h"
#include "Camera.h"


void Camera::Update()
{
	UpdateView();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move(Vector2 size, Vector3 position)
{
	float x, y, z;
	if (position.x < (0.f + this->size.x / 2.f))
		x = 0.f + this->size.x / 2.f;
	else if (position.x > (size.x - this->size.x /2.f))
		x = size.x - this->size.x / 2.f;
	else
		x = position.x;

	if (position.y < (0.f + this->size.y / 2.f))
		y = 0.f + this->size.y / 2.f;
	else if (position.y > (size.y - this->size.y / 2.f))
		y = size.y - this->size.y / 2.f;
	else
		y = position.y;

	z = 0.f;

	SetPosition({ x, y, z });

}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + Values::FwdVec), &Values::UpVec);
	vpb->SetView(view);
}

void Camera::UnProjection(Vector3* out, Vector3 source, Matrix world)
{
	Vector3 position = source;

	out->x = (position.x * 2.0f / WinMaxWidth) - 1.f;
	out->y = (position.y * 2.0f / WinMaxHeight) - 1.f;
	out->z = position.z;

	Matrix wvp = world * view * proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);
	D3DXVec3TransformCoord(out, out, &wvp);
}

void Camera::SetCameraSize(Vector2 size)
{
	this->size = size;

	// projection 행렬
	{
		D3DXMatrixOrthoOffCenterLH
		(
			&proj,					// 투영
			0.0f,					// 왼쪽 면의 위치
			size.x,					// 오른쪽 면의 위치
			0.0f,					// 아래쪽 면의 위치
			size.y,					// 위쪽 면의 위치
			0,						// 가까운 면
			1						// 멀리 있는 면
		);

		vpb->SetView(view);
		vpb->SetProj(proj);
	}

	UpdateView();
}

void Camera::SetPosition(Vector3 Targetposition)
{
	position.x = Targetposition.x - size.x / 2.f;
	position.y = Targetposition.y - size.y / 2.f;
	position.z = Targetposition.z;

}

Camera::Camera()
{
	// 카메라 화면 크기 설정
	size = { WinMaxWidth / 1.9f, WinMaxHeight / 1.9f };

	// view, projection 버퍼 선언
	vpb = new VPBuffer;

	// view 행렬
	D3DXMatrixLookAtLH
	(
		&view,
		&Vector3(0, 0, 0),	// 카메라 위치
		&Vector3(0, 0, 1),	// 카메라가 바라보는 방향
		&Vector3(0, 1, 0)	// 카메라 위쪽 방향
	);

	// projection 행렬
	{
		D3DXMatrixOrthoOffCenterLH
		(
			&proj,					// 투영
			0.0f,					// 왼쪽 면의 위치
			size.x,					// 오른쪽 면의 위치
			0.0f,					// 아래쪽 면의 위치
			size.y,					// 위쪽 면의 위치
			0,						// 가까운 면
			1						// 멀리 있는 면
		);

		vpb->SetView(view);
		vpb->SetProj(proj);
	}


}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}
