#include "resourceModel.h"
#include "graphic/shader/shaderFactory.h"
#include <QFileInfo>

namespace QTUI {

	using namespace CGFF;

	int ResourceModel::m_cubeCount = 0;
	int ResourceModel::m_planeCount = 0;
	int ResourceModel::m_sphereCount = 0;
    QMap<QString, int> ResourceModel::m_modelCounts;

	ResourceModel::ResourceModel(QObject * parent)
		: QStandardItemModel(parent)
		, m_itemScene(nullptr)
		, m_itemEntity(nullptr)
		, m_itemLight(nullptr)
		, m_itemSkybox(nullptr)
        , m_itemModel(nullptr)
        , m_currentScene("")
        , m_currentEntity("")
        , m_currentLight("")
        , m_currentSkybox("")
        , m_currentModel("")
        , m_currentObjType(CurrentObjectType::NONE)
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

		ResourceManager::getSceneResource(m_currentScene)->addEntity(name, QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateDebugCube(5,
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugSceneShader()))))))));

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        ResourceManager::UiTransformMats[name] = {};
        ResourceManager::UiTransformVecs[name] = {};
        ResourceManager::UiUniformDatas[name] = {};

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

		ResourceManager::getSceneResource(m_currentScene)->addEntity(name,
			QSharedPointer<Entity>(new Entity(MeshFactory::CreateDebugPlane(64, 64, QVector3D(0, 1, 0),
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugSceneShader()))))))));

		QStandardItem* itemChild = new QStandardItem(name);
		m_itemEntity->appendRow(itemChild);

        ResourceManager::UiTransformMats[name] = {};
        ResourceManager::UiTransformVecs[name] = {};
        ResourceManager::UiUniformDatas[name] = {};

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

        QSharedPointer<Model> sphereModel = QSharedPointer<Model>(new Model("/resource/Sphere.obj", QSharedPointer<MaterialInstance>(new MaterialInstance(
            QSharedPointer<Material>(new Material(ShaderFactory::DebugSceneShader()))))));

        ResourceManager::getSceneResource(m_currentScene)->addEntity(name,
            QSharedPointer<Entity>(new Entity(sphereModel->getMeshes()[0])));

        QStandardItem* itemChild = new QStandardItem(name);
        m_itemEntity->appendRow(itemChild);

        ResourceManager::UiTransformMats[name] = {};
        ResourceManager::UiTransformVecs[name] = {};
        ResourceManager::UiUniformDatas[name] = {};

        emit entityAdded(name);

        onSetCurrentEntity(name);

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

		m_itemEntity = new QStandardItem(ResourceManager::EntityHierarchyName);
		m_itemEntity->setEditable(false);
		m_itemScene->appendRow(m_itemEntity);

		m_itemLight = new QStandardItem(ResourceManager::LightHierarchyName);
		m_itemLight->setEditable(false);
		m_itemScene->appendRow(m_itemLight);

		m_itemSkybox = new QStandardItem(ResourceManager::SkyBoxHierarchyName);
		m_itemSkybox->setEditable(false);
		m_itemScene->appendRow(m_itemSkybox);

        m_itemModel = new QStandardItem(ResourceManager::ModelHierarchyName);
        m_itemModel->setEditable(false);
        m_itemScene->appendRow(m_itemModel);

		setHorizontalHeaderLabels(QStringList() << QStringLiteral("Scene"));
	}

    void ResourceModel::translateCurrentObject(const QVector3D& tanslate)
    {
        switch (m_currentObjType)
        {
        case CurrentObjectType::ENTITY:
            translateCurrentEntity(tanslate);
            break;
        case CurrentObjectType::LIGHT:
            break;
        case CurrentObjectType::MODEL:
            translateCurrentModelObject(tanslate);
        }
    }

    void ResourceModel::rotateCurrentObject(float angle, const QVector3D& rotate)
    {
        switch (m_currentObjType)
        {
        case CurrentObjectType::ENTITY:
            rotateCurrentEntity(angle, rotate);
            break;
        case CurrentObjectType::LIGHT:
            break;
        case CurrentObjectType::MODEL:
            rotateCurrentModelObject(angle, rotate);
        }
    }

    void ResourceModel::scaleCurrentObject(const QVector3D& scale)
    {
        switch (m_currentObjType)
        {
        case CurrentObjectType::ENTITY:
            scaleCurrentEntity(scale);
            break;
        case CurrentObjectType::LIGHT:
            break;
        case CurrentObjectType::MODEL:
            scaleCurrentModelObject(scale);
        }
    }

    void ResourceModel::translateCurrentEntity(const QVector3D& tanslate)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            ResourceManager::UiTransformMats[m_currentEntity].translateMat.setToIdentity();
            ResourceManager::UiTransformMats[m_currentEntity].translateMat.translate(tanslate);
            transComponent->setTransform(ResourceManager::UiTransformMats[m_currentEntity].getTransform());

            ResourceManager::UiTransformVecs[m_currentEntity].translateVec = tanslate;
        }
    }

    void ResourceModel::rotateCurrentEntity(float angle, const QVector3D& rotate)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            if(rotate == QVector3D(1.0, 0.0, 0.0))
                ResourceManager::UiTransformVecs[m_currentEntity].rotateVec.setX(angle);
            else if (rotate == QVector3D(0.0, 1.0, 0.0))
                ResourceManager::UiTransformVecs[m_currentEntity].rotateVec.setY(angle);
            else if (rotate == QVector3D(0.0, 0.0, 1.0))
                ResourceManager::UiTransformVecs[m_currentEntity].rotateVec.setZ(angle);

			TransformComponent* transComponent = entity->getComponent<TransformComponent>();
			ResourceManager::UiTransformMats[m_currentEntity].rotateMat.setToIdentity();
			ResourceManager::UiTransformMats[m_currentEntity].rotateMat.rotate(ResourceManager::UiTransformVecs[m_currentEntity].rotateVec.x(), QVector3D(1.0, 0.0, 0.0));
			ResourceManager::UiTransformMats[m_currentEntity].rotateMat.rotate(ResourceManager::UiTransformVecs[m_currentEntity].rotateVec.y(), QVector3D(0.0, 1.0, 0.0));
			ResourceManager::UiTransformMats[m_currentEntity].rotateMat.rotate(ResourceManager::UiTransformVecs[m_currentEntity].rotateVec.z(), QVector3D(0.0, 0.0, 1.0));
			transComponent->setTransform(ResourceManager::UiTransformMats[m_currentEntity].getTransform());
        }
    }

    void ResourceModel::scaleCurrentEntity(const QVector3D& scale)
    {
        QSharedPointer<Entity> entity = ResourceManager::getEntity(m_currentScene, m_currentEntity);
        if (entity)
        {
            TransformComponent* transComponent = entity->getComponent<TransformComponent>();
            ResourceManager::UiTransformMats[m_currentEntity].scaleMat.setToIdentity();
            ResourceManager::UiTransformMats[m_currentEntity].scaleMat.scale(scale);
            transComponent->setTransform(ResourceManager::UiTransformMats[m_currentEntity].getTransform());

            ResourceManager::UiTransformVecs[m_currentEntity].scaleVec = scale;
        }
    }

    void ResourceModel::translateCurrentModelObject(const QVector3D& tanslate)
    {
        QSharedPointer<ModelObject> modelobj = ResourceManager::getModelObject(m_currentScene, m_currentModel);
        if (modelobj)
        {
            ResourceManager::UiTransformMats[m_currentModel].translateMat.setToIdentity();
            ResourceManager::UiTransformMats[m_currentModel].translateMat.translate(tanslate);
            modelobj->transform(ResourceManager::UiTransformMats[m_currentModel].getTransform());

            ResourceManager::UiTransformVecs[m_currentModel].translateVec = tanslate;

            //for (const QString& key : modelobj->getEntities().keys())
            //{
            //    ResourceManager::UiTransformMats[key].translateMat = ResourceManager::UiTransformMats[m_currentModel].translateMat;
            //    ResourceManager::UiTransformVecs[key].translateVec = ResourceManager::UiTransformVecs[m_currentModel].translateVec;
            //}
        }
    }
    void ResourceModel::rotateCurrentModelObject(float angle, const QVector3D& rotate)
    {
        QSharedPointer<ModelObject> modelobj = ResourceManager::getModelObject(m_currentScene, m_currentModel);
        if (modelobj)
        {
            if (rotate == QVector3D(1.0, 0.0, 0.0))
                ResourceManager::UiTransformVecs[m_currentModel].rotateVec.setX(angle);
            else if (rotate == QVector3D(0.0, 1.0, 0.0))
                ResourceManager::UiTransformVecs[m_currentModel].rotateVec.setY(angle);
            else if (rotate == QVector3D(0.0, 0.0, 1.0))
                ResourceManager::UiTransformVecs[m_currentModel].rotateVec.setZ(angle);

            ResourceManager::UiTransformMats[m_currentModel].rotateMat.setToIdentity();
            ResourceManager::UiTransformMats[m_currentModel].rotateMat.rotate(ResourceManager::UiTransformVecs[m_currentModel].rotateVec.x(), QVector3D(1.0, 0.0, 0.0));
            ResourceManager::UiTransformMats[m_currentModel].rotateMat.rotate(ResourceManager::UiTransformVecs[m_currentModel].rotateVec.y(), QVector3D(0.0, 1.0, 0.0));
            ResourceManager::UiTransformMats[m_currentModel].rotateMat.rotate(ResourceManager::UiTransformVecs[m_currentModel].rotateVec.z(), QVector3D(0.0, 0.0, 1.0));

            //for (const QString& key : modelobj->getEntities().keys())
            //{
            //    ResourceManager::UiTransformMats[key].rotateMat = ResourceManager::UiTransformMats[m_currentModel].rotateMat;
            //    ResourceManager::UiTransformVecs[key].rotateVec = ResourceManager::UiTransformVecs[m_currentModel].rotateVec;
            //}

            modelobj->transform(ResourceManager::UiTransformMats[m_currentModel].getTransform());
        }
    }

    void ResourceModel::scaleCurrentModelObject(const QVector3D& scale)
    {
        QSharedPointer<ModelObject> modelobj = ResourceManager::getModelObject(m_currentScene, m_currentModel);
        if (modelobj)
        {
            ResourceManager::UiTransformMats[m_currentModel].scaleMat.setToIdentity();
            ResourceManager::UiTransformMats[m_currentModel].scaleMat.scale(scale);
            modelobj->transform(ResourceManager::UiTransformMats[m_currentModel].getTransform());
            ResourceManager::UiTransformVecs[m_currentModel].scaleVec = scale;

            //for (const QString& key : modelobj->getEntities().keys())
            //{
            //    ResourceManager::UiTransformMats[key].scaleMat = ResourceManager::UiTransformMats[m_currentModel].scaleMat;
            //    ResourceManager::UiTransformVecs[key].scaleVec = ResourceManager::UiTransformVecs[m_currentModel].scaleVec;
            //}
        }
    }

	QString ResourceModel::getShaderName(const QString& entityName)
	{
		QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(entityName);

		if (shader.isNull())
			return "";

		return shader->getName();
	}

	QVector<UniformInfo> ResourceModel::getShaderUniformsInfo(const QString& entityName)
	{
		return ResourceManager::getSceneResource(m_currentScene)->getEntityShader(entityName)->getShaderUniformsInfo();
	}

    QVector<CGFF::ShaderResourceUniformInfo> ResourceModel::getShaderResourcesInfo(const QString& entityName)
	{
		return ResourceManager::getSceneResource(m_currentScene)->getEntityShader(entityName)->getShaderResourcesInfo();
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

    void ResourceModel::onLoadModel(const QString& path)
    {
        QSharedPointer<Model> model = QSharedPointer<Model>(new Model(path, 
            QSharedPointer<MaterialInstance>(new MaterialInstance(
            QSharedPointer<Material>(new Material(ShaderFactory::DebugSceneShader()))))));

        QFileInfo file(path);
        QString name = file.baseName();
        QSharedPointer<ModelObject> modelobj = QSharedPointer<ModelObject>(new ModelObject(name, model));
        ResourceManager::getSceneResource(m_currentScene)->addModelObject(name, modelobj);

        m_modelCounts[name] = 1;

        QStandardItem* itemChild = new QStandardItem(name);
        m_itemModel->appendRow(itemChild);

        for (const QString& key : modelobj->getEntities().keys())
        {
            QStandardItem* itemEntity = new QStandardItem(key);
            itemChild->appendRow(itemEntity);

            ResourceManager::getSceneResource(m_currentScene)->addEntity(key, modelobj->getEntities()[key]);

            ResourceManager::UiTransformMats[key] = {};
            ResourceManager::UiTransformVecs[key] = {};
        }

        ResourceManager::UiTransformMats[name] = {};
        ResourceManager::UiTransformVecs[name] = {};
        //ResourceManager::UiUniformDatas[name] = {};

        onSetCurrentModel(name);
        emit modelObjectAdded(name);
    }

    void ResourceModel::onSetCurrentEntity(const QString& name)
    {
        m_currentEntity = name;
        m_currentObjType = CurrentObjectType::ENTITY;
        emit currentEntitySet(name, ResourceManager::UiTransformVecs[name]);
    }

    void ResourceModel::onSetCurrentLight(const QString& name)
    {
        m_currentLight = name;
        m_currentObjType = CurrentObjectType::LIGHT;
        emit currentLightSet(name, ResourceManager::UiTransformVecs[name]);
    }

    void ResourceModel::onSetCurrentSkyBox(const QString& name)
    {
        m_currentSkybox = name;
    }

    void ResourceModel::onSetCurrentModel(const QString& name)
    {
        m_currentModel = name;
        m_currentObjType = CurrentObjectType::MODEL;
        emit currentModelObjectSet(name, ResourceManager::UiTransformVecs[name]);
    }


	void ResourceModel::onItemChanged(QStandardItem *item)
	{
		QString newName = item->index().data().toString();

		QString parentName = item->index().parent().data(Qt::DisplayRole).toString();

		if (parentName == CGFF::ResourceManager::EntityHierarchyName)
		{
			QString preName = m_currentEntity;
			m_currentEntity = changeNameInSet(m_currentEntity, newName, m_entityNames);
			ResourceManager::getSceneResource(m_currentScene)->changeObjectName(preName, m_currentEntity);
			item->setText(m_currentEntity);
            m_currentObjType = CurrentObjectType::ENTITY;
			emit currentItemNameChanged(m_currentEntity);
		}

		if (parentName == CGFF::ResourceManager::LightHierarchyName)
		{
			QString preName = m_currentLight;
			m_currentLight = changeNameInSet(m_currentLight, newName, m_lightNames);
			ResourceManager::getSceneResource(m_currentScene)->changeLightName(preName, m_currentLight);
			item->setText(m_currentLight);
            m_currentObjType = CurrentObjectType::LIGHT;
			emit currentItemNameChanged(m_currentLight);
		}

		if (parentName == CGFF::ResourceManager::SkyBoxHierarchyName)
		{
			QString preName = m_currentSkybox;
			m_currentSkybox = changeNameInSet(m_currentSkybox, newName, m_skyboxNames);
			ResourceManager::getSceneResource(m_currentScene)->changeSkyBoxName(preName, m_currentSkybox);
			item->setText(m_currentSkybox);
			emit currentItemNameChanged(m_currentSkybox);
		}

        if (parentName == CGFF::ResourceManager::ModelHierarchyName)
        {
            QString preName = m_currentModel;
            m_currentModel = changeNameInSet(m_currentModel, newName, m_skyboxNames);
            ResourceManager::getSceneResource(m_currentScene)->changeModelName(preName, m_currentModel);
            item->setText(m_currentModel);
            m_currentObjType = CurrentObjectType::MODEL;
            emit currentItemNameChanged(m_currentModel);
        }

	}

    void ResourceModel::onSetEmptyItem()
    {
        emit setEmptyItem();
    }

	void ResourceModel::onShaderUniformChanged(const QString& name, const UniformType& type)
	{
		QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(name);
	}

	void ResourceModel::onShaderResourceChanged(const QString& name, const ShaderResourceType& type)
	{
		QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(name);
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