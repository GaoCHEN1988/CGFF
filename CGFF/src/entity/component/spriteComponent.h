#ifndef CGFF_SPRITE_COMPONENTS_H
#define CGFF_SPRITE_COMPONENTS_H

#include "maths/qtmaths.h"
#include "component.h"
#include "graphic/sprite.h"

namespace CGFF {

	class SpriteComponent : public Component
	{

	public:
		SpriteComponent(QSharedPointer<Sprite> sprite);

		static ComponentType* getStaticType()
		{
			static ComponentType type({ "Sprite" });
			return &type;
		}

		inline virtual ComponentType* getType() const override { return getStaticType(); }

	public:
		QSharedPointer<Sprite> sprite;
	};
}

#endif
