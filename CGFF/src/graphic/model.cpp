#include "model.h"
#include "graphic/shader/shaderManager.h"
#include "system/fileSystem/vfs.h"

namespace CGFF {

    Model::Model(const QString& path, QSharedPointer<MaterialInstance> materialInstance)
    {
		if (load(path))
		{
			m_mesh->setMaterial(materialInstance);
		}
        else
            qFatal("Can't load model from ", path);
    }

    Model::~Model()
    {
    }

	void Model::insertVertex(const QVector3D& position, const QVector3D& normal, const QVector2D& uv, const QVector3D& binormal, const QVector3D& tangent)
	{
		Vertex vertex = { position, normal, uv, binormal, tangent };
		auto lookup = m_indexMapping.find(vertex);
		if (lookup != m_indexMapping.end())
		{
			m_indices.push_back(lookup.value());
		}
		else
		{
			int index = m_vertices.size();
			m_indexMapping[vertex] = index;
			m_indices.push_back(index);
			m_vertices.push_back(vertex);
		}
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
			insertVertex(position, normal, uv, binormal, tangent);
		}
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

		//// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			qFatal("ERROR::ASSIMP:: ", importer.GetErrorString());
			return false;
		}

		m_vertices.clear();
		m_indices.clear();

		// process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene);

		ShaderManager::get("AdvancedLighting")->bind();
		QSharedPointer<VertexArray> va = VertexArray::create();
		va->bind();
		QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
		buffer->setData(m_vertices.size()* sizeof(Vertex), (void*)m_vertices.data());

		LayoutBuffer layout;
		layout.push<QVector3D>("POSITION");
		layout.push<QVector3D>("NORMAL");
		layout.push<QVector2D>("TEXCOORD");
		layout.push<QVector3D>("BINORMAL");
		layout.push<QVector3D>("TANGENT");

		buffer->setLayout(layout);

		va->pushBuffer(buffer);

		QSharedPointer<IndexBuffer> ib = IndexBuffer::create((uint*)m_indices.data(), m_indices.size());

		va->unBind();
		m_mesh = QSharedPointer<Mesh>(new Mesh(va, ib, nullptr));
        
        return true;
    }

    void Model::render(Renderer3D& renderer)
    {
		m_mesh->render(renderer);
    }
}