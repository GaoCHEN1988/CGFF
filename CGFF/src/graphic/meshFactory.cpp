#include "meshFactory.h"
#include "../utils/types.h"
#include "renderable2d.h"

namespace CGFF {
    namespace MeshFactory {

		QSharedPointer<Mesh> CreateQuad(float x, float y, float width, float height, QSharedPointer<MaterialInstance> material)
		{
			struct QuadVertex
			{
				QVector3D position;
				QVector2D uv;
			};

			QuadVertex data[4];

			data[0].position = QVector3D(x, y, 0);
			data[0].uv = QVector2D(0, 1);

			data[1].position = QVector3D(x + width, y, 0);
			data[1].uv = QVector2D(1, 1);

			data[2].position = QVector3D(x + width, y + height, 0);
			data[2].uv = QVector2D(1, 0);

			data[3].position = QVector3D(x, y + width, 0);
			data[3].uv = QVector2D(0, 0);

			QSharedPointer<VertexArray> va = VertexArray::create();
			va->bind();
			QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
			buffer->setData(sizeof(QuadVertex) * 4, data);
			LayoutBuffer layout;
			layout.push<QVector3D>("POSITION");
			layout.push<QVector2D>("TEXCOORD");
			buffer->setLayout(layout);
			
			va->pushBuffer(buffer);
			uint indices[6] = { 0, 1, 2, 2, 3, 0, };
			QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 6);

			va->unBind();
			return QSharedPointer<Mesh>(new Mesh(va, ib, material));
		}

		QSharedPointer<Mesh> CreateQuad(const QVector2D& position, const QVector2D& size, QSharedPointer<MaterialInstance> material)
		{
			return CreateQuad(position.x(), position.y(), size.x(), size.y(), material);
		}

        QSharedPointer<Mesh> CreateScreenQuad(QSharedPointer<CGFF::MaterialInstance> material)
        {
            struct QuadVertex
            {
                QVector3D position;
                QVector2D uv;
            };

            QuadVertex data[4];

            data[0].position = QVector3D(-1.0, 1.0, 0.0f);
            data[0].uv = QVector2D(0.0f, 1.0f);

            data[1].position = QVector3D(-1.0f, -1.0f, 0.0f);
            data[1].uv = QVector2D(0.0f, 0.0f);

            data[2].position = QVector3D(1.0f, 1.0f, 0.0f);
            data[2].uv = QVector2D(1.0f, 1.0f);

            data[3].position = QVector3D(1.0f, -1.0f, 0.0f);
            data[3].uv = QVector2D(1.0f, 0.0f);

            QSharedPointer<VertexArray> va = VertexArray::create();
            va->bind();
            QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
            buffer->setData(sizeof(QuadVertex) * 4, data);
            LayoutBuffer layout;
            layout.push<QVector3D>("POSITION");
            layout.push<QVector2D>("TEXCOORD");
            buffer->setLayout(layout);

            va->pushBuffer(buffer);
            uint indices[6] = { 0, 1, 2, 2, 3, 1, };
            QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 6);

