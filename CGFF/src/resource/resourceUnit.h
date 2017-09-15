#ifndef CGFF_RESOURCE_UNIT_H
#define CGFF_RESOURCE_UNIT_H

#include "graphic/meshFactory.h"
#include "graphic/model.h"
#include "entity/entity.h"
#include "graphic/pbrMaterial.h"
#include "graphic/shader/shaderManager.h"
#include "graphic/light.h"

namespace CGFF
{
	struct ResourceUnit
	{
		QSharedPointer<Mesh> materialInstance;
		QSharedPointer<Material> material;
		QMatrix4x4 transform;
		ResourceUnit()
			: materialInstance(nullptr)
			, material(nullptr)
			, transform()
		{}
	};

	struct SceneReource
	{
		QSharedPointer<Camera> camera;
		QVector<QSharedPointer<ResourceUnit>> resUnits;
		QVector<QSharedPointer<Light>> lights;
		QSharedPointer<Material> skyBox;

		SceneReource()
			: camera(nullptr)
			, resUnits()
			, lights()
			, skyBox(nullptr)
		{}
	};
}

#endif