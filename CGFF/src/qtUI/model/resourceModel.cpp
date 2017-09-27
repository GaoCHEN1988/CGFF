#include "resourceModel.h"
#include "graphic/shader/shaderFactory.h"

namespace QTUI {

	using namespace CGFF;

	int ResourceModel::m_cubeCount = 0;
	int ResourceModel::m_planeCount = 0;
	int ResourceModel::m_sphereCount = 0;
	QVector4D ResourceModel::m_defaultColor = QVector4D(0.6, 0.6, 0.6, 0.6);

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

		setupConnections();
	}

	QString ResourceModel::addCube()
	{
		QString name = "Cube" + QString::number(++m_cubeCount);

		while (!addNameInSet(name, m_entityNames))
		{
			name = "Cube" + QString::number(++m_cubeCount);
		}

		ResourceManager::getSceneResource(m_currentScene)->addObject(name, QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateDebugCube(5, m_defaultColor,
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugShader()))))))));

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        ResourceManager::EntityTransformMats[name] = {};
        ResourceManager::EntityTransformVecs[name] = {};

        emit entityAdded(name);

        onSetCurrentEntity(name);

		return name;
	}

	QString ResourceModel::addPlane()
	{
		QString name = "Plane" + QString::number(++m_planeCount);
		while (!addNameInSet(name, m_entityNames))
		{
			name = "Plane" + QString::number(++m_cubeCount);
		}

		ResourceManager::getSceneResource(m_currentScene)->addObject(name,
			QSharedPointer<Entity>(new Entity(MeshFactory::CreateDebugPlane(64, 64, QVector3D(0, 1, 0),
				m_defaultColor,
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugShader()))))))));

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        ResourceManager::EntityTransformMats[name] = {};
        ResourceManager::EntityTransformVecs[name] = {};

        emit entityAdded(name);

        onSetCurrentEntity(name);

		return name;
	}

	QString ResourceModel::addSphere()
	{
		QString name = "Sphere" + QString::number(++m_sphereCount);
		while (!addNameInSet(name, m_entityNames))
		{
			name = "Sphere" + QString::number(++m_cubeCount);
		}

		//QStandardItem* itemChild = new QStandardItem(name);
		//m_itemEntity->appendRow(itemChild);

  //      ResourceManager::EntityTransformMats[name] = {};
  //      ResourceManager::EntityTransformVecs[name] = {};

  //      emit entityAdded(name);

  //      onSetCurrentEntity(name);

		return name;
	}

	void ResourceModel::addScene()
	{
		CGFF::ResourceManager::getSceneResource(ResourceManager::getScene3DName());

        m_currentScene = ResourceManager::getScene3DName();
		addNameInSet(m_currentScene, m_sceneNames);

		m_itemScene = new QStandardItem(m_currentScene);
		m_itemScene->setEditable(false);
		appendRow(m_itemScene);

		m_itemEntity = new QStandardItem(ResourceManager::getEntityHierarchyName());
		m_itemEntity->setEditable(false);
		m_itemScene->appendRow(m_itemEntity);

		m_itemLight = new QStandardItem(ResourceManager::getLightHierarchyName());
		m_itemLight->setEditable(false);
		m_itemScene->appendRow(m_itemLight);

		m_itemSkybox = new QStandardItem(ResourceManager::getSkyBoxHierarchyName());
		m_itemSkybox->setEditable(false);
		m_itemScene->appendRow(m_itemSkybox);

		setHorizontalHeaderLabels(QStringList() << QStringLiteral("Scene"));
	}

    void ResourceModel::translateCurrentEntity(const QVector3D& tanslate)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            ResourceManager::EntityTransformMats[m_currentEntity].translateMat.setToIdentity();
            ResourceManager::EntityTransformMats[m_currentEntity].translateMat.translate(tanslate);
            transComponent->transform = ResourceManager::EntityTransformMats[m_currentEntity].getTransform();

            ResourceManager::EntityTransformVecs[m_currentEntity].translateVec = tanslate;
        }
    }

    void ResourceModel::rotateCurrentEntity(float angle, const QVector3D& rotate)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            if(rotate == QVector3D(1.0, 0.0, 0.0))
                ResourceManager::EntityTransformVecs[m_currentEntity].rotateVec.setX(angle);
            else if (rotate == QVector3D(0.0, 1.0, 0.0))
                ResourceManager::EntityTransformVecs[m_currentEntity].rotateVec.setY(angle);
            else if (rotate == QVector3D(0.0, 0.0, 1.0))
                ResourceManager::EntityTransformVecs[m_currentEntity].rotateVec.setZ(angle);

			TransformComponent* transComponent = entity->getComponent<TransformComponent>();
			ResourceManager::EntityTransformMats[m_currentEntity].rotateMat.setToIdentity();
			ResourceManager::EntityTransformMats[m_currentEntity].rotateMat.rotate(ResourceManager::EntityTransformVecs[m_currentEntity].rotateVec.x(), QVector3D(1.0, 0.0, 0.0));
			ResourceManager::EntityTransformMats[m_currentEntity].rotateMat.rotate(ResourceManager::EntityTransformVecs[m_currentEntity].rotateVec.y(), QVector3D(0.0, 1.0, 0.0));
			ResourceManager::EntityTransformMats[m_currentEntity].rotateMat.rotate(ResourceManager::EntityTransformVecs[m_currentEntity].rotateVec.z(), QVector3D(0.0, 0.0, 1.0));
			transComponent->transform = ResourceManager::EntityTransformMats[m_currentEntity].getTransform();
        }
    }

    void ResourceModel::scaleCurrentEntity(const QVector3D& scale)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            ResourceManager::EntityTransformMats[m_currentEntity].scaleMat.setToIdentity();
            ResourceManager::EntityTransformMats[m_currentEntity].scaleMat.scale(scale);
            transComponent->transform = ResourceManager::EntityTransformMats[m_currentEntity].getTransform();

            ResourceManager::EntityTransformVecs[m_currentEntity].scaleVec = scale;
        }
    }

	QString ResourceModel::getShaderName(const QString& entityName)
	{
		QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(entityName);

		if (shader.isNull())
			return "";

		return shader->getName();
	}

	QList<UniformInfo> ResourceModel::getShaderUniforms(const QString& entityName)
	{
		QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(entityName);
		QList<UniformInfo> result;

		const ShaderUniformList& uniforms = shader->getPSUserUniformBuffer()->getUniformDeclarations();

		for (uint i = 0; i < uniforms.size(); i++)
		{
			UniformInfo uniformInfo = { uniforms[i]->getName(),  uniforms[i]->getType() };

			result.append(uniformInfo);
		}

		return result;
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
        emit currentEntitySet(name, ResourceManager::EntityTransformVecs[name]);
    }

    void ResourceModel::onSetCurrentLight(const QString& name)
    {
        m_currentLight = name;
        emit currentLightSet(name, ResourceManager::EntityTransformVecs[name]);
    }

    void ResourceModel::onSetCurrentSkyBox(const QString& name)
    {
        m_currentSkybox = name;
    }

	void ResourceModel::onItemChanged(QStandardItem *item)
	{
		QString newName = item->index().data().toString();

		QString parentName = item->index().parent().data(Qt::DisplayRole).toString();

		if (parentName == CGFF::ResourceManager::getEntityHierarchyName())
		{
			QString preName = m_currentEntity;
			m_currentEntity = changeNameInSet(m_currentEntity, newName, m_entityNames);
			ResourceManager::getSceneResource(m_currentScene)->changeObjectName(preName, m_currentEntity);
			item->setText(m_currentEntity);
			emit currentItemNameChanged(m_currentEntity);
		}

		if (parentName == CGFF::ResourceManager::getLightHierarchyName())
		{
			QString preName = m_currentLight;
			m_currentLight = changeNameInSet(m_currentLight, newName, m_lightNames);
			ResourceManager::getSceneResource(m_currentScene)->changeLightName(preName, m_currentLight);
			item->setText(m_currentLight);
			emit currentItemNameChanged(m_currentLight);
		}

		if (parentName == CGFF::ResourceManager::getSkyBoxHierarchyName())
		{
			QString preName = m_currentSkybox;
			m_currentSkybox = changeNameInSet(m_currentSkybox, newName, m_skyboxNames);
			ResourceManager::getSceneResource(m_currentScene)->changeSkyBoxName(preName, m_currentSkybox);
			item->setText(m_currentSkybox);
			emit currentItemNameChanged(m_currentSkybox);
		}

	}

	void ResourceModel::setupConnections()
	{
		connect(this, &ResourceModel::itemChanged, this, &ResourceModel::onItemChanged);
	}

	//Return false if name is already in set, else return true
	bool ResourceModel::addNameInSet(const QString& name, QSet<QString>& set)
	{
		if (set.contains(name))
		{
			return false;

		}
		else
		{
			set.insert(name);
			return true;
		}
	}

	//Return the changed name and the new set
	QString ResourceModel::changeNameInSet(const QString& preName, const QString& newName, QSet<QString>& set)
	{
		if (set.contains(newName))
			return preName;

		if (set.contains(preName))
		{
			set.remove(preName);
			set.insert(newName);
			return newName;
		}
		else
		{
			qFatal("Set name error!");
			return "";
		}
	}
}