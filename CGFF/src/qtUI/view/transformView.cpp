#include "transformView.h"
#include <QGridLayout>

namespace QTUI {

	TransformView::TransformView(QWidget *parent)
		: BaseView(parent)
		, m_position(nullptr)
		, m_x_label(nullptr)
		, m_y_label(nullptr)
		, m_z_label(nullptr)
		, m_x_spin_box(nullptr)
		, m_y_spin_box(nullptr)
		, m_z_spin_box(nullptr)
		, m_rotation(nullptr)
		, m_x_rotation_label(nullptr)
		, m_y_rotation_label(nullptr)
		, m_z_rotation_label(nullptr)
		, m_x_rotation_spin_box(nullptr)
		, m_y_rotation_spin_box(nullptr)
		, m_z_rotation_spin_box(nullptr)
		, m_scale(nullptr)
		, m_x_scale_label(nullptr)
		, m_y_scale_label(nullptr)
		, m_z_scale_label(nullptr)
		, m_x_scale_spin_box(nullptr)
		, m_y_scale_spin_box(nullptr)
		, m_z_scale_spin_box(nullptr)
	{
		init();

        setupConnections();
	}

    void TransformView::onPositionChanged(double value)
    {
        QVector3D tanslate = QVector3D(static_cast<float>(m_x_spin_box->value()),
            static_cast<float>(m_y_spin_box->value()),
            static_cast<float>(m_z_spin_box->value()));
        if(m_model)
            m_model->translateCurrentEntity(tanslate);
    }

    void TransformView::onRotationXChanged(double value)
    {
        QVector3D axis = QVector3D(1.0, 0.0, 0.0);
        if (m_model)
           m_model->rotateCurrentEntity(static_cast<float>(value), axis);
    }

    void TransformView::onRotationYChanged(double value)
    {
        QVector3D axis = QVector3D(0.0, 1.0, 0.0);
        if (m_model)
            m_model->rotateCurrentEntity(static_cast<float>(value), axis);
    }

    void TransformView::onRotationZChanged(double value)
    {
        QVector3D axis = QVector3D(0.0, 0.0, 1.0);

        if (m_model)
            m_model->rotateCurrentEntity(static_cast<float>(value), axis);
    }

    void TransformView::onScaleChanged(double value)
    {
        QVector3D scale = QVector3D(static_cast<float>(m_x_scale_spin_box->value()),
            static_cast<float>(m_y_scale_spin_box->value()),
            static_cast<float>(m_z_scale_spin_box->value()));

        if (m_model)
            m_model->scaleCurrentEntity(scale);
    }

    void TransformView::onCurrentEntitySet(const QString& name, const CGFF::EntityTransformVec& transform)
    {
        updateView(transform);
    }

