#ifndef QTUI_OBJECT_INFO_VIEW_H
#define QTUI_OBJECT_INFO_VIEW_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include "baseView.h"
#include "transformView.h"
#include "materialView.h"

namespace QTUI {

	class ObjectInfoView : public BaseView
	{
		Q_OBJECT

	public:

		ObjectInfoView(QWidget *parent = Q_NULLPTR);
		virtual ~ObjectInfoView() {};

        void setModel(ResourceModel * model) override;

        public slots:
        void onCurrentEntitySet(const QString& name, const CGFF::UiTransformVec& transform);
        void onCurrentModelObjectSet(const QString& name, const CGFF::UiTransformVec& transform);
        void onCurrentItemNameChanged(const QString& name);
        void onSetEmptyItem();

	private:
		void init();
        void setupConnections();

	private:
		QGroupBox * m_transform_groupBox;
        QGroupBox * m_material_groupBox;
		QLabel* m_object_name_label;
		TransformView* m_transformView;
        MaterialView* m_materialView;
	};
}

#endif