#ifndef DEBUG_LAYER_H
#define DEBUG_LAYER_H

#include "graphic/layer/layer2D.h"
#include "graphic/sprite.h"
#include "graphic/label.h"
#include "debugMenu.h"

namespace CGFF {

    class DebugLayer : public Layer2D
    {
    public:
        DebugLayer(QSize screenSize);
        virtual ~DebugLayer() {};

        void init() override;
		void init(QSharedPointer<Renderer2D> renderer, QSharedPointer<Material> material) override;
        void render() override;
        void resize(int width, int height) override;

        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void update() override;

	public:
		inline static DebugLayer* GetInstance() { return s_instance; }

		static void drawSprite(QSharedPointer<Sprite> sprite);
		static void drawTexture(QSharedPointer<Texture2D> texture, const QVector2D& position = QVector2D(), const QVector2D& size = QVector2D(80.0f, 80.0f));

	private:
		static DebugLayer* s_instance;

	private:
		//Application& m_Application;
		QSharedPointer<Label> m_FPSLabel;
		QSharedPointer<Label> m_memoryUsageLabel;
		QSharedPointer<Label> m_frametimeLabel;
		QVector<QSharedPointer<Sprite>> m_tempSprites;
    };

}

#endif
