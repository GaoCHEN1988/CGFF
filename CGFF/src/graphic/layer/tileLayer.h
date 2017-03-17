#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "layer.h"
#include "batchRenderer2d.h"

namespace CGFF {
	class TileLayer : public Layer
	{
	public:
		TileLayer(QSharedPointer<QOpenGLShaderProgram> shader, QMatrix4x4 projectionMatrix);

		virtual ~TileLayer();


	};
}

#endif