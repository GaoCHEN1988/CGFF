#include "materialView.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>

namespace QTUI {

	MaterialView::MaterialView(QWidget *parent)
		: BaseView(parent)
		, m_shader_label(nullptr)
		, m_shader_comboBox(nullptr)
		, m_uniformLayout(nullptr)
		, m_resourceLayout(nullptr)
	{
		init();
	}

	void MaterialView::onCurrentEntitySet(const QString& name)
	{
		QString shaderName = m_model->getShaderName(name);

		if (shaderName.isEmpty())
			return;

		m_shader_comboBox->clear();
		m_shader_comboBox->addItem(shaderName);

		QList<CGFF::UniformInfo> shaderUniformInfo = m_model->getShaderUniforms(name);

		generalizeShaderUniformView(shaderUniformInfo);

		QList<CGFF::ShaderResourceUniformInfo> shaderREsourceInfo = m_model->getShaderResources(name);

		generalizeShaderResourceView(shaderREsourceInfo);

	}

	void MaterialView::init()
	{
		m_layout = new QGridLayout(this);

		m_shader_label = new QLabel("Shader", this);

		m_layout->addWidget(m_shader_label, 0, 0, 1, 1);

		m_shader_comboBox= new QComboBox(this);

		m_layout->addWidget(m_shader_comboBox, 0, 2, 1, 2);
		
	}

	void MaterialView::setupConnections()
	{

	}

