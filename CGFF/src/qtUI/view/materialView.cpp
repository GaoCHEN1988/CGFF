#include "materialView.h"
#include "resource/shaderManager.h"
#include "system/fileSystem/vfs.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

namespace QTUI {

    static int s_row_count = 0;

	MaterialView::MaterialView(QWidget *parent)
		: BaseView(parent)
		, m_shader_label(nullptr)
		, m_shader_comboBox(nullptr)
		, m_uniformLayout(nullptr)
		, m_resourceLayout(nullptr)
        , m_isInitilized(false)
	{
		init();

        setupConnections();
	}

	void MaterialView::onCurrentEntitySet(const QString& name)
	{
        if (!m_isInitilized)
        {
            const QMap<QString, QSharedPointer<CGFF::Shader>>& shaderMap = CGFF::ShaderManager::getShaderMap();

            m_shader_comboBox->clear();
            foreach(QString shaderName, shaderMap.keys())
            {
                m_shader_comboBox->addItem(shaderName);
            }

            m_isInitilized = true;
            s_row_count = 0;
        }

        showItems(true);

		QString shaderName = m_model->getShaderName(name);

		if (shaderName.isEmpty())
			return;

		//m_shader_comboBox->clear();
		//m_shader_comboBox->addItem(shaderName);

        int index = m_shader_comboBox->findText(shaderName);

        if(index != -1)
            m_shader_comboBox->setCurrentIndex(index);

        QVector<CGFF::UniformInfo> shaderUniformInfo = m_model->getShaderUniformsInfo(name);

		generalizeShaderUniformView(shaderUniformInfo);

        QVector<CGFF::ShaderResourceUniformInfo> shaderREsourceInfo = m_model->getShaderResourcesInfo(name);

		generalizeShaderResourceView(shaderREsourceInfo);


	}

    void MaterialView::onCurrentModelObjectSet(const QString& name)
    {

    }

    void MaterialView::onCurrentShaderChanged(const QString& shaderName)
    {
        generalizeShaderUniformView(CGFF::ShaderManager::getShader(shaderName)->getShaderUniformsInfo());

        generalizeShaderResourceView(CGFF::ShaderManager::getShader(shaderName)->getShaderResourcesInfo());
    }

    void MaterialView::onSetEmpty()
    {
        clearLayout(m_uniformLayout);

        showItems(false);
    }

	void MaterialView::init()
	{
		m_layout = new QGridLayout(this);

		m_shader_label = new QLabel("Shader", this);

		m_layout->addWidget(m_shader_label, 0, 0, 1, 1);

		m_shader_comboBox= new QComboBox(this);

		m_layout->addWidget(m_shader_comboBox, 0, 2, 1, 2);

        showItems(false);
		
	}

	void MaterialView::setupConnections()
	{
        connect(m_shader_comboBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this, &MaterialView::onCurrentShaderChanged);
	}

