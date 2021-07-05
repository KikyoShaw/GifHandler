#include "userListView.h"

userListView::userListView(QWidget *parent /* = Q_NULLPTR */)
	:QWidget(parent)
{
	ui.setupUi(this);

	ui.listView->setModel(&m_userListViewModel);
	ui.listView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.listView->setUpdatesEnabled(true);
	//ui.listView->setItemDelegate(new vUserListViewDelegate());
	ui.listView->setItemDelegate(&m_userListViewDelegate);
	//ui.listView->installEventFilter(this);

	//ģ������
	for (int i = 0; i < 100; i++) {
		UserInfo info;
		info.userId = QString("1100110%1").arg(i);
		info.nickName = QStringLiteral("ʮ������");
		info.userSlogn = QStringLiteral("�㳤�ú������ǾͲ�Ҫ���̫��");
		info.fileName = "test.gif";
		m_userListViewModel.addInfoToModel(info);
	}

	movie.setFileName("test.gif");
	connect(&movie, &QMovie::updated, this, [=] {
		QImage _image = movie.currentImage();
		m_userListViewDelegate.setImage(_image);
		ui.listView->update();
	}); //updated()���ŵ���һ���µ�֡
	movie.start();

	//��ʱ����ʱˢ��
	//m_updateTimer.setTimerType(Qt::PreciseTimer);
	//m_updateTimer.setInterval(1000);
	//connect(&m_updateTimer, &QTimer::timeout, this, [=]() {
	//	ui.listView->update();
	//});
	//m_updateTimer.start();
}

userListView::~userListView()
{
}
