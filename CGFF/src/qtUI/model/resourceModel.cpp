#include "resourceModel.h"
#include "graphic/shader/shaderFactory.h"
#include "resource/shaderManager.h"
#include <QFileInfo>

namespace QTUI {

	using namespace CGFF;

	int ResourceModel::m_cubeCount = 0;
	int ResourceModel::m_planeCount = 0;
	int ResourceModel::m_sphereCount = 0;
    int ResourceModel::m_lightCount = 0;
    int ResourceModel::m_skyBoxCount = 0;

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
			name = "Plane" + QString::number(++m_planeCount);
		}

		ResourceManager::getSceneResource(m_currentScene)->addEntity(name,
			QSharedPointer<Entity>(new Entity(MeshFactory::CreatePlane(100, 100, QVector3D(0, 1, 0),
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
			name = "Sphere" + QString::number(++m_sphereCount);
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

    void ResourceModel::addDirectionalLight()
    {
        //To do....

        //QString name = "Directional_Light" + QString::number(++m_lightCount);
        //while (!addNameInSet(name, m_lightNames))
        //{
        //    name = "Directional_Light" + QString::number(++m_lightCount);
        //}
        //QSharedPointer<Light> light = QSharedPointer<Light>(new Light);
        //ResourceManager::getSceneResource(m_currentScene)->addLight(name, light);
        //QStandardItem* itemChild = new QStandardItem(name);
        //m_itemLight->appendRow(itemChild);
        //ResourceManager::UiTransformMats[name] = {};
        //ResourceManager::UiTransformVecs[name] = {};
        //onSetCurrentLight(name);
        //emit lightAdded(name);
    }

    void ResourceModel::translateCurrentObject(const QVector3D& tanslate)
    {
        switch (m_currentObjType)
        {
        case CurrentObjectType::ENTITY:
            translateCurrentEntity(tanslate);
            break;
        case CurrentObjectType::LIGHT:
            translateCurrentLight(tanslate);
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

    void ResourceModel::translateCurrentLight(const QVector3D& tanslate)
    {
        QSharedPointer<Light> light = ResourceManager::getLight(m_currentScene, m_currentEntity);
        if (light)
        {
            ResourceManager::UiTransformMats[m_currentEntity].translateMat.setToIdentity();
            ResourceManager::UiTransformMats[m_currentEntity].translateMat.translate(tanslate);
            light->position = tanslate;
            ResourceManager::UiTransformVecs[m_currentEntity].translateVec = tanslate;
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

    QString ResourceModel::getModelShaderName(const QString& modelName)
    {
        auto model = ResourceManager::getSceneResource(m_currentScene)->getModelObject()[modelName];

        auto modelEntities = model->getEntities();

        QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(modelEntities.begin().key());

        if (shader.isNull())
            return "";

        return shader->getName();
    }

    QVector<CGFF::UniformInfo> ResourceModel::getModelShaderUniformsInfo(const QString& modelName)
    {
        auto model = ResourceManager::getSceneResource(m_currentScene)->getModelObject()[modelName];

        auto modelEntities = model->getEntities();

        QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(modelEntities.begin().key());

        return shader->getShaderUniformsInfo();
    }

    QVector<CGFF::ShaderResourceUniformInfo> ResourceModel::getModelShaderResourcesInfo(const QString& modelName)
    {
        auto model = ResourceManager::getSceneResource(m_currentScene)->getModelObject()[modelName];

        auto modelEntities = model->getEntities();

        QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(modelEntities.begin().key());

        return shader->getShaderResourcesInfo();
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
            QSharedPointer<Material>(new Material(ShaderManager::getShader("DebugSceneShader")))))));

        QFileInfo file(path);
        QString name = file.baseName();
        int tmpCount = 0;
        while (!addNameInSet(name, m_modelObjectNames))
        {
            name = name + QString::number(++tmpCount);
        }

        QSharedPointer<ModelObject> modelobj = QSharedPointer<ModelObject>(new ModelObject(name, model));
        ResourceManager::getSceneResource(m_currentScene)->addModelObject(name, modelobj);

        QStandardItem* itemChild = new QStandardItem(name);
        m_itemModel->appendRow(itemChild);

        for (const QString& key : modelobj->getEntities().keys())
        {
            int tmpCount = 0;
            QString tmpName = key;
            while (!addNameInSet(tmpName, m_entityNames))
            {
                tmpName = tmpName + QString::number(++tmpCount);
            }

            QStandardItem* itemEntity = new QStandardItem(tmpName);
            itemChild->appendRow(itemEntity);

            ResourceManager::getSceneResource(m_currentScene)->addEntity(tmpName, modelobj->getEntities()[key]);

            ResourceManager::UiTransformMats[tmpName] = {};
            ResourceManager::UiTransformVecs[tmpName] = {};
            ResourceManager::UiUniformDatas[tmpName] = {};
        }

        ResourceManager::UiTransformMats[name] = {};
        ResourceManager::UiTransformVecs[name] = {};
        //ResourceManager::UiUniformDatas[name] = {};

        onSetCurrentModel(name);
        emit modelObjectAdded(name);
    }
    void ResourceModel::onAddLight(const CGFF::LightType& type)
    {
        switch (type)
        {
        case CGFF::LightType::DIRECTIONAL:
        {
            addDirectionalLight();
            break;
        }
        case CGFF::LightType::POINT:
        {
            break;
        }
        case CGFF::LightType::SPOT:
        {
            break;
        }
        }
    }

    void ResourceModel::onLoadSkyBox(const QStringList& images)
    {
        QString name = "SkyBox" + QString::number(++m_skyBoxCount);
        while (!addNameInSet(name, m_skyboxNames))
        {
            name = "SkyBox" + QString::number(++m_skyBoxCount);
        }

        QSharedPointer<Texture> environment = TextureManager::getTextureCube(images);
        QSharedPointer<Shader> skybox = ShaderManager::getShader("Internal_SkyBoxShader");

        QSharedPointer<MaterialInstance> skyboxMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(QSharedPointer<Material>(new Material(skybox))));
        skyboxMaterial->setRenderFlag(Material::RenderFlags::DISABLE_DEPTH_TEST);
        skyboxMaterial->setTexture("u_EnvironmentMap", environment);

        QSharedPointer<Entity> skyboxEntity = QSharedPointer<Entity>(new Entity(MeshFactory::CreateSkyCube(skyboxMaterial)));

        ResourceManager::getSceneResource(m_currentScene)->addSkyBox(name, skyboxEntity, environment);

        QStandardItem* itemChild = new QStandardItem(name);
        m_itemSkybox->appendRow(itemChild);

        onSetCurrentSkyBox(name);

        emit skyBoxAdded(name);
    }

    void ResourceModel::onSetCurrentEntity(const QString& name)
    {
        m_currentEntity = name;
        m_currentObjType = CurrentObjectType::ENTITY;
        emit currentEntitySet(m_currentEntity, ResourceManager::UiTransformVecs[m_currentEntity], ResourceManager::UiUniformDatas[m_currentEntity]);
    }

    void ResourceModel::onSetCurrentLight(const QString& name)
    {
        m_currentLight = name;
        m_currentObjType = CurrentObjectType::LIGHT;
        emit currentLightSet(m_currentLight, ResourceManager::UiTransformVecs[m_currentLight], ResourceManager::UiUniformDatas[m_currentLight]);
    }

    void ResourceModel::onSetCurrentSkyBox(const QString& name)
    {
        m_currentSkybox = name;
        m_currentObjType = CurrentObjectType::SKYBOX;
        emit currentSkyBoxSet(name);
    }

    void ResourceModel::onSetCurrentModel(const QString& name)
    {
        m_currentModel = name;
        m_currentObjType = CurrentObjectType::MODEL;
        emit currentModelObjectSet(m_currentModel, ResourceManager::UiTransformVecs[m_currentModel], ResourceManager::UiUniformDatas[m_currentModel]);
    }


	void ResourceModel::onItemChanged(QStandardItem *item)
	{
		QString newName = item->index().data().toString();

		QString parentName = item->index().parent().data(Qt::DisplayRole).toString();

		if (parentName == CGFF::ResourceManager::EntityHierarchyName)
		{
			QString preName = m_currentEntity;
			m_currentEntity = changeNameInSet(m_currentEntity, newName, m_entityNames);
			ResourceManager::getSceneResource(m_currentScene)->changeEntityName(preName, m_currentEntity);
			item->setText(m_currentEntity);
            m_currentObjType = CurrentObjectType::ENTITY;
			emit currentItemNameChanged(m_currentEntity);
		}
        else if (parentName == CGFF::ResourceManager::LightHierarchyName)
		{
			QString preName = m_currentLight;
			m_currentLight = changeNameInSet(m_currentLight, newName, m_lightNames);
			ResourceManager::getSceneResource(m_currentScene)->changeLightName(preName, m_currentLight);
			item->setText(m_currentLight);
            m_currentObjType = CurrentObjectType::LIGHT;
			emit currentItemNameChanged(m_currentLight);
		}
        else if (parentName == CGFF::ResourceManager::SkyBoxHierarchyName)
		{
			QString preName = m_currentSkybox;
			m_currentSkybox = changeNameInSet(m_currentSkybox, newName, m_skyboxNames);
			ResourceManager::getSceneResource(m_currentScene)->changeSkyBoxName(preName, m_currentSkybox);
			item->setText(m_currentSkybox);
			emit currentItemNameChanged(m_currentSkybox);
		}
        else if (parentName == CGFF::ResourceManager::ModelHierarchyName)
        {
            QString preName = m_currentModel;
            m_currentModel = changeNameInSet(m_currentModel, newName, m_modelObjectNames);
            ResourceManager::getSceneResource(m_currentScene)->changeModelName(preName, m_currentModel);
            item->setText(m_currentModel);
            m_currentObjType = CurrentObjectType::MODEL;
            emit currentItemNameChanged(m_currentModel);
        }
        else if (CGFF::ResourceManager::isModelObjectExisted(parentName))
        {
            QString preName = m_currentEntity;
            m_currentEntity = changeNameInSet(m_currentEntity, newName, m_entityNames);
            ResourceManager::getSceneResource(m_currentScene)->changeEntityName(preName, m_currentEntity);
            item->setText(m_currentEntity);
            m_currentObjType = CurrentObjectType::ENTITY;
            emit currentItemNameChanged(m_currentEntity);
        }

	}

    void ResourceModel::onSetEmptyItem()
    {
        emit setEmptyItem();
    }

    void ResourceModel::onSetCurrentEntityShader(const QString& shaderName)
    {
        QSharedPointer<Shader> shader = CGFF::ShaderManager::getShader(shaderName);
        ResourceManager::getSceneResource(m_currentScene)->setEntityShader(m_currentEntity, shader);
        ResourceManager::UiUniformDatas[m_currentEntity].clear();
    }

    void ResourceModel::onSetCurrentModelShader(const QString& shaderName)
    {
        QSharedPointer<Shader> shader = CGFF::ShaderManager::getShader(shaderName);

        auto model = ResourceManager::getSceneResource(m_currentScene)->getModelObject()[m_currentModel];

        auto modelEntities = model->getEntities();
       
        for (const QString& entity_name : modelEntities.keys())
        {
            ResourceManager::getSceneResource(m_currentScene)->setEntityShader(entity_name, shader);
            ResourceManager::UiUniformDatas[entity_name].clear();
        }

        ResourceManager::UiUniformDatas[m_currentModel].clear();
    }

	//void ResourceModel::onShaderUniformChanged(const QString& name, const UniformType& type)
	//{
	//	QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(name);
	//}

	//void ResourceModel::onShaderResourceChanged(const QString& name, const ShaderResourceType& type)
	//{
	//	QSharedPointer<Shader> shader = ResourceManager::getSceneResource(m_currentScene)->getEntityShader(name);
	//}

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