	void MaterialView::generalizeShaderUniformView(const QList<CGFF::UniformInfo>& uniformList)
	{
		if (m_uniformLayout)
		{
			QLayoutItem* item;
			while ((item = m_uniformLayout->takeAt(0)) != NULL)
			{
				delete item->widget();
				delete item;
			}
			delete m_uniformLayout;
		}

		m_uniformLayout = new QGridLayout(this);
			
		int row = 0;

		foreach(const CGFF::UniformInfo& uniform, uniformList)
		{
			QLabel * uniformLabel = new QLabel(uniform.uniformName, this);

			m_uniformLayout->addWidget(uniformLabel, row, 0, 1, 1);

			switch (uniform.uniformType)
			{
			case CGFF::UniformType::GLfloat:
			{
                m_uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_x->setMaximum(1000.0);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_x, row, 1, 1, 1);

                connect(m_uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });
				break;
			}
			case CGFF::UniformType::GLint:
			{
                m_uniformInt_spinbox_x = new QSpinBox(this);
                m_uniformInt_spinbox_x->setMaximum(1000);
                m_uniformLayout->addWidget(m_uniformInt_spinbox_x, row, 1, 1, 1);

                connect(m_uniformInt_spinbox_x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });
				break;
			}
			case CGFF::UniformType::GLuint:
			{
                m_uniformInt_spinbox_x = new QSpinBox(this);
                m_uniformInt_spinbox_x->setMaximum(1000);
                m_uniformLayout->addWidget(m_uniformInt_spinbox_x, row, 1, 1, 1);

                connect(m_uniformInt_spinbox_x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });
				break;
			}
			case CGFF::UniformType::QVector2D:
			{
                m_uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_x->setMaximum(1000.0);
                m_uniformFloat_spinbox_x->setMinimum(-1000.0);
                m_uniformFloat_spinbox_y = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_y->setMaximum(1000.0);
                m_uniformFloat_spinbox_y->setMinimum(-1000.0);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_x, row, 1, 1, 1);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_y, row, 2, 1, 1);

                connect(m_uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

                connect(m_uniformFloat_spinbox_y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });
				break;
			}
			case CGFF::UniformType::QVector3D:
			{
                m_uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_x->setMaximum(1000.0);
                m_uniformFloat_spinbox_x->setMinimum(-1000.0);

                m_uniformFloat_spinbox_y = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_y->setMaximum(1000.0);
                m_uniformFloat_spinbox_y->setMinimum(-1000.0);

                m_uniformFloat_spinbox_z = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_z->setMaximum(1000.0);
                m_uniformFloat_spinbox_z->setMinimum(-1000.0);

                m_uniformLayout->addWidget(m_uniformFloat_spinbox_x, row, 1, 1, 1);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_y, row, 2, 1, 1);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_z, row, 3,  1, 1);

                connect(m_uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

                connect(m_uniformFloat_spinbox_y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

                connect(m_uniformFloat_spinbox_z, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

				break;
			}
			case CGFF::UniformType::QVector4D:
			{
                m_uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_x->setMaximum(1000.0);
                m_uniformFloat_spinbox_x->setMinimum(-1000.0);

                m_uniformFloat_spinbox_y = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_y->setMaximum(1000.0);
                m_uniformFloat_spinbox_y->setMinimum(-1000.0);

                m_uniformFloat_spinbox_z = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_z->setMaximum(1000.0);
                m_uniformFloat_spinbox_z->setMinimum(-1000.0);

                m_uniformFloat_spinbox_w = new QDoubleSpinBox(this);
                m_uniformFloat_spinbox_w->setMaximum(1000.0);
                m_uniformFloat_spinbox_w->setMinimum(-1000.0);

                m_uniformLayout->addWidget(m_uniformFloat_spinbox_x, row, 1, 1, 1);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_y, row, 2, 1, 1);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_z, row, 3, 1, 1);
                m_uniformLayout->addWidget(m_uniformFloat_spinbox_w, row, 4, 1, 1);

                connect(m_uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

                connect(m_uniformFloat_spinbox_y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

                connect(m_uniformFloat_spinbox_z, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

                connect(m_uniformFloat_spinbox_w, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform); });

				break;
			}
			case CGFF::UniformType::QMatrix2x2:
			{

				break;
			}
			case CGFF::UniformType::QMatrix3x3:
			{

				break;
			}
			case CGFF::UniformType::QMatrix4x4:
			{

				break;
			}
			case CGFF::UniformType::STRUCT:
			{

				break;
			}
			}
			row++;
		}

		m_layout->addLayout(m_uniformLayout, 1, 0, row, 3);
	}

	void MaterialView::generalizeShaderResourceView(const QList<CGFF::ShaderResourceUniformInfo>& resourceList)
	{
		if (m_resourceLayout)
		{
			QLayoutItem* item;
			while ((item = m_resourceLayout->takeAt(0)) != NULL)
			{
				delete item->widget();
				delete item;
			}
			delete m_resourceLayout;
		}

		m_resourceLayout = new QGridLayout(this);

		int row = 0;

		foreach(const CGFF::ShaderResourceUniformInfo& resource, resourceList)
		{
			QLabel * resourceLabel = new QLabel(resource.resourceName, this);

			m_resourceLayout->addWidget(resourceLabel, 0, row, 1, 1);

			switch (resource.resourceType)
			{
			case CGFF::ShaderResourceType::TEXTURE2D:
			{
				QLineEdit* line = new QLineEdit(this);
				QPushButton  *button = new QPushButton(this);
				break;
			}

			case CGFF::ShaderResourceType::TEXTURECUBE:
			{
				QLineEdit* line1 = new QLineEdit(this);
				QLineEdit* line2 = new QLineEdit(this);
				QLineEdit* line3 = new QLineEdit(this);
				QLineEdit* line4 = new QLineEdit(this);
				QLineEdit* line5 = new QLineEdit(this);
				QLineEdit* line6 = new QLineEdit(this);
				QPushButton  *button = new QPushButton(this);
				break;
			}

			//case CGFF::ShaderResourceType::TEXTURESHADOW:
			//{
			//	QLineEdit* line = new QLineEdit(this);
			//	QPushButton  *button = new QPushButton(this);
			//	break;
			//}
			}

			row++;
		}

		m_layout->addLayout(m_resourceLayout, 2, 0, row, 3);
	}

    void MaterialView::changeUniformValue(const CGFF::UniformInfo& uniformInfo)
    {
        switch (uniformInfo.uniformType)
        {
        case CGFF::UniformType::GLfloat:
        {
            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, static_cast<float>(m_uniformFloat_spinbox_x->value()));
            break;
        }
        case CGFF::UniformType::GLint:
        {
            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, m_uniformInt_spinbox_x->value());
            break;
        }
        case CGFF::UniformType::GLuint:
        {
            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, static_cast<GLuint>(m_uniformInt_spinbox_x->value()));
            break;
        }
        case CGFF::UniformType::QVector2D:
        {
            QVector2D tempVector(m_uniformFloat_spinbox_x->value(), m_uniformFloat_spinbox_y->value());

            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, tempVector);
            break;
        }
        case CGFF::UniformType::QVector3D:
        {
            QVector3D tempVector(m_uniformFloat_spinbox_x->value(),
                m_uniformFloat_spinbox_y->value(),
                m_uniformFloat_spinbox_z->value());

            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, tempVector);

            break;
        }
        case CGFF::UniformType::QVector4D:
        {
            QVector4D tempVector(m_uniformFloat_spinbox_x->value(),
                m_uniformFloat_spinbox_y->value(),
                m_uniformFloat_spinbox_z->value(),
                m_uniformFloat_spinbox_w->value());

            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, tempVector);

            break;
        }

        }
    }
}
