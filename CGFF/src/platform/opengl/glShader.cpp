#include "glShader.h"
//#include <QFile>
#include "glShaderPareser.h"
#include "system/fileSystem/vfs.h"
namespace CGFF {

    GLShader::GLShader(const QString& name)
        : m_name(name)
        , m_vertexFile("")
        , m_fragmentFile("")
        , m_vertexSource("")
        , m_fragmentSource("")
        , m_geometryFile("")
        , m_geometrySource("")
        , m_glShaderProgram()
    {
    }
    GLShader::~GLShader()
    {
    }

    void GLShader::createFromFile(const QString& vertexFile, const QString& fragmentFile, const QString& geometryFile)
    {
        m_glShaderProgram.removeAllShaders();
        m_vertexFile = vertexFile;
        m_fragmentFile = fragmentFile;
        m_geometryFile = geometryFile;

        m_vertexSource.clear();
        m_vertexSource = VFS::get()->readTextFile(vertexFile);

        m_fragmentSource.clear();
        m_fragmentSource = VFS::get()->readTextFile(fragmentFile);

        if (!m_geometryFile.isEmpty())
        {
            m_geometrySource.clear();
            m_geometrySource = VFS::get()->readTextFile(m_geometryFile);
        }

        load();
        init();
    }

    void GLShader::createFromSource(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource)
    {
        m_glShaderProgram.removeAllShaders();
        m_vertexSource = vertexSource;
        m_fragmentSource = fragmentSource;
        m_geometrySource = geometrySource;

        load();
        init();
    }

    void GLShader::init()
    {
        m_VSUserUniformBuffer = nullptr;
        m_PSUserUniformBuffer = nullptr;

        parse(m_vertexSource, m_fragmentSource, m_geometrySource);
        resolveUniforms();
    }

    void GLShader::close()
    {
        m_glShaderProgram.removeAllShaders();
        m_vertexFile = "";
        m_fragmentFile = "";
        m_geometryFile = "";
        m_vertexSource = "";
        m_fragmentSource = "";
        m_geometrySource = "";
    }

    void GLShader::bind()
    {
        m_glShaderProgram.bind();
        s_currentlyBound = this;
    }

    void GLShader::unBind()
    {
        m_glShaderProgram.release();
        s_currentlyBound = nullptr;
    }

    void GLShader::reload()
    {
        m_glShaderProgram.removeAllShaders();
        load();
    }

    void GLShader::setVSSystemUniformBuffer(uchar* data, uint size, uint slot)
    {
        bind();
        Q_ASSERT(m_VSUniformBuffers.size() > slot);
        QSharedPointer<ShaderUniformBufferDeclaration> declaration = m_VSUniformBuffers[slot];
        resolveAndSetUniforms(declaration, data);
    }

    void GLShader::setPSSystemUniformBuffer(uchar* data, uint size, uint slot)
    {
        bind();
        Q_ASSERT(m_PSUniformBuffers.size() > slot);
        QSharedPointer<ShaderUniformBufferDeclaration> declaration = m_PSUniformBuffers[slot];
        resolveAndSetUniforms(declaration, data);
    }

    void GLShader::setVSUserUniformBuffer(uchar* data, uint size)
    {
        resolveAndSetUniforms(m_VSUserUniformBuffer, data);
    }

    void GLShader::setPSUserUniformBuffer(uchar* data, uint size)
    {
        resolveAndSetUniforms(m_PSUserUniformBuffer, data);
    }

    void GLShader::setUniform(const QString& name, uchar* data)
    {
        QSharedPointer<ShaderUniformDeclaration> uniform = findUniformDeclaration(name);
        if (uniform.isNull())
        {
            qFatal("Cannot find uniform in ", m_name, " shader with name '", name, "'");
            return;
        }
        resolveAndSetUniform(qSharedPointerCast<GLShaderUniformDeclaration>(uniform), data);
    }

