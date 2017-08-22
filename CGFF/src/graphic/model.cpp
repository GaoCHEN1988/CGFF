#include "model.h"
#include "graphic/shader/shaderManager.h"
#include <QFile>

namespace CGFF {

    Model::Model(const QString& path, QSharedPointer<MaterialInstance> materialInstance)
    {
		if (load(path))
		{
			for (QSharedPointer<Mesh>& m : m_meshes)
			{
				m->setMaterial(materialInstance);
			}
		}
        else
            qFatal("Can't load model from ", path);
    }

    Model::~Model()
    {
    }

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		// process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(processMesh(mesh, scene));
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}

	}

	QSharedPointer<Mesh> Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		if (!(mesh->mNumVertices > 0))
			qFatal("No meshes loaded");

		QVector<Vertex> vertices;
		QVector<uint> indices;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			//position
			vertex.position = QVector3D(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			// normals
			vertex.normal = QVector3D(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{

				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vertex.uv = QVector2D(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}
			else
				vertex.uv = QVector2D(0.0f, 0.0f);

			// tangent
			vertex.tangent = QVector3D(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
			// bitangent
			vertex.binormal = QVector3D(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			vertices.push_back(vertex);
		}

		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		ShaderManager::get("AdvancedLighting")->bind();

		QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
		buffer->setData(vertices.size(), (void*)vertices.data());

		LayoutBuffer layout;
		layout.push<QVector3D>("POSITION");
		layout.push<QVector3D>("NORMAL");
		layout.push<QVector2D>("TEXCOORD");
		layout.push<QVector3D>("BINORMAL");
		layout.push<QVector3D>("TANGENT");
		buffer->setLayout(layout);

		QSharedPointer<VertexArray> va =VertexArray::create();
		va->pushBuffer(buffer);

		QSharedPointer<IndexBuffer> ib = IndexBuffer::create((uint*)indices.data(), indices.size());

		//// process materials
		//aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		//// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		//// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		//// Same applies to other texture as the following list summarizes:
		//// diffuse: texture_diffuseN
		//// specular: texture_specularN
		//// normal: texture_normalN
		//// 1. diffuse maps
		//vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//// 2. specular maps
		//vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//// 3. normal maps
		//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		//// 4. height maps
		//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		return QSharedPointer<Mesh>(new Mesh(va, ib, nullptr));
	}

    bool Model::load(const QString& path)
    {
		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			qFatal("ERROR::ASSIMP:: ", importer.GetErrorString());
			return false;
		}

		// process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene);
        
        return true;
    }

    void Model::render(Renderer3D& renderer)
    {
		for (QSharedPointer<Mesh>& m : m_meshes)
		{
			m->render(renderer);
		}
    }
}