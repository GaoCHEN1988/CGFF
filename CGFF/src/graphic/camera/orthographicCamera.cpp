#include "orthographicCamera.h"

namespace CGFF {

	OrthographicCamera::OrthographicCamera(const QMatrix4x4& projectionMatrix)
		: Camera(projectionMatrix)
	{

	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::focus()
	{
	}

	void OrthographicCamera::update()
	{
	}

}