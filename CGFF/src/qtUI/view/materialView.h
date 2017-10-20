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
        void onCurrentModelObjectSet(const QString& name);
        void onCurrentShaderChanged(const QString& shaderName);
        void onSetEmpty();
	private:
		void init();
		void setupConnections();
		void generalizeShaderUniformView(const QVector<CGFF::UniformInfo>& uniformList);
		void generalizeShaderResourceView(const QVector<CGFF::ShaderResourceUniformInfo>& resourceList);
        void showItems(bool visible);
        void clearLayout(QLayout* layout);
        template<typename T>
        void changeUniformValue(const CGFF::UniformInfo& uniformInfo, const T& data)
        {
            m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, data);
        }

        void changeUniformTexture(const CGFF::ShaderResourceUniformInfo& uniformInfo);

	private:

        bool m_isInitilized;

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

        //QSpinBox * m_uniformInt_spinbox_x;
        //QSpinBox * m_uniformInt_spinbox_y;
        //QSpinBox * m_uniformInt_spinbox_z;
        //QSpinBox * m_uniformInt_spinbox_w;
        //QDoubleSpinBox * m_uniformFloat_spinbox_x;
        //QDoubleSpinBox * m_uniformFloat_spinbox_y;
        //QDoubleSpinBox * m_uniformFloat_spinbox_z;
        //QDoubleSpinBox * m_uniformFloat_spinbox_w;

	};
}

#endif