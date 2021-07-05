#pragma once

#include <QStyledItemDelegate>
#include <QPainter>
#include <QMovie>

class vUserListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	vUserListViewDelegate();

	void setImage(QImage image);

protected:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
	QMovie movie; //”√¿¥Ω‚Œˆgif
	QImage m_newImage;
};