    void TransformView::init()
    {
        QGridLayout * layout = new QGridLayout(this);

        //Position
        m_position = new QLabel("position: ", this);
        layout->addWidget(m_position, 0, 0, 1, 2);

        m_x_label = new QLabel("x", this);
        layout->addWidget(m_x_label, 0, 3, 1, 1);

        m_x_spin_box = new QDoubleSpinBox(this);
        m_x_spin_box->setValue(0);
        m_x_spin_box->setMinimum(-100.0);
        layout->addWidget(m_x_spin_box, 0, 4, 1, 2);

        m_y_label = new QLabel("y", this);
        layout->addWidget(m_y_label, 0, 6, 1, 1);

        m_y_spin_box = new QDoubleSpinBox(this);
        m_y_spin_box->setValue(0);
        m_y_spin_box->setMinimum(-100.0);
        layout->addWidget(m_y_spin_box, 0, 7, 1, 2);

        m_z_label = new QLabel("z", this);
        layout->addWidget(m_z_label, 0, 9, 1, 1);

        m_z_spin_box = new QDoubleSpinBox(this);
        m_z_spin_box->setValue(0);
        m_z_spin_box->setMinimum(-100.0);
        layout->addWidget(m_z_spin_box, 0, 10, 1, 2);

        //Rotation
        m_rotation = new QLabel("rotatiom: ", this);
        layout->addWidget(m_rotation, 1, 0, 1, 2);

        m_x_rotation_label = new QLabel("x", this);
        layout->addWidget(m_x_rotation_label, 1, 3, 1, 1);

        m_x_rotation_spin_box = new QDoubleSpinBox(this);
        m_x_rotation_spin_box->setValue(0);
        m_x_rotation_spin_box->setMinimum(-100.0);
        layout->addWidget(m_x_rotation_spin_box, 1, 4, 1, 2);

        m_y_rotation_label = new QLabel("y", this);
        layout->addWidget(m_y_rotation_label, 1, 6, 1, 1);

        m_y_rotation_spin_box = new QDoubleSpinBox(this);
        m_y_rotation_spin_box->setValue(0);
        m_y_rotation_spin_box->setMinimum(-100.0);
        layout->addWidget(m_y_rotation_spin_box, 1, 7, 1, 2);

        m_z_rotation_label = new QLabel("z", this);
        layout->addWidget(m_z_rotation_label, 1, 9, 1, 1);

        m_z_rotation_spin_box = new QDoubleSpinBox(this);
        m_z_rotation_spin_box->setValue(0);
        m_z_rotation_spin_box->setMinimum(-100.0);
        layout->addWidget(m_z_rotation_spin_box, 1, 10, 1, 2);

        //Scale
        m_scale = new QLabel("scale: ", this);
        layout->addWidget(m_scale, 2, 0, 1, 2);

        m_x_scale_label = new QLabel("x", this);
        layout->addWidget(m_x_scale_label, 2, 3, 1, 1);

        m_x_scale_spin_box = new QDoubleSpinBox(this);
        m_x_scale_spin_box->setValue(1.0);
        m_x_scale_spin_box->setMinimum(0.01);
        layout->addWidget(m_x_scale_spin_box, 2, 4, 1, 2);

        m_y_scale_label = new QLabel("y", this);
        layout->addWidget(m_y_scale_label, 2, 6, 1, 1);

        m_y_scale_spin_box = new QDoubleSpinBox(this);
        m_y_scale_spin_box->setValue(1.0);
        m_y_scale_spin_box->setMinimum(0.01);
        layout->addWidget(m_y_scale_spin_box, 2, 7, 1, 2);

        m_z_scale_label = new QLabel("z", this);
        layout->addWidget(m_z_scale_label, 2, 9, 1, 1);

        m_z_scale_spin_box = new QDoubleSpinBox(this);
        m_z_scale_spin_box->setValue(1.0);
        m_z_scale_spin_box->setMinimum(0.01);
        layout->addWidget(m_z_scale_spin_box, 2, 10, 1, 2);
    }

    void TransformView::setupConnections()
    {
        connect(m_x_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onPositionChanged);

        connect(m_y_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onPositionChanged);

        connect(m_z_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onPositionChanged);

        connect(m_x_rotation_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onRotationXChanged);

        connect(m_y_rotation_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onRotationYChanged);

        connect(m_z_rotation_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onRotationZChanged);

        connect(m_x_scale_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onScaleChanged);

        connect(m_y_scale_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onScaleChanged);

        connect(m_z_scale_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &TransformView::onScaleChanged);
    }

	void TransformView::disconnections()
	{
		disconnect(m_x_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onPositionChanged);

		disconnect(m_y_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onPositionChanged);

		disconnect(m_z_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onPositionChanged);

		disconnect(m_x_rotation_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onRotationXChanged);

		disconnect(m_y_rotation_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onRotationYChanged);

		disconnect(m_z_rotation_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onRotationZChanged);

		disconnect(m_x_scale_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onScaleChanged);

		disconnect(m_y_scale_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onScaleChanged);

		disconnect(m_z_scale_spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &TransformView::onScaleChanged);
	}

    void TransformView::updateView(const CGFF::EntityTransformVec& transform)
    {
		disconnections();
        m_x_spin_box->setValue(static_cast<double>(transform.translateVec.x()));
        m_y_spin_box->setValue(static_cast<double>(transform.translateVec.y()));
        m_z_spin_box->setValue(static_cast<double>(transform.translateVec.z()));

        m_x_rotation_spin_box->setValue(static_cast<double>(transform.rotateVec.x()));
        m_y_rotation_spin_box->setValue(static_cast<double>(transform.rotateVec.y()));
        m_z_rotation_spin_box->setValue(static_cast<double>(transform.rotateVec.z()));

        m_x_scale_spin_box->setValue(static_cast<double>(transform.scaleVec.x()));
        m_y_scale_spin_box->setValue(static_cast<double>(transform.scaleVec.y()));
        m_z_scale_spin_box->setValue(static_cast<double>(transform.scaleVec.z()));

		setupConnections();
    }
}