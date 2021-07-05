#pragma once

#include <QWidget>
#include <QTimer>
#include <QMovie>
#include "userListViewModel.h"
#include "ui_userListView.h"
#include "userListViewDelegate.h"

class userListView : public QWidget
{
	Q_OBJECT
public:
	explicit userListView(QWidget *parent = Q_NULLPTR);
	~userListView();

private:
	Ui::testListView ui;
	vUserListViewModel m_userListViewModel;
	QMovie movie; //”√¿¥Ω‚Œˆgif
	//QTimer m_updateTimer;
	vUserListViewDelegate m_userListViewDelegate;
};