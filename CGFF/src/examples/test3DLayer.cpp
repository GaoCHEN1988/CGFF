#include "test3DLayer.h"
#include "Debug/debugMenu.h"
#include <QImageReader>

#define DEBUG_MENU(name, var, min, max) DebugMenu::add("Test3D/" ## name, var, min, max)

namespace CGFF {

    Test3DLayer::Test3DLayer()
        : Layer3D(QSharedPointer<CGFF::Scene>(new CGFF::Scene()))
    {
		m_mayaCamera = m_scene->getCamera();

		QMatrix4x4 m;
		m.perspective(65.0f, float(CGFF::g_openglWidgetSize.width()) / float(CGFF::g_openglWidgetSize.height()), 0.1f, 1000.0f);
		m_FPSCamera = QSharedPointer<FPSCamera>(new FPSCamera(m));

		m_rotation = 0.0f;
    }

	Test3DLayer::~Test3DLayer()
	{
	}

	QVector3D g_CubeTransform(40, 0, 0);
	QVector3D g_DaggerTransform(20, 0, 0);
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
		QStringList skybox_files =
		{
			"/resource/skybox/sky_xp.jpg",
			"/resource/skybox/sky_xn.jpg",
			"/resource/skybox/sky_yp.jpg",
			"/resource/skybox/sky_yn.jpg",
			"/resource/skybox/sky_zp.jpg",
			"/resource/skybox/sky_zn.jpg"

			//"Resources/skybox/interstellar_skybox/xpos.png",
			//"Resources/skybox/interstellar_skybox/xneg.png",
			//"Resources/skybox/interstellar_skybox/ypos.png",
			//"Resources/skybox/interstellar_skybox/yneg.png",
			//"Resources/skybox/interstellar_skybox/zpos.png",
			//"Resources/skybox/interstellar_skybox/zneg.png"
		};

		//{
		//	QImageReader reader("Resources/skybox/ame_shadow/shadowpeak_nx.tga");
		//	QList<QByteArray> b = reader.supportedImageFormats();
		//	//Test image
		//	QImage posx = reader.read();
		//	QImageReader::ImageReaderError error = reader.error();
		//	QImage negx = QImage(skybox_files[1]);
		//	QImage posy = QImage(skybox_files[2]);
		//	QImage negy = QImage(skybox_files[3]);
		//	QImage posz = QImage(skybox_files[4]);
		//	QImage negz = QImage(skybox_files[5]);
		//}

		QSharedPointer<TextureCube> environment = TextureCube::createFromFiles(skybox_files);
		QSharedPointer<Shader> skybox = Shader::createFromFile("Skybox", "/shaders/Skybox.vert", "/shaders/Skybox.frag");

		QSharedPointer<Material> skyboxMaterial = QSharedPointer<Material>(new Material(skybox));
		skyboxMaterial->setRenderFlag(Material::RenderFlags::DISABLE_DEPTH_TEST);
		skybox->bind();
		m_skyboxMaterial = QSharedPointer<MaterialInstance>(new MaterialInstance(skyboxMaterial));
		m_skyboxMaterial->setTexture("u_EnvironmentMap", environment);

		QSharedPointer<Entity> skyboxEntity = QSharedPointer<Entity>(new Entity(MeshFactory::CreateSkyCube(m_skyboxMaterial)));
		m_scene->add(skyboxEntity);

		QSharedPointer<Shader> pbrShader = Shader::createFromFile("AdvancedLighting", "/shaders/AdvancedLighting.vert", "/shaders/AdvancedLighting.frag");
		ShaderManager::add(pbrShader);
		QSharedPointer<PBRMaterial> material = QSharedPointer<PBRMaterial>(new PBRMaterial(pbrShader));