    void GLShader::resolveAndSetUniformField(const QSharedPointer<GLShaderUniformDeclaration>& field, uchar* data, int offset)
    {
        switch (field->getType())
        {
        case GLShaderUniformDeclaration::Type::GLboolean:
        {
            m_glShaderProgram.setUniformValue(field->getLocation(), *(GLboolean *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::GLfloat:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (GLfloat *)&data[offset], field->getCount(), 4);
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(GLfloat *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::GLint:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (GLint *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(GLint *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::GLuint:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (GLuint *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(GLuint *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::QVector2D:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (QVector2D *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(QVector2D *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::QVector3D:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (QVector3D *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(QVector3D *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QVector4D:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (QVector4D *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(QVector4D *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::QMatrix2x2:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (QMatrix2x2 *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(QMatrix2x2 *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QMatrix3x3:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (QMatrix3x3 *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(QMatrix3x3 *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::QMatrix4x4:
        {
            if (field->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(field->getLocation(), (QMatrix4x4 *)&data[offset], field->getCount());
            else
                m_glShaderProgram.setUniformValue(field->getLocation(), *(QMatrix4x4 *)&data[offset]);

            break;
        }
        default:
            qFatal("Unknown type!");
        }
    }

    void GLShader::load()
    {
        if (!m_glShaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, m_vertexSource))
            qFatal(QString("Error:Can't compile vertex shader:\n" + m_vertexFile + "\n" + m_glShaderProgram.log()).toStdString().c_str());
        if (!m_glShaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, m_fragmentSource))
            qFatal(QString("Error:Can't compile fragment shader:\n" + m_fragmentFile + "\n" + m_glShaderProgram.log()).toStdString().c_str());
        if (!m_geometrySource.isEmpty())
        {
            if (!m_glShaderProgram.addShaderFromSourceCode(QOpenGLShader::Geometry, m_geometrySource))
                qFatal(QString("Error:Can't compile geometry shader:\n"+ m_geometryFile + "\n" + m_glShaderProgram.log()).toStdString().c_str());
        }

        if (!m_glShaderProgram.link())
            qFatal(QString("Error:Can't link shaders:\n" + m_glShaderProgram.log()).toStdString().c_str());
    }

    QSharedPointer<ShaderUniformDeclaration> GLShader::findUniformDeclaration(const QString& name, QSharedPointer<ShaderUniformBufferDeclaration> buffer)
    {
        const ShaderUniformList& uniforms = buffer->getUniformDeclarations();
        for (uint i = 0; i < uniforms.size(); i++)
        {
            if (uniforms[i]->getName() == name)
                return uniforms[i];
        }
        return nullptr;
    }

    QSharedPointer<ShaderUniformDeclaration> GLShader::findUniformDeclaration(const QString& name)
    {
        QSharedPointer<ShaderUniformDeclaration> result = nullptr;
        for (uint i = 0; i < m_VSUniformBuffers.size(); i++)
        {
            result = findUniformDeclaration(name, m_VSUniformBuffers[i]);
            if (!result.isNull())
                return result;
        }

        for (uint i = 0; i < m_PSUniformBuffers.size(); i++)
        {
            result = findUniformDeclaration(name, m_PSUniformBuffers[i]);
            if (!result.isNull())
                return result;
        }

        result = findUniformDeclaration(name, m_VSUserUniformBuffer);
        if (!result.isNull())
            return result;

        result = findUniformDeclaration(name, m_PSUserUniformBuffer);
        if (!result.isNull())
            return result;

        return result;
    }

    void GLShader::resolveAndSetUniforms(const QSharedPointer<ShaderUniformBufferDeclaration>& buffer, uchar* data)
    {
        const ShaderUniformList& uniforms = buffer->getUniformDeclarations();
        for (uint i = 0; i < uniforms.size(); i++)
        {
            QSharedPointer<GLShaderUniformDeclaration> uniform = qSharedPointerCast<GLShaderUniformDeclaration>(uniforms[i]);
            resolveAndSetUniform(uniform, data);
        }
    }

    void GLShader::resolveAndSetUniform(const QSharedPointer<GLShaderUniformDeclaration>& uniform, uchar* data)
    {
        if (uniform->getLocation() == -1)
            return;

        uint offset = uniform->getOffset();

        switch (uniform->getType())
        {
        case GLShaderUniformDeclaration::Type::GLboolean:
        {
            m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLboolean *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::GLfloat:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (GLfloat *)&data[offset], uniform->getCount(), 4);
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLfloat *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::GLint:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (GLint *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLint *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::GLuint:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (GLuint *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(GLuint *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QVector2D:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (QVector2D *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QVector2D *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QVector3D:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (QVector3D *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QVector3D *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QVector4D:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (QVector4D *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QVector4D *)&data[offset]);
            break;
        }
        case GLShaderUniformDeclaration::Type::QMatrix2x2:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (QMatrix2x2 *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix2x2 *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QMatrix3x3:
        {
            if (uniform->getCount() > 1)
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (QMatrix3x3 *)&data[offset], uniform->getCount());
            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix3x3 *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::QMatrix4x4:
        {
            if (uniform->getCount() > 1)
            {
                m_glShaderProgram.setUniformValueArray(uniform->getLocation(), (QMatrix4x4 *)&data[offset], uniform->getCount());
            }

            else
                m_glShaderProgram.setUniformValue(uniform->getLocation(), *(QMatrix4x4 *)&data[offset]);

            break;
        }
        case GLShaderUniformDeclaration::Type::STRUCT:
        {
            if (uniform->getCount() > 1)
                setUniformStructList(uniform, data, offset);
            else
                setUniformStruct(uniform, data, offset);

            break;
        }
        default:
            qFatal("Unknown uniform type!");
        }
    }

    void GLShader::setUniformStruct(const QSharedPointer<GLShaderUniformDeclaration>& uniform, uchar* data, int offset)
    {
        const QSharedPointer<ShaderStruct>& s = uniform->getShaderUniformStruct();
        const auto& fields = s->getFields();
        for (uint k = 0; k < fields.size(); k++)
        {
            QSharedPointer<GLShaderUniformDeclaration> field = qSharedPointerCast<GLShaderUniformDeclaration>(fields[k]);
            resolveAndSetUniformField(field, data, offset);
            offset += field->getSize();
        }
    }

    void GLShader::setUniformStructList(const QSharedPointer<GLShaderUniformDeclaration>& uniform, uchar* data, int offset)
    {
        for (int i = 0; i < uniform->getCount(); i++)
        {
            const QSharedPointer<ShaderStruct>& s = uniform->getShaderUniformStruct(i);
            const auto& fields = s->getFields();
            for (uint k = 0; k < fields.size(); k++)
            {
                QSharedPointer<GLShaderUniformDeclaration> field = qSharedPointerCast<GLShaderUniformDeclaration>(fields[k]);
                resolveAndSetUniformField(field, data, offset);
                offset += field->getSize();
            }
        }
    }

    void GLShader::parse(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource)
    {
        m_VSUniformBuffers.push_back(QSharedPointer<GLShaderUniformBufferDeclaration>(new GLShaderUniformBufferDeclaration("Global", ShaderType::VERTEX)));
        m_PSUniformBuffers.push_back(QSharedPointer<GLShaderUniformBufferDeclaration>(new GLShaderUniformBufferDeclaration("Global", ShaderType::FRAGMENT)));

        QStringList tokens;

        // Vertex Shader
        tokens = GLShaderParser::findStructs(vertexSource);
        for (QString s : tokens)
        {
            parseUniformStruct(s, ShaderType::VERTEX);
        }

        tokens = GLShaderParser::findUniforms(vertexSource);
        for (QString s : tokens)
        {
            parseUniform(s, ShaderType::VERTEX);
        }

        // Fragment Shader
        tokens = GLShaderParser::findStructs(fragmentSource);
        for (QString s : tokens)
        {
            parseUniformStruct(s, ShaderType::FRAGMENT);
        }

        tokens = GLShaderParser::findUniforms(fragmentSource);
        for (QString s : tokens)
        {
            parseUniform(s, ShaderType::FRAGMENT);
        }

        //Geometry Shader
        if (!geometrySource.isEmpty())
        {
            tokens = GLShaderParser::findUniforms(geometrySource);
            for (QString s : tokens)
            {
                parseUniform(s, ShaderType::GEOMETRY);
            }
        }
    }

    void GLShader::parseUniform(const QString& statement, ShaderType shaderType)
    {
        QString typeString;
        QString name;
        int count;

        GLShaderParser::seperateTokenStatement(statement, typeString, name, count);

        if (isTypeStringResource(typeString))
        {
            QSharedPointer<ShaderResourceDeclaration> declaration = QSharedPointer<ShaderResourceDeclaration>(new
                GLShaderResourceDeclaration(GLShaderResourceDeclaration::stringToType(typeString), name, count));
            m_resources.push_back(declaration);
        }
        else
        {
            GLShaderUniformDeclaration::Type t = GLShaderUniformDeclaration::stringToType(typeString);
            QSharedPointer<GLShaderUniformDeclaration> declaration = nullptr;

            if (t == GLShaderUniformDeclaration::Type::NONE)
            {
                // Find struct
                QSharedPointer<ShaderStruct> s = findStruct(typeString);
                Q_ASSERT(!s.isNull());
                declaration = QSharedPointer<GLShaderUniformDeclaration>(new GLShaderUniformDeclaration(s, name, count));
            }
            else
            {
                declaration = QSharedPointer<GLShaderUniformDeclaration>(new GLShaderUniformDeclaration(t, name, count));
            }

            if (name.indexOf("sys_") == 0)
            {
                if (shaderType == ShaderType::VERTEX)
                    (qSharedPointerCast<GLShaderUniformBufferDeclaration>(m_VSUniformBuffers.front()))->pushUniform(declaration);
                else if (shaderType == ShaderType::FRAGMENT)
                    (qSharedPointerCast<GLShaderUniformBufferDeclaration>(m_PSUniformBuffers.front()))->pushUniform(declaration);
            }
            else
            {
                if (shaderType == ShaderType::VERTEX)
                {
                    if (m_VSUserUniformBuffer == nullptr)
                        m_VSUserUniformBuffer = QSharedPointer<GLShaderUniformBufferDeclaration>(new GLShaderUniformBufferDeclaration("", ShaderType::VERTEX));

                    m_VSUserUniformBuffer->pushUniform(declaration);
                }
                else if (shaderType == ShaderType::FRAGMENT)
                {
                    if (m_PSUserUniformBuffer == nullptr)
                        m_PSUserUniformBuffer = QSharedPointer<GLShaderUniformBufferDeclaration>(new GLShaderUniformBufferDeclaration("", ShaderType::FRAGMENT));

                    m_PSUserUniformBuffer->pushUniform(declaration);
                }
                else if (shaderType == ShaderType::GEOMETRY)
                {
                    if (m_PSUserUniformBuffer == nullptr)
                        m_PSUserUniformBuffer = QSharedPointer<GLShaderUniformBufferDeclaration>(new GLShaderUniformBufferDeclaration("", ShaderType::FRAGMENT));

                    m_PSUserUniformBuffer->pushUniform(declaration);
                }
            }
        }
    }

    void GLShader::parseUniformStruct(const QString& block, ShaderType shaderType)
    {
        QString structName;
        QStringList structs = GLShaderParser::seperateStructStatement(block, structName);

        QSharedPointer<ShaderStruct> uniformStruct = QSharedPointer<ShaderStruct>(new ShaderStruct(structName));

        for (QString s : structs)
        {
            QString typeString;
            QString name;
            int count;
            GLShaderParser::seperateTokenStatement(s, typeString, name, count);

            QSharedPointer<ShaderUniformDeclaration> field = QSharedPointer<ShaderUniformDeclaration>(
                new GLShaderUniformDeclaration(GLShaderUniformDeclaration::stringToType(typeString), name, count));
            uniformStruct->addField(field);
        }

        m_structs.push_back(uniformStruct);
    }

    bool GLShader::isTypeStringResource(const QString& type)
    {
        if (type == "sampler2D")		return true;
        if (type == "samplerCube")		return true;
        if (type == "sampler2DShadow")	return true;
        return false;
    }

    QSharedPointer<ShaderStruct> GLShader::findStruct(const QString& name)
    {
        for (QSharedPointer<ShaderStruct> s : m_structs)
        {
            if (s->getName() == name)
                return s;
        }
        return nullptr;
    }

    void GLShader::resolveUniformLists(const ShaderUniformList& uniformBufferList)
    {
        for (uint i = 0;  i< uniformBufferList.size(); i++)
        {
            QSharedPointer<GLShaderUniformDeclaration> uniform = qSharedPointerCast<GLShaderUniformDeclaration>(uniformBufferList[i]);
            if (uniform->getType() == GLShaderUniformDeclaration::Type::STRUCT)
            {
                if (uniform->getCount() == 1)
                {
                    const QSharedPointer<ShaderStruct>& s = uniform->getShaderUniformStruct();
                    const auto& fields = s->getFields();
                    for (uint k = 0; k < fields.size(); k++)
                    {
                        QSharedPointer<GLShaderUniformDeclaration> field = qSharedPointerCast<GLShaderUniformDeclaration>(fields[k]);
                        field->m_location = m_glShaderProgram.uniformLocation(uniform->m_name + "." + field->m_name);
                    }
                }
                else
                {
                    for (uint c = 0; c < uniform->getCount(); c++)
                    {
                        const QSharedPointer<ShaderStruct>& s = uniform->getShaderUniformStruct(c);
                        const auto& fields = s->getFields();
                        for (uint k = 0; k < fields.size(); k++)
                        {
                            QSharedPointer<GLShaderUniformDeclaration> field = qSharedPointerCast<GLShaderUniformDeclaration>(fields[k]);
                            field->m_location = m_glShaderProgram.uniformLocation(uniform->m_name+ "[" + QString::number(c) + "]." + field->m_name);
                        }
                    }
                }
            }
            else
            {
                uniform->m_location = m_glShaderProgram.uniformLocation(uniform->m_name);
            }
        }
    }

    void GLShader::resolveUniformBufferLists(const ShaderUniformBufferList& uniformBufferList)
    {
        for (uint i = 0; i < uniformBufferList.size(); i++)
        {
            QSharedPointer<GLShaderUniformBufferDeclaration> decl = qSharedPointerCast<GLShaderUniformBufferDeclaration>(uniformBufferList[i]);
            const ShaderUniformList& uniforms = decl->getUniformDeclarations();
            resolveUniformLists(uniforms);
        }
    }

    void GLShader::resolveUniforms()
    {
        bind();

        resolveUniformBufferLists(m_VSUniformBuffers);

        resolveUniformBufferLists(m_PSUniformBuffers);

        {
            QSharedPointer<GLShaderUniformBufferDeclaration> decl = m_VSUserUniformBuffer;
            if (!decl.isNull())
            {
                const ShaderUniformList& uniforms = decl->getUniformDeclarations();
                resolveUniformLists(uniforms);
            }
        }

        {
            QSharedPointer<GLShaderUniformBufferDeclaration> decl = m_PSUserUniformBuffer;
            if (!decl.isNull())
            {
                const ShaderUniformList& uniforms = decl->getUniformDeclarations();
                resolveUniformLists(uniforms);
            }
        }

        uint sampler = 0;
        for (uint i = 0; i < m_resources.size(); i++)
        {
            QSharedPointer<GLShaderResourceDeclaration> resource = qSharedPointerCast<GLShaderResourceDeclaration>(m_resources[i]);
            uint location = m_glShaderProgram.uniformLocation(resource->m_name);
            if (resource->getCount() == 1)
            {
                resource->m_register = sampler;
                m_glShaderProgram.setUniformValue(location, sampler++);
                sampler++;
            }
            else if (resource->getCount() > 1)
            {
                resource->m_register = 0;
                uint count = resource->getCount();
                int* samplers = new int[count];
                for (uint s = 0; s < count; s++)
                    samplers[s] = s;

                m_glShaderProgram.setUniformValueArray(resource->getName().toStdString().c_str(), samplers, count);
                delete[] samplers;
            }
        }

        unBind();
    }
}