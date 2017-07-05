#include "tileLayer.h"

namespace CGFF {

	TileLayer::TileLayer(QSharedPointer<QOpenGLShaderProgram> shader, QMatrix4x4 projectionMatrix)
		: Layer2D(QSharedPointer<BatchRenderer2D>(new BatchRenderer2D(QSize(0,0))), shader, /*QSharedPointer<Renderer2D>(new BatchRenderer2D()),*/ projectionMatrix)
	{
	}

	TileLayer::~TileLayer() 
	{
	}

	

}