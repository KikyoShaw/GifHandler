#pragma once

#include <QAbstractListModel>

struct UserInfo
{
	operator QVariant() const
	{
		return QVariant::fromValue(*this);
	}

	QString userId; //�û�id
	QString nickName; //�û��ǳ�
	QString userSlogn; //�û�ǩ��
	QString fileName; //ͷ��·��
};
Q_DECLARE_METATYPE(UserInfo);

class vUserListViewModel : public QAbstractListModel
{
	Q_OBJECT
public:
	vUserListViewModel();
	void clear();
	void addInfoToModel(UserInfo pInfo);
	//  model/view override����
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
	QVector<UserInfo> m_listInfo;
};
