#include "model.h"
#include "system/fileSystem/vfs.h"

namespace CGFF {

    Model::Model(const QString& path, const QSharedPointer<MaterialInstance>& materialInstance)
        : m_materialInstance(materialInstance)
        , m_directoryPath("")
    {
		if (!load(path))
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
			processMesh(mesh, scene);
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	void Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		if (!(mesh->mNumVertices > 0))
			qFatal("No meshes loaded");

        QVector<Vertex> vertices;
        QVector<int> indices;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			//position
			QVector3D position = QVector3D(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			// normals
			QVector3D normal = QVector3D(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			QVector2D uv;
			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{

				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				uv = QVector2D(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}
			else
				uv = QVector2D(0.0f, 0.0f);

			// tangent
			QVector3D tangent = QVector3D(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
			// bitangent
			QVector3D binormal = QVector3D(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			//insertVertex(position, normal, uv, binormal, tangent);

            vertices.push_back({ position, normal, uv, binormal, tangent });
		}

        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        loadMaterialTextures(material, aiTextureType_DIFFUSE, pbr_diffuseMap, m_textures);

        // 2. specular maps
        loadMaterialTextures(material, aiTextureType_SPECULAR, pbr_specularMap, m_textures);
       
        // 3. normal maps
        loadMaterialTextures(material, aiTextureType_HEIGHT, pbr_normalMap, m_textures);

        // 4. height maps
        loadMaterialTextures(material, aiTextureType_AMBIENT, pbr_heightMap, m_textures);

        //Add new mesh to mesh vector
        QSharedPointer<VertexArray> va = VertexArray::create();
        va->bind();
        QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
        buffer->setData(vertices.size()* sizeof(Vertex), (void*)vertices.data());

        LayoutBuffer layout;
        layout.push<QVector3D>("POSITION");
        layout.push<QVector3D>("NORMAL");
        layout.push<QVector2D>("TEXCOORD");
        layout.push<QVector3D>("BINORMAL");
        layout.push<QVector3D>("TANGENT");

        buffer->setLayout(layout);

        va->pushBuffer(buffer);

        QSharedPointer<IndexBuffer> ib = IndexBuffer::create((uint*)indices.data(), indices.size());

        va->unBind();

        m_meshes.append(QSharedPointer<Mesh>(new Mesh(va, ib, m_materialInstance, m_textures)));
	}

	uchar* ReadBytes(FILE* file, uchar* buffer, uint size)
	{
		fread(buffer, 1, size, file);
		return buffer;
	}

    bool Model::load(const QString& path)
    {
		QString filename;
		if (!VFS::get()->resolvePhysicalPath(path, filename))
			qFatal("Can't load file: ", path);

        m_directoryPath = path.left(path.lastIndexOf('/')+1);

		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
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

    void Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, QString typeName, QVector<MeshTexture>& outMeshTextureVector)
    {
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            QString path(str.C_Str());
            QSharedPointer<Texture> texture = TextureManager::getTexture2D(m_directoryPath+path);
            outMeshTextureVector.push_back({ texture, typeName });
        }
    }

    void Model::render(Renderer3D& renderer)
    {
		//m_mesh->render(renderer);

        for (QSharedPointer<Mesh>& mesh : m_meshes)
        {
            mesh->render(renderer);
        }
    }
}