#ifndef CGFF_SHADER_PROGRAM_H
#define CGFF_SHADER_PROGRAM_H

#include "utils/qtopengl.h"
#include <QOpenGLShaderProgram>

namespace CGFF {
    class ShaderProgram : public QOpenGLShaderProgram
    {
    public:
        ShaderProgram(QString name, QString vertexFile, QString fragmentFile);
        ~ShaderProgram() {}
        void reload();

        inline QString getName() 
        {
            return m_name;
        }

    private:
        void load();

    private:
        QString m_name;
        QString m_vertexFile;
        QString m_fragmentFile;
    };
}

#endif