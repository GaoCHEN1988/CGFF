#ifndef QTUI_MATERIAL_VIEW_H
#define QTUI_MATERIAL_VIEW_H

#include "baseView.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

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

        void onCurrentEntitySet(const QString& name, const CGFF::UiUniformDataMap& uniformMap);
        void onCurrentLightSet(const QString& name, const CGFF::UiUniformDataMap& uniformMap);
        void onCurrentModelObjectSet(const QString& name, const CGFF::UiUniformDataMap& uniformMap);
        void onCurrentShaderChanged(const QString& shaderName);
        void onCurrentModelShaderChanged(const QString& shaderName);
        void onSetEmpty();

	private:
		void init();
		void setupConnections();
		void generalizeShaderUniformView(const QVector<CGFF::UniformInfo>& uniformList, const CGFF::UiUniformDataMap& uniformMap, bool isModelObject = false);
		void generalizeShaderResourceView(const QVector<CGFF::ShaderResourceUniformInfo>& resourceList, const CGFF::UiUniformDataMap& uniformMap, bool isModelObject = false);
        void showItems(bool visible);
        void clearLayout(QLayout* layout);
        template<typename T>
        void changeUniformValue(const CGFF::UniformInfo& uniformInfo, const T& data, bool isModelObject = false)
        {
            if (isModelObject)
                m_model->changeCurrentModelUniformValue(uniformInfo.uniformName, data);
            else
                m_model->changeCurrentEntityUniformValue(uniformInfo.uniformName, data);
        }

        void changeUniformTexture(QPushButton * button, const CGFF::ShaderResourceUniformInfo& uniformInfo, bool isModelObject = false);

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
	};
}

#endif