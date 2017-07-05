#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "graphic/batchRenderer2d.h"
#include "layer2D.h"


namespace CGFF {
	class TileLayer : public Layer2D
	{
	public:
		TileLayer(QSharedPointer<QOpenGLShaderProgram> shader, QMatrix4x4 projectionMatrix);

		virtual ~TileLayer();


	};
}

#endif