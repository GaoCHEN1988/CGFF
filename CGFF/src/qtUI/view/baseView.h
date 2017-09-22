#ifndef QTUI_BASE_VIEW_H
#define QTUI_BASE_VIEW_H

#include "qtUI/model/resourceModel.h"
#include <QWidget>

namespace QTUI {

	class BaseView : public QWidget
	{
		Q_OBJECT

	public:

		BaseView(QWidget *parent = Q_NULLPTR);
		virtual ~BaseView() {};

		virtual void setModel(ResourceModel * model)
		{
			m_model = model;
		}

	protected:
		ResourceModel * m_model;
	};

}

#endif