	void MaterialView::generalizeShaderUniformView(const QVector<CGFF::UniformInfo>& uniformList)
	{
        clearLayout(m_uniformLayout);

        if (!m_uniformLayout)
            m_uniformLayout = new QGridLayout(this);
			
		foreach(const CGFF::UniformInfo& uniform, uniformList)
		{
			QLabel * uniformLabel = new QLabel(uniform.uniformName, this);


			switch (uniform.uniformType)
			{
			case CGFF::UniformType::GLfloat:
			{
                m_uniformLayout->addWidget(uniformLabel, s_row_count, 0, 1, 1);
                QDoubleSpinBox * uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                uniformFloat_spinbox_x->setMaximum(1000.0);
                m_uniformLayout->addWidget(uniformFloat_spinbox_x, s_row_count, 1, 1, 1);
                s_row_count++;

                connect(uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform, static_cast<GLfloat>(uniformFloat_spinbox_x->value())); });
				break;
			}
			case CGFF::UniformType::GLint:
			{
                m_uniformLayout->addWidget(uniformLabel, s_row_count, 0, 1, 1);

                QSpinBox * uniformInt_spinbox_x = new QSpinBox(this);
                uniformInt_spinbox_x->setMaximum(1000);
                m_uniformLayout->addWidget(uniformInt_spinbox_x, s_row_count, 1, 1, 1);
                s_row_count++;

                connect(uniformInt_spinbox_x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform, static_cast<GLint>(uniformInt_spinbox_x->value())); });
				break;
			}
			case CGFF::UniformType::GLuint:
			{
                m_uniformLayout->addWidget(uniformLabel, s_row_count, 0, 1, 1);

                QSpinBox * uniformInt_spinbox_x = new QSpinBox(this);
                uniformInt_spinbox_x->setMaximum(1000);
                m_uniformLayout->addWidget(uniformInt_spinbox_x, s_row_count, 1, 1, 1);
                s_row_count++;

                connect(uniformInt_spinbox_x, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform, static_cast<GLuint>(uniformInt_spinbox_x->value())); });
				break;
			}
			case CGFF::UniformType::QVector2D:
			{
                m_uniformLayout->addWidget(uniformLabel, s_row_count, 0, 1, 1);

                QDoubleSpinBox * uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                uniformFloat_spinbox_x->setMaximum(1000.0);
                uniformFloat_spinbox_x->setMinimum(-1000.0);
                QDoubleSpinBox * uniformFloat_spinbox_y = new QDoubleSpinBox(this);
                uniformFloat_spinbox_y->setMaximum(1000.0);
                uniformFloat_spinbox_y->setMinimum(-1000.0);
                m_uniformLayout->addWidget(uniformFloat_spinbox_x, s_row_count, 1, 1, 1);
                m_uniformLayout->addWidget(uniformFloat_spinbox_y, s_row_count, 2, 1, 1);

                connect(uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector2D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value())); });

                connect(uniformFloat_spinbox_y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector2D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value())); });
				break;
			}
			case CGFF::UniformType::QVector3D:
			{
                m_uniformLayout->addWidget(uniformLabel, s_row_count, 0, 1, 1);

                QDoubleSpinBox * uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                uniformFloat_spinbox_x->setMaximum(1000.0);
                uniformFloat_spinbox_x->setMinimum(-1000.0);

                QDoubleSpinBox * uniformFloat_spinbox_y = new QDoubleSpinBox(this);
                uniformFloat_spinbox_y->setMaximum(1000.0);
                uniformFloat_spinbox_y->setMinimum(-1000.0);

                QDoubleSpinBox * uniformFloat_spinbox_z = new QDoubleSpinBox(this);
                uniformFloat_spinbox_z->setMaximum(1000.0);
                uniformFloat_spinbox_z->setMinimum(-1000.0);

                m_uniformLayout->addWidget(uniformFloat_spinbox_x, s_row_count, 1, 1, 1);
                m_uniformLayout->addWidget(uniformFloat_spinbox_y, s_row_count, 2, 1, 1);
                m_uniformLayout->addWidget(uniformFloat_spinbox_z, s_row_count, 3,  1, 1);

                s_row_count++;

                connect(uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform, 
                        QVector3D(uniformFloat_spinbox_x->value(),
                        uniformFloat_spinbox_y->value(),
                        uniformFloat_spinbox_z->value())); });

                connect(uniformFloat_spinbox_y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector3D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value(),
                            uniformFloat_spinbox_z->value())); });

                connect(uniformFloat_spinbox_z, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector3D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value(),
                            uniformFloat_spinbox_z->value())); });

				break;
			}
			case CGFF::UniformType::QVector4D:
			{
                m_uniformLayout->addWidget(uniformLabel, s_row_count, 0, 1, 1);

                QDoubleSpinBox *uniformFloat_spinbox_x = new QDoubleSpinBox(this);
                uniformFloat_spinbox_x->setMaximum(1000.0);
                uniformFloat_spinbox_x->setMinimum(-1000.0);

                QDoubleSpinBox * uniformFloat_spinbox_y = new QDoubleSpinBox(this);
                uniformFloat_spinbox_y->setMaximum(1000.0);
                uniformFloat_spinbox_y->setMinimum(-1000.0);

                QDoubleSpinBox * uniformFloat_spinbox_z = new QDoubleSpinBox(this);
                uniformFloat_spinbox_z->setMaximum(1000.0);
                uniformFloat_spinbox_z->setMinimum(-1000.0);

                QDoubleSpinBox * uniformFloat_spinbox_w = new QDoubleSpinBox(this);
                uniformFloat_spinbox_w->setMaximum(1000.0);
                uniformFloat_spinbox_w->setMinimum(-1000.0);

                m_uniformLayout->addWidget(uniformFloat_spinbox_x, s_row_count, 1, 1, 1);
                m_uniformLayout->addWidget(uniformFloat_spinbox_y, s_row_count, 2, 1, 1);
                m_uniformLayout->addWidget(uniformFloat_spinbox_z, s_row_count, 3, 1, 1);
                m_uniformLayout->addWidget(uniformFloat_spinbox_w, s_row_count, 4, 1, 1);

                s_row_count++;

                connect(uniformFloat_spinbox_x, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform, 
                            QVector4D(uniformFloat_spinbox_x->value(), 
                                      uniformFloat_spinbox_y->value(), 
                                      uniformFloat_spinbox_z->value(), 
                                      uniformFloat_spinbox_w->value())); });

                connect(uniformFloat_spinbox_y, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector4D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value(),
                            uniformFloat_spinbox_z->value(),
                            uniformFloat_spinbox_w->value())); });

                connect(uniformFloat_spinbox_z, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector4D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value(),
                            uniformFloat_spinbox_z->value(),
                            uniformFloat_spinbox_w->value())); });

                connect(uniformFloat_spinbox_w, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [=]() { changeUniformValue(uniform,
                        QVector4D(uniformFloat_spinbox_x->value(),
                            uniformFloat_spinbox_y->value(),
                            uniformFloat_spinbox_z->value(),
                            uniformFloat_spinbox_w->value())); });

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
		}

		m_layout->addLayout(m_uniformLayout, 1, 0, s_row_count, 3);
	}

	void MaterialView::generalizeShaderResourceView(const QVector<CGFF::ShaderResourceUniformInfo>& resourceList)
	{
        clearLayout(m_resourceLayout);

        if(!m_resourceLayout)
		    m_resourceLayout = new QGridLayout(this);

		int row_count = 0;

		foreach(const CGFF::ShaderResourceUniformInfo& resource, resourceList)
		{
			QLabel * resourceLabel = new QLabel(resource.resourceName, this);


			switch (resource.resourceType)
			{
			case CGFF::ShaderResourceType::TEXTURE2D:
			{
                m_resourceLayout->addWidget(resourceLabel, row_count, 0, 1, 1);

				QLineEdit* line = new QLineEdit(this);
				QPushButton  *button = new QPushButton("Load", this);
                m_resourceLayout->addWidget(button, row_count, 1, 1, 1);

                connect(button, &QPushButton::clicked,
                    [=]() { changeUniformTexture(resource); });

                row_count++;
				break;
			}

			case CGFF::ShaderResourceType::TEXTURECUBE:
			{
                m_resourceLayout->addWidget(resourceLabel, row_count, 0, 1, 1);

				QPushButton  *button = new QPushButton("Load Cube Texture", this);

                connect(button, &QPushButton::clicked,
                    [=]() { changeUniformTexture(resource); });
                row_count++;
				break;
			}
			}
		}

		m_layout->addLayout(m_resourceLayout, s_row_count+1, 0, row_count, 3);
	}

    void MaterialView::showItems(bool visible)
    {
        if (!visible)
        {
            if (m_shader_label)
                m_shader_label->hide();

            if (m_shader_comboBox)
                m_shader_comboBox->hide();
        }
        else
        {
            if (m_shader_label)
                m_shader_label->show();

            if (m_shader_comboBox)
                m_shader_comboBox->show();
        }

    }

    void MaterialView::clearLayout(QLayout* layout)
    {
        if (layout)
        {
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != NULL)
            {
                delete item->widget();
                delete item;
            }
        }
    }

    void MaterialView::changeUniformTexture(const CGFF::ShaderResourceUniformInfo& uniformInfo)
    {
        if (uniformInfo.resourceType == CGFF::ShaderResourceType::TEXTURE2D)
        {
            QFileDialog dialog;
            QString directoryName = CGFF::VFS::get()->getMountedPhysicalPath("resource");
            dialog.setDirectory(directoryName);
            QString fileName = dialog.getOpenFileName(this,
                tr("Texture Image"), "",
                tr("Image (*.png, *.jpg, *.tga)"));

            if (fileName.isEmpty())
                return;
            else
            {
                QFile file(fileName);
                if (!file.open(QIODevice::ReadOnly)) {
                    QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                    return;
                }

                m_model->changeCurrentEntityTextureUniform(uniformInfo.resourceName, fileName);
            }
        }

        if (uniformInfo.resourceType == CGFF::ShaderResourceType::TEXTURECUBE)
        {
            QFileDialog dialog;
            QString directoryName = CGFF::VFS::get()->getMountedPhysicalPath("resource");
            dialog.setDirectory(directoryName);
            QStringList fileNames = dialog.getOpenFileNames(this,
                tr("Chose 6 Texture Images"), "",
                tr("Image (*.png, *.jpg, *.tng)"));

            if (!fileNames.isEmpty())
            {
                if (fileNames.size() != 6)
                {
                    QMessageBox::information(this, tr("Unable to import images"), tr("Must have 6 images for cube texture!"));
                    return;
                }

                m_model->changeCurrentEntityTextureUniform(uniformInfo.resourceName, fileNames);
            }

        }
    }
}
