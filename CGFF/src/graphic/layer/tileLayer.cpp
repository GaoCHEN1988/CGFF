#include "tileLayer.h"

namespace CGFF {

	TileLayer::TileLayer(QSharedPointer<QOpenGLShaderProgram> shader, QMatrix4x4 projectionMatrix)
		: Layer(shader, QSharedPointer<Renderer2D>(new BatchRenderer2D()), projectionMatrix)
	{
	}

	TileLayer::~TileLayer() 
	{
	}

	

}