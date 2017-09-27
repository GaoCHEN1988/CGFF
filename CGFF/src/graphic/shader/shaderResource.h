#ifndef CGFF_SHADER_RESOURCE_H
#define CGFF_SHADER_RESOURCE_H

#include "utils/qtopengl.h"

namespace CGFF {

    class ShaderResourceDeclaration
    {
	public:
		enum class Type
		{
			NONE,
			TEXTURE2D,
			TEXTURECUBE,
			TEXTURESHADOW
		};

    public:
        virtual QString getName() const = 0;
        virtual uint getRegister() const = 0;
        virtual uint getCount() const = 0;
		virtual Type getType() const = 0;
    };

    typedef QVector<QSharedPointer<ShaderResourceDeclaration>> ShaderResourceList;
}

#endif