#ifndef CGFF_ORTHORGRAPHIC_CAMERA_H
#define CGFF_ORTHORGRAPHIC_CAMERA_H

#include "camera.h"

namespace CGFF {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(const QMatrix4x4& projectionMatrix);
		virtual ~OrthographicCamera();
		void focus() override;
		void update() override;
	};

}

#endif