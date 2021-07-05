#pragma once

#include <QAbstractListModel>

struct UserInfo
{
	operator QVariant() const
	{
		return QVariant::fromValue(*this);
	}

	QString userId; //用户id
	QString nickName; //用户昵称
	QString userSlogn; //用户签名
	QString fileName; //头像路径
};
Q_DECLARE_METATYPE(UserInfo);

class vUserListViewModel : public QAbstractListModel
{
	Q_OBJECT
public:
	vUserListViewModel();
	void clear();
	void addInfoToModel(UserInfo pInfo);
	//  model/view override函数
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
	QVector<UserInfo> m_listInfo;
};
