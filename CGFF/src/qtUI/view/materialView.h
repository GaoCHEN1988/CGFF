#ifndef QTUI_MATERIAL_VIEW_H
#define QTUI_MATERIAL_VIEW_H

#include "baseView.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGridLayout>

namespace QTUI {

	class MaterialView : public BaseView
	{
		Q_OBJECT

	public:

		struct ShaderUniformView
		{
			QLabel * uniformName;
			QLabel * uniformValue;
		};

		MaterialView(QWidget *parent = Q_NULLPTR);
		virtual ~MaterialView() {};

		public slots:

		void onCurrentEntitySet(const QString& name);

	private:
		void init();
		void setupConnections();
		void generalizeShaderUniformView(const QList<CGFF::UniformInfo>& uniformList);
		void generalizeShaderResourceView(const QList<CGFF::ShaderResourceUniformInfo>& resourceList);

	private:

		QGridLayout * m_layout;
		QGridLayout * m_uniformLayout;
		QGridLayout * m_resourceLayout;
		QLabel * m_shader_label;
		QLabel * m_albedoMap_label;
		QLabel * m_specularMap_label;
		QLabel * m_glossMap_label;
		QLabel * m_normalMap_label;

		QComboBox * m_shader_comboBox;
		QComboBox * m_albedoMap_comboBox;
		QComboBox * m_specularMap_comboBox;
		QComboBox * m_glossMap_comboBox;
		QComboBox * m_normalMap_comboBox;

	};
}

#endif