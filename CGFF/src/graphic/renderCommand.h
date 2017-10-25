#ifndef CGFF_RENDER_COMMAND_H
#define CGFF_RENDER_COMMAND_H

#include "utils/types.h"
//#include "mesh.h"

namespace CGFF {

	class Mesh;

    struct RenderCommand
    {
        QSharedPointer<Mesh> mesh;
        QMatrix4x4 transform;
        QVector4D color;
		QSharedPointer<Shader> shader;
    };
}

#endif
