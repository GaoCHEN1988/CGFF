#ifndef QTUI_TRANSFORM_VIEW_H
#define QTUI_TRANSFORM_VIEW_H

#include "baseView.h"
#include <QLabel>
#include <QDoubleSpinBox>

namespace QTUI {

	class TransformView : public BaseView
	{
		Q_OBJECT

	public:

		TransformView(QWidget *parent = Q_NULLPTR);
		virtual ~TransformView() {};

        public slots:

        void onPositionChanged(double value);
        void onRotationXChanged(double value);
        void onRotationYChanged(double value);
        void onRotationZChanged(double value);
        void onScaleChanged(double value);

        void onCurrentEntityChanged(const QString& name, const EntityTransformVec& transform);

    private:
        void init();
        void setupConnections();
        void updateView(const EntityTransformVec& transform);
	private:
		QLabel* m_position;
		QLabel* m_x_label;
		QLabel* m_y_label;
		QLabel* m_z_label;
		QDoubleSpinBox* m_x_spin_box;
		QDoubleSpinBox* m_y_spin_box;
		QDoubleSpinBox* m_z_spin_box;
		QLabel* m_rotation;
		QLabel* m_x_rotation_label;
		QLabel* m_y_rotation_label;
		QLabel* m_z_rotation_label;
		QDoubleSpinBox* m_x_rotation_spin_box;
		QDoubleSpinBox* m_y_rotation_spin_box;
		QDoubleSpinBox* m_z_rotation_spin_box;
		QLabel* m_scale;
		QLabel* m_x_scale_label;
		QLabel* m_y_scale_label;
		QLabel* m_z_scale_label;
		QDoubleSpinBox* m_x_scale_spin_box;
		QDoubleSpinBox* m_y_scale_spin_box;
		QDoubleSpinBox* m_z_scale_spin_box;
	};
}

#endif
