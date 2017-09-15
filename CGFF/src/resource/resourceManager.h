#ifndef CGFF_RESOURCE_MANAGER_H
#define CGFF_RESOURCE_MANAGER_H

#include "resourceUnit.h"

namespace CGFF {
	class ResourceManger
	{
	public:
		ResourceManger() = delete;



	private:
		QSharedPointer<SceneReource> SceneReource;
	};
}

#endif