#ifndef SHADER_RESOURCE_H
#define SHADER_RESOURCE_H

#include "utils/qtopengl.h"

namespace CGFF {

    class ShaderResourceDeclaration
    {
    public:
        virtual const QString& getName() const = 0;
        virtual uint getRegister() const = 0;
        virtual uint getCount() const = 0;
    };

    typedef QVector<QSharedPointer<ShaderResourceDeclaration>> ShaderResourceList;
}

#endif