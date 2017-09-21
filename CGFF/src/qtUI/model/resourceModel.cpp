#include "resourceModel.h"
#include "graphic/shader/shaderFactory.h"

namespace QTUI {

	using namespace CGFF;

	int ResourceModel::m_cubeCount = 0;
	int ResourceModel::m_planeCount = 0;
	int ResourceModel::m_sphereCount = 0;

	ResourceModel::ResourceModel(QObject * parent)
		: QStandardItemModel(parent)
	{
	}

	QString ResourceModel::addCube()
	{
		QString name = "Cube" + QString::number(++m_cubeCount);
		ResourceManger::getSceneResource(ResourceManger::getScene3DName())->addObject(name, QSharedPointer<Entity>(
			new Entity(MeshFactory::CreateDebugCube(5, QVector4D(0.6, 0.6, 0.6, 1.0),
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugShader()))))))));

		return name;
	}

	QString ResourceModel::addPlane()
	{
		QString name = "Plane" + QString::number(++m_planeCount);
		ResourceManger::getSceneResource(ResourceManger::getScene3DName())->addObject(name,
			QSharedPointer<Entity>(new Entity(MeshFactory::CreateDebugPlane(64, 64, QVector3D(0, 1, 0),
				QVector4D(0.6, 0.6, 0.6, 1.0),
				QSharedPointer<MaterialInstance>(new MaterialInstance(
					QSharedPointer<Material>(new Material(ShaderFactory::DebugShader()))))))));
		return name;
	}

	QString ResourceModel::addSphere()
	{
		QString name = "Sphere" + QString::number(++m_sphereCount);

		return name;
	}

	void ResourceModel::addScene()
	{
		CGFF::ResourceManger::getSceneResource(ResourceManger::getScene3DName());
	}

}