		m_daggerMaterial = QSharedPointer<PBRMaterial>(new PBRMaterial(pbrShader));
		m_daggerMaterial->setEnviromentMap(environment);
		{
			m_daggerMaterial->setAlbedoMap(Texture2D::createFromFile("/resource/Dagger/Textures/Dagger_Albedo.tga"));
			m_daggerMaterial->setSpecularMap(Texture2D::createFromFile("/resource/Dagger/Textures/Dagger_Specular.tga"));
			m_daggerMaterial->setGlossMap(Texture2D::createFromFile("/resource/Dagger/Textures/Dagger_Gloss.tga"));
			m_daggerMaterial->setNormalMap(Texture2D::createFromFile("/resource/Dagger/Textures/Dagger_Normals.tga"));
		}

		QSharedPointer<Model> daggerModel = QSharedPointer<Model>(new Model("/resource/Dagger/Dagger.obj", QSharedPointer<MaterialInstance>(new MaterialInstance(m_daggerMaterial))));
		
		QMatrix4x4 trans_dagger;
		trans_dagger.translate(g_DaggerTransform);
		trans_dagger.scale(0.2);

		m_dagger = QSharedPointer<Entity>(new Entity(daggerModel->getMesh(), trans_dagger));
		m_scene->add(m_dagger);

		QMatrix4x4 trans_cube;
		trans_cube.translate(g_CubeTransform);

		QSharedPointer<PBRMaterial> cubeMaterial = QSharedPointer<PBRMaterial>(new PBRMaterial(pbrShader));
		cubeMaterial->setEnviromentMap(environment);
		QSharedPointer<Model> cubeModel = QSharedPointer<Model>(new Model("/resource/RoundedCube.obj", QSharedPointer<MaterialInstance>(new MaterialInstance(cubeMaterial))));
		m_cube = QSharedPointer<Entity>(new Entity(cubeModel->getMesh(), trans_cube));
		m_scene->add(m_cube);

		QSharedPointer<LightSetup> lights = QSharedPointer<LightSetup>(new LightSetup());
		m_light = QSharedPointer<Light>(new Light(QVector3D(0.8f, 0.8f, 0.8f)));
		lights->add(m_light);
		m_scene->pushLightSetup(lights);

		//DebugMenu::add("Light Direction", &lights->getLights()[0]->direction, -1.0f, 1.0f);
		//DebugMenu::add("Light Intensity", &lights->getLights()[0]->intensity, 0, 100);
		//DebugMenu::add("Dagger", &g_DaggerTransform, 0, 100);

		DEBUG_MENU("Light Direction", &lights->getLights()[0]->direction, -1.0f, 1.0f);
		DEBUG_MENU("Light Intensity", &lights->getLights()[0]->intensity, 0, 100);
		DEBUG_MENU("Dagger", &g_DaggerTransform, 0, 100);
    }

    void Test3DLayer::render()
    {
		if (!m_dagger.isNull())
		{
			TransformComponent* dagger = m_dagger->getComponent<TransformComponent>();
			QMatrix4x4 trans_dagger;
			trans_dagger.translate(g_DaggerTransform);
			trans_dagger.scale(0.2);
			dagger->transform = trans_dagger;
		}

		// Remove the translation part for skybox
		QMatrix4x4 vm = m_scene->getCamera()->getViewMatrix();
		m_skyboxMaterial->setUniform("u_ViewMatrix", QMatrix4x4(QMatrix3x3(vm.toGenericMatrix<3,3>())));

		Layer3D::render();

		GLenum error = CGFF::GL->glGetError();
		if (error != GL_NO_ERROR)
		{
			//To do: show error in logging system
			qFatal("Opengl error!");
		}
    }

    void Test3DLayer::resize(int width, int height) 
    {
		Layer3D::resize(width, height);
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

	void Test3DLayer::closeEvent(QEvent *event)
	{
		Layer3D::closeEvent(event);
		m_Spheres.clear();
		m_plane.clear();
		m_dagger.clear();
		m_cube.clear();
		m_daggerMaterial.clear();
		m_skyboxMaterial.clear();
	}
}