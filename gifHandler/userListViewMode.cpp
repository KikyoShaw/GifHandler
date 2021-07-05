#include "userListViewModel.h"

vUserListViewModel::vUserListViewModel()
{
}

void vUserListViewModel::clear()
{
	m_listInfo.clear();
}

void vUserListViewModel::addInfoToModel(UserInfo pInfo)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_listInfo.push_back(pInfo);
	endInsertRows();
}

int vUserListViewModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return m_listInfo.count();
}

QVariant vUserListViewModel::data(const QModelIndex & index, int role) const
{
	if (index.row() < 0 || index.row() >= m_listInfo.count()) {
		return QVariant();
	}
	if (Qt::DisplayRole == role) {
		UserInfo pInfo = m_listInfo.at(index.row());
		return pInfo;
	}
	return QVariant();
}
