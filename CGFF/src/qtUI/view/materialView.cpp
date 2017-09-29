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

			m_uniformLayout->addWidget(uniformLabel, 0, row, 1, 1);

			switch (uniform.uniformType)
			{
			case CGFF::UniformType::GLfloat:
			{
				QDoubleSpinBox * spinbox = new QDoubleSpinBox(this);
				break;
			}
			case CGFF::UniformType::GLint:
			{
				QSpinBox * spinbox = new QSpinBox(this);
				break;
			}
			case CGFF::UniformType::GLuint:
			{
				QSpinBox * spinbox = new QSpinBox(this);
				break;
			}
			case CGFF::UniformType::QVector2D:
			{
				QSpinBox * spinbox_x = new QSpinBox(this);
				QSpinBox * spinbox_y = new QSpinBox(this);
				break;
			}
			case CGFF::UniformType::QVector3D:
			{
				QSpinBox * spinbox_x = new QSpinBox(this);
				QSpinBox * spinbox_y = new QSpinBox(this);
				QSpinBox * spinbox_z = new QSpinBox(this);
				break;
			}
			case CGFF::UniformType::QVector4D:
			{
				QSpinBox * spinbox_x = new QSpinBox(this);
				QSpinBox * spinbox_y = new QSpinBox(this);
				QSpinBox * spinbox_z = new QSpinBox(this);
				QSpinBox * spinbox_w = new QSpinBox(this);
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

			case CGFF::ShaderResourceType::TEXTURESHADOW:
			{
				QLineEdit* line = new QLineEdit(this);
				QPushButton  *button = new QPushButton(this);
				break;
			}
			}

			row++;
		}

		m_layout->addLayout(m_resourceLayout, 2, 0, row, 3);
	}
}
