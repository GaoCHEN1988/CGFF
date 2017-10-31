#ifndef CGFF_LEARNGL_WINDOW_H
#define CGFF_LEARNGL_WINDOW_H

#include "baseWindow.h"
#include "examples/app3DLayer.h"

    class LearnGLWindow : public BaseWindow
    {
        Q_OBJECT

    public:

        LearnGLWindow(QWidget * parent, CGFF::RenderAPI api = CGFF::RenderAPI::OPENGL);
        virtual ~LearnGLWindow();

        inline static LearnGLWindow* getApplication() { return m_instance; }

    private:
        void setupLayers() override;
    private:
        static LearnGLWindow * m_instance;

        QSharedPointer<CGFF::App3DLayer> m_appDLayer;
    };

#endif