            va->unBind();
            return QSharedPointer<Mesh>(new Mesh(va, ib, material));
        }

		QSharedPointer<Mesh> CreateCube(float size, QSharedPointer<MaterialInstance> material)
		{
			struct CubeVertex
			{
				QVector3D position;
			};

			CubeVertex data[8];

			data[0].position = QVector3D(-size / 2.0f, -size / 2.0f, size / 2.0f);
			data[1].position = QVector3D(size / 2.0f, -size / 2.0f, size / 2.0f);
			data[2].position = QVector3D(size / 2.0f, size / 2.0f, size / 2.0f);
			data[3].position = QVector3D(-size / 2.0f, size / 2.0f, size / 2.0f);
			data[4].position = QVector3D(-size / 2.0f, -size / 2.0f, -size / 2.0f);
			data[5].position = QVector3D(size / 2.0f, -size / 2.0f, -size / 2.0f);
			data[6].position = QVector3D(size / 2.0f, size / 2.0f, -size / 2.0f);
			data[7].position = QVector3D(-size / 2.0f, size / 2.0f, -size / 2.0f);

			QSharedPointer<VertexArray> va = VertexArray::create();
			va->bind();
			QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
			buffer->setData(8 * sizeof(CubeVertex), data);
			LayoutBuffer layout;
			layout.push<QVector3D>("position");
			buffer->setLayout(layout);

			va->pushBuffer(buffer);

			uint indices[36] =
			{
				0, 1, 2, 2, 3, 0,
				3, 2, 6, 6, 7, 3,
				7, 6, 5, 5, 4, 7,
				4, 0, 3, 3, 7, 4,
				0, 1, 5, 5, 4, 0,
				1, 5, 6, 6, 2, 1
			};

			QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 36);

			va->unBind();

			return QSharedPointer<Mesh>(new Mesh(va, ib, material));
		}

		QSharedPointer<Mesh> CreateDebugCube(float size, const QVector4D& color, QSharedPointer<MaterialInstance> material)
		{
			struct CubeDebugVertex
			{
				QVector3D position;
				QVector4D color;
				QVector3D normal;
			};

			CubeDebugVertex data[8];

			data[0].position = QVector3D(-size / 2.0f, 0, size / 2.0f);
			data[0].color = color;
			data[1].position = QVector3D(size / 2.0f, 0, size / 2.0f);
			data[1].color = color;
			data[2].position = QVector3D(size / 2.0f, size , size / 2.0f);
			data[2].color = color;
			data[3].position = QVector3D(-size / 2.0f, size, size / 2.0f);
			data[3].color = color;
			data[4].position = QVector3D(-size / 2.0f, 0, -size / 2.0f);
			data[4].color = color;
			data[5].position = QVector3D(size / 2.0f, 0, -size / 2.0f);
			data[5].color = color;
			data[6].position = QVector3D(size / 2.0f, size, -size / 2.0f);
			data[6].color = color;
			data[7].position = QVector3D(-size / 2.0f, size, -size / 2.0f);
			data[7].color = color;

			data[0].normal = QVector3D(-1.0f, -1.0f, 1.0f);
			data[1].normal = QVector3D(1.0f, -1.0f, 1.0f);
			data[2].normal = QVector3D(1.0f, 1.0f, 1.0f);
			data[3].normal = QVector3D(-1.0f, 1.0f, 1.0f);
			data[4].normal = QVector3D(-1.0f, -1.0f, -1.0f);
			data[5].normal = QVector3D(1.0f, -1.0f, -1.0f);
			data[6].normal = QVector3D(1.0f, 1.0f, -1.0f);
			data[7].normal = QVector3D(-1.0f, 1.0f, -1.0f);

			QSharedPointer<VertexArray> va = VertexArray::create();
			va->bind();
			QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
			buffer->setData(8 * sizeof(CubeDebugVertex), data);
			LayoutBuffer layout;
			layout.push<QVector3D>("position");
			layout.push<QVector4D>("color");
			layout.push<QVector3D>("normal");
			buffer->setLayout(layout);

			va->pushBuffer(buffer);

			uint indices[36] =
			{
				0, 1, 2, 2, 3, 0,
				3, 2, 6, 6, 7, 3,
				7, 6, 5, 5, 4, 7,
				4, 0, 3, 3, 7, 4,
				0, 1, 5, 5, 4, 0,
				1, 5, 6, 6, 2, 1
			};

			QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 36);

			va->unBind();

			return QSharedPointer<Mesh>(new Mesh(va, ib, material));
		}

		QSharedPointer<Mesh> CreateSkyCube(QSharedPointer<MaterialInstance> material)
		{
			return CreateCube(2.0f, material);
		}

		QSharedPointer<Mesh> CreatePlane(float width, float height, const QVector3D& normal, QSharedPointer<MaterialInstance> material)
		{
			QVector3D vec = normal * 90.0f;

			QMatrix4x4 rotation;
			rotation.rotate(vec.x(), QVector3D(0, 0, 1));
			rotation.rotate(vec.y(), QVector3D(0, 1, 0));
			rotation.rotate(vec.z(), QVector3D(1, 0, 0));

			Vertex data[4];
			memset(data, 0, 4 * sizeof(Vertex));

			QMatrix4x4 tmpRotate;
			//
			data[0].position = rotation * QVector3D(-width / 2.0f, 0.0f, -height / 2.0f);
			data[0].normal = normal;
			data[0].uv = QVector2D(0.0f, 0.0f);	

			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 1, 0));
			data[0].binormal = tmpRotate * normal;
			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 0, 1));
			data[0].tangent = tmpRotate * normal;
			//
			data[1].position = rotation * QVector3D(-width / 2.0f, 0.0f, height / 2.0f);
			data[1].normal = normal;
			data[1].uv = QVector2D(0.0f, 1.0f);

			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 1, 0));
			data[1].binormal = tmpRotate * normal;
			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 0, 1));
			data[1].tangent = tmpRotate * normal;
			//
			data[2].position = rotation * QVector3D(width / 2.0f, 0.0f, height / 2.0f);
			data[2].normal = normal;
			data[2].uv = QVector2D(1.0f, 1.0f);

			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 1, 0));
			data[2].binormal = tmpRotate * normal;
			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 0, 1));
			data[2].tangent = tmpRotate * normal;
			//
			data[3].position = rotation * QVector3D(width / 2.0f, 0.0f, -height / 2.0f);
			data[3].normal = normal;
			data[3].uv = QVector2D(1.0f, 0.0f);
			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 1, 0));
			data[3].binormal = tmpRotate * normal;
			tmpRotate.setToIdentity();
			tmpRotate.rotate(90.0f, QVector3D(0, 0, 1));
			data[3].tangent = tmpRotate * normal;

			QSharedPointer<VertexArray> va = VertexArray::create();
			va->bind();
			QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
			buffer->setData(4 * sizeof(Vertex), data);
			LayoutBuffer layout;
			layout.push<QVector3D>("POSITION");
			layout.push<QVector3D>("NORMAL");
			layout.push<QVector2D>("TEXCOORD");
			layout.push<QVector3D>("BINORMAL");
			layout.push<QVector3D>("TANGENT");
			buffer->setLayout(layout);

			va->pushBuffer(buffer);

			uint indices[6] =
			{
				0, 1, 2,
				2, 3, 0
			};

			QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 6);

			va->unBind();

			return QSharedPointer<Mesh>(new Mesh(va, ib, material));
		}

		QSharedPointer<Mesh> CreateDebugPlane(float width, float height, const QVector3D& normal, const QVector4D& color, QSharedPointer<MaterialInstance> material)
		{
			struct PlaneVertex
			{
				QVector3D position;
				QVector4D color;
				QVector3D normal;
			};

			QVector3D vec = normal * 90.0f;

			QMatrix4x4 rotation;
			rotation.rotate(vec.x(), QVector3D(0, 0, 1));
			rotation.rotate(vec.y(), QVector3D(0, 1, 0));
			rotation.rotate(vec.z(), QVector3D(1, 0, 0));

			PlaneVertex data[4];
			memset(data, 0, 4 * sizeof(PlaneVertex));

			QMatrix4x4 tmpRotate;
			//
			data[0].position = rotation * QVector3D(-width / 2.0f, 0.0f, -height / 2.0f);
			data[0].color = color;
			data[0].normal = normal;

			data[1].position = rotation * QVector3D(-width / 2.0f, 0.0f, height / 2.0f);
			data[1].color = color;
			data[1].normal = normal;

			data[2].position = rotation * QVector3D(width / 2.0f, 0.0f, height / 2.0f);
			data[2].color = color;
			data[2].normal = normal;

			data[3].position = rotation * QVector3D(width / 2.0f, 0.0f, -height / 2.0f);
			data[3].color = color;
			data[3].normal = normal;

			QSharedPointer<VertexArray> va = VertexArray::create();
			va->bind();
			QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
			buffer->setData(4 * sizeof(PlaneVertex), data);
			LayoutBuffer layout;
			layout.push<QVector3D>("POSITION");
			layout.push<QVector4D>("COLOR");
			layout.push<QVector3D>("NORMAL");
			buffer->setLayout(layout);

			va->pushBuffer(buffer);

			uint indices[6] =
			{
				0, 1, 2,
				2, 3, 0
			};

			QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 6);

			va->unBind();

			return QSharedPointer<Mesh>(new Mesh(va, ib, material));
		}

		QSharedPointer<Mesh> CreateLine(const QVector3D& start, const QVector3D& end, const QVector4D& color, QSharedPointer<MaterialInstance> material)
		{
			struct LineVertex
			{
				QVector3D position;
				QVector4D color;
			};

			LineVertex data[2];

			data[0].position = start;
			data[0].color = color;
			data[1].position = end;
			data[1].color = color;

			QSharedPointer<VertexArray> va = VertexArray::create();
			va->bind();
			QSharedPointer<VertexBuffer> buffer = VertexBuffer::create(BufferUsage::STATIC);
			buffer->setData(2 * sizeof(LineVertex), data);
			LayoutBuffer layout;
			layout.push<QVector3D>("position");
			layout.push<QVector4D>("color");
			buffer->setLayout(layout);

			va->pushBuffer(buffer);

			uint indices[2] =
			{
				0, 1
			};

			QSharedPointer<IndexBuffer> ib = IndexBuffer::create(indices, 2);

			va->unBind();

			return QSharedPointer<Mesh>(new Mesh(va, ib, material, QVector<MeshTexture>(), DrawMode::LINES));
		}
    }
}