#include "resourceModel.h"
#include "graphic/shader/shaderFactory.h"

namespace QTUI {

	using namespace CGFF;

	int ResourceModel::m_cubeCount = 0;
	int ResourceModel::m_planeCount = 0;
	int ResourceModel::m_sphereCount = 0;

	ResourceModel::ResourceModel(QObject * parent)
		: QStandardItemModel(parent)
		, m_itemScene(nullptr)
		, m_itemEntity(nullptr)
		, m_itemLight(nullptr)
		, m_itemSkybox(nullptr)
        , m_currentScene("")
        , m_currentEntity("")
        , m_currentLight("")
        , m_currentSkybox("")
	{
		addScene();
	}

	QString ResourceModel::addCube()
	{
		QString name = "Cube" + QString::number(++m_cubeCount);
		ResourceManager::getSceneResource(m_currentScene)->addObject(name, QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateDebugCube(5, QVector4D(0.6, 0.6, 0.6, 1.0),
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugShader()))))))));

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        m_entityTransformMats[name] = {};
        m_entityTransformVecs[name] = {};

        emit entityAdded(name);

        onSetCurrentEntity(name);

		return name;
	}

	QString ResourceModel::addPlane()
	{
		QString name = "Plane" + QString::number(++m_planeCount);
		ResourceManager::getSceneResource(m_currentScene)->addObject(name,
			QSharedPointer<Entity>(new Entity(MeshFactory::CreateDebugPlane(64, 64, QVector3D(0, 1, 0),
				QVector4D(0.6, 0.6, 0.6, 1.0),
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugShader()))))))));

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        m_entityTransformMats[name] = {};
        m_entityTransformVecs[name] = {};

        emit entityAdded(name);

        onSetCurrentEntity(name);

		return name;
	}

	QString ResourceModel::addSphere()
	{
		QString name = "Sphere" + QString::number(++m_sphereCount);

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        m_entityTransformMats[name] = {};
        m_entityTransformVecs[name] = {};

        emit entityAdded(name);

        onSetCurrentEntity(name);

		return name;
	}

	void ResourceModel::addScene()
	{
		CGFF::ResourceManager::getSceneResource(ResourceManager::getScene3DName());

        m_currentScene = ResourceManager::getScene3DName();

		m_itemScene = new QStandardItem(m_currentScene);
		appendRow(m_itemScene);

		m_itemEntity = new QStandardItem(ResourceManager::getEntityHierarchyName());
		m_itemScene->appendRow(m_itemEntity);

		m_itemLight = new QStandardItem(ResourceManager::getLightHierarchyName());
		m_itemScene->appendRow(m_itemLight);

		m_itemSkybox = new QStandardItem(ResourceManager::getSkyBoxHierarchyName());
		m_itemScene->appendRow(m_itemSkybox);

		setHorizontalHeaderLabels(QStringList() << QStringLiteral("Scene"));
	}

    void ResourceModel::translateCurrentEntity(const QVector3D& tanslate)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            m_entityTransformMats[m_currentEntity].translateMat.setToIdentity();
            m_entityTransformMats[m_currentEntity].translateMat.translate(tanslate);
            transComponent->transform = m_entityTransformMats[m_currentEntity].getTransform();

            m_entityTransformVecs[m_currentEntity].translateVec = tanslate;
        }
    }

    void ResourceModel::rotateCurrentEntity(float angle, const QVector3D& rotate)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            m_entityTransformMats[m_currentEntity].rotateMat.setToIdentity();
            m_entityTransformMats[m_currentEntity].rotateMat.rotate(angle, rotate);
            transComponent->transform = m_entityTransformMats[m_currentEntity].getTransform();

            if(rotate == QVector3D(1.0, 0.0, 0.0))
                m_entityTransformVecs[m_currentEntity].rotateVec.setX(angle);
            else if (rotate == QVector3D(0.0, 1.0, 0.0))
                m_entityTransformVecs[m_currentEntity].rotateVec.setY(angle);
            else if (rotate == QVector3D(0.0, 0.0, 1.0))
                m_entityTransformVecs[m_currentEntity].rotateVec.setZ(angle);
        }
    }

    void ResourceModel::scaleCurrentEntity(const QVector3D& scale)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            m_entityTransformMats[m_currentEntity].scaleMat.setToIdentity();
            m_entityTransformMats[m_currentEntity].scaleMat.scale(scale);
            transComponent->transform = m_entityTransformMats[m_currentEntity].getTransform();

            m_entityTransformVecs[m_currentEntity].scaleVec = scale;
        }
    }

    void ResourceModel::onAddEntity(CGFF::EntityType type)
    {
        switch (type)
        {
        case CGFF::EntityType::CUBE:
        {
            addCube();
            break;
        }
        case CGFF::EntityType::PLANE:
        {
            addPlane();
            break;
        }
        case CGFF::EntityType::SPHERE:
        {
            addSphere();
            break;
        }
        }
    }

    void ResourceModel::onSetCurrentEntity(const QString& name)
    {
        m_currentEntity = name;
        emit currentEntitySet(name, m_entityTransformVecs[name]);
    }

    void ResourceModel::onSetCurrentLight(const QString& name)
    {
        m_currentLight = name;
        emit currentLightSet(name, m_entityTransformVecs[name]);
    }

    void ResourceModel::onSetCurrentSkyBox(const QString& name)
    {
        m_currentSkybox = name;
    }
}