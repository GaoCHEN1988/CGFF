#include "test3DLayer.h"
#include "Debug/debugMenu.h"

namespace CGFF {

    Test3DLayer::Test3DLayer()
        : Layer3D(QSharedPointer<CGFF::Scene>(new CGFF::Scene()))
    {
		m_mayaCamera = m_scene->getCamera();

		QMatrix4x4 m;
		m.perspective(65.0f, 16.0f / 9.0f, 0.1f, 100.0f);
		m_FPSCamera = QSharedPointer<FPSCamera>(new FPSCamera(m));

		m_rotation = 0.0f;
    }

	QVector3D g_CubeTransform(-10, 10, 0);
	QVector3D g_DaggerTransform(0, 20, 0);
	QVector4D g_SphereColor(0.0f, 0.0f, 0.0f, 1.0f);
	QVector3D g_SphereSpecularColor(1.0f, 1.0f, 0.6f);

	float g_DaggerGloss = 0.5f;

	QSharedPointer<Shader> shadowPassShader;
	QSharedPointer<FramebufferDepth> g_DepthBuffer;
	QSharedPointer<TextureDepth> g_ShadowMap;

	QString materialInputs[5] =
	{
		"CastIron",
		"WornWood",
		"GunMetal",
		"ABSRed",
		"Custom"
	};

	enum Materials : uint
	{
		CAST_IRON = 0,
		WORN_WOOD,
		GUN_METAL,
		ABS_RED,
		CUSTOM
	};

    void Test3DLayer::init()
    {
		QString files[6] =
		{
			"Resources/skybox/sky_xp.png",
			"Resources/skybox/sky_xn.png",
			"Resources/skybox/sky_yp.png",
			"Resources/skybox/sky_yn.png",
			"Resources/skybox/sky_zp.png",
			"Resources/skybox/sky_zn.png"
		};

		QStringList environmentFiles =
		{
			"Resources/pbr/cubemap/CubeMap0.tga",
			"Resources/pbr/cubemap/CubeMap1.tga",
			"Resources/pbr/cubemap/CubeMap2.tga",
			"Resources/pbr/cubemap/CubeMap3.tga",
			"Resources/pbr/cubemap/CubeMap4.tga",
			"Resources/pbr/cubemap/CubeMap5.tga",
			"Resources/pbr/cubemap/CubeMap6.tga",
			"Resources/pbr/cubemap/CubeMap7.tga",
			"Resources/pbr/cubemap/CubeMap8.tga",
			"Resources/pbr/cubemap/CubeMap9.tga",
			"Resources/pbr/cubemap/CubeMap10.tga"
		};
		QSharedPointer<TextureCube> environment = TextureCube::createFromVCross(environmentFiles, 11);

		QSharedPointer<Shader> pbrShader = Shader::createFromFile("AdvancedLighting", "src/graphic/shaders/AdvancedLighting.vert", "src/graphic/shaders/AdvancedLighting.frag");
		ShaderManager::add(pbrShader);
		QSharedPointer<PBRMaterial> material = QSharedPointer<PBRMaterial>(new PBRMaterial(pbrShader));

		m_daggerMaterial = QSharedPointer<PBRMaterial>(new PBRMaterial(pbrShader));
		m_daggerMaterial->setEnviromentMap(environment);
		{
			TextureLoadOptions options(false, true);
			m_daggerMaterial->setAlbedoMap(Texture2D::createFromFile("res/Dagger/Textures/Dagger_Albedo.tga", TextureParameters(), options));
			m_daggerMaterial->setSpecularMap(Texture2D::createFromFile("res/Dagger/Textures/Dagger_Specular.tga", TextureParameters(), options));
			m_daggerMaterial->setGlossMap(Texture2D::createFromFile("res/Dagger/Textures/Dagger_Gloss.tga", TextureParameters(), options));
			m_daggerMaterial->setNormalMap(Texture2D::createFromFile("res/Dagger/Textures/Dagger_Normals.tga", TextureParameters(), options));
		}

		QSharedPointer<Model> daggerModel = QSharedPointer<Model>(new Model("res/models/Dagger.spm", QSharedPointer<MaterialInstance>(new MaterialInstance(m_daggerMaterial))));
		QMatrix4x4 trans_dagger;
		trans_dagger.translate(g_DaggerTransform);
		//Test
		m_dagger = QSharedPointer<Entity>(new Entity(daggerModel->getMeshes().front(), trans_dagger));
		m_scene->add(m_dagger);
    }

 //   void Test3DLayer::render()
 //   {
 //      
 //   }

	//void Test3DLayer::update()
	//{

	//}

	//void Test3DLayer::tick()
	//{

	//}

    void Test3DLayer::resize(int width, int height) 
    {
        CGFF::GL->glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        Layer3D::getScene()->getCamera()->resize(width, height);
    }

    void Test3DLayer::mousePressEvent(QMouseEvent *event)
    {
        Layer3D::getScene()->getCamera()->mousePressEvent(event);
    }
    void Test3DLayer::mouseMoveEvent(QMouseEvent *event)
    {
        Layer3D::getScene()->getCamera()->mouseMoveEvent(event);
    }

    void Test3DLayer::mouseReleaseEvent(QMouseEvent *event) 
    {
        Layer3D::getScene()->getCamera()->mousePressEvent(event);
    }

    void Test3DLayer::keyPressEvent(QKeyEvent *event) 
    {
		switch (event->key())
		{
		case (Qt::Key_R):
		{
			ShaderManager::reload("AdvancedLighting");
			break;
		}
		case (Qt::Key_C):
		{
			m_scene->setCamera(m_scene->getCamera() == m_mayaCamera ? m_FPSCamera : m_mayaCamera);
			break;
		}
		}
    }
}