#ifndef CGFF_RENDERER_2D_H
#define CGFF_RENDERER_2D_H

#include "utils/qtopengl.h"
#include "maths/qtmaths.h"
#include "mask.h"
#include "postfx/postEffects.h"


namespace CGFF {

	class Renderable2D;

    enum class RenderTarget
    {
        SCREEN = 0,
        BUFFER = 1
    };

	class Renderer2D
	{
	protected:
		Renderer2D()
            : m_mask(nullptr)
            , m_postEffectsEnabled(true)
            , m_target(RenderTarget::SCREEN)
            , m_postEffects(nullptr)
		{       
			m_transformationStack.push_back(QMatrix4x4());

			m_tranformationBack = &m_transformationStack.back();
		}
	public:
		virtual void submit(QSharedPointer<Renderable2D>& renderable) = 0;
		virtual void flush() = 0;
		virtual void begin() {}
		virtual void end() {}
        
        virtual void drawString(QString text, const QVector3D& position, int width, int height, QVector4D& color, QFont font = QFont("Sans")) {};
        virtual void drawLine(float x0, float y0, float x1, float y1, QVector4D color = QVector4D(1, 1, 1, 1), float thickness = 1.0f) {}
        virtual void drawLine(const QVector2D& start, const QVector2D& end, QVector4D color = QVector4D(1, 1, 1, 1), float thickness = 1.0f) {}
        virtual void drawRect(float x, float y, float width, float height, QVector4D color = QVector4D(1, 1, 1, 1), float thickness = 1.0f) {}
        virtual void drawRect(const QRect& rectangle, QVector4D color = QVector4D(1, 1, 1, 1)) {}
        virtual void fillRect(float x, float y, float width, float height, QVector4D color = QVector4D(1, 1, 1, 1)) {}
        virtual void fillRect(const QRect& rectangle, QVector4D color = QVector4D(1, 1, 1, 1)) {}


		void push(QMatrix4x4 matrix, bool override = false)
		{
			if(override)
				m_transformationStack.push_back(matrix);
			else
				m_transformationStack.push_back(m_transformationStack.back()*matrix);

			m_tranformationBack = &m_transformationStack.back();
		}

		void pop() 
		{
			if(m_transformationStack.size()>0)
				m_transformationStack.pop_back();

			m_tranformationBack = &m_transformationStack.back();
			//To do: Add to log system
		}

        void setMask(QSharedPointer<CGFF::Mask> mask)
        {
            m_mask = mask;
        }

        inline void setRenderTarget(RenderTarget target) { m_renderTarget = target; }
        inline const RenderTarget getRenderTarget() const { return m_renderTarget; }

        inline void setPostEffects(bool enabled) { m_postEffectsEnabled = enabled; }
        inline bool getPostEffects() const { return m_postEffectsEnabled; }
        inline void addPostEffectsPass(QSharedPointer<PostEffectsPass>& pass) { m_postEffects->push(pass); }

	protected:
		QVector<QMatrix4x4> m_transformationStack;
		QMatrix4x4* m_tranformationBack;
        QSharedPointer<CGFF::Mask> m_mask;
        RenderTarget m_renderTarget;

        RenderTarget m_target;
        QSharedPointer<PostEffects> m_postEffects;
        bool m_postEffectsEnabled;
	};
}

#endif