#include "materialView.h"


namespace QTUI {

	MaterialView::MaterialView(QWidget *parent)
		: BaseView(parent)
		, m_shader_label(nullptr)
		, m_shader_comboBox(nullptr)
		, m_uniformLayout(nullptr)
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

		QList<CGFF::UniformInfo> shaderUniformNames = m_model->getShaderUniforms(name);

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
		int row = 0;

		if (m_uniformLayout)
			delete m_uniformLayout;

		m_uniformLayout = new QGridLayout(this);

		foreach(const CGFF::UniformInfo& uniform, uniformList)
		{
			QLabel * uniformName = new QLabel(uniform.uniformName, this);

			m_uniformLayout->addWidget(uniformName, 0, row, 1, 1);

			row++;
		}

		m_layout->addLayout(m_uniformLayout, 1, 0, row, 3);
	}
}
