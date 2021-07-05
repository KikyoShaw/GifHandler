#include "userListViewDelegate.h"
#include "userListViewModel.h"
#include <QPainter>

static QPixmap scaledPixmap(const QPixmap & src, int width, int height)
{
	return src.scaled(width, (height == 0 ? width : height),
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

static QPixmap generatePixmap(const QPixmap & src, const QSize & size, const int & radius)
{
	// ��ЧͼƬ������
	if (src.isNull()) {
		return src;
	}

	//��ȡͼƬ�ߴ�
	int imageWidth = size.width();
	int imageHeight = size.height();

	// ����ͼƬ
	QPixmap pixmap = scaledPixmap(src, imageWidth, imageHeight);

	QPixmap destImage(imageWidth, imageHeight);
	destImage.fill(Qt::transparent);
	QPainter painter(&destImage);
	// ����� + ƽ����Ե����
	painter.setRenderHints(QPainter::Antialiasing, true);
	painter.setRenderHints(QPainter::SmoothPixmapTransform, true);

	// �ü�ΪԲ��
	QPainterPath path;
	QRect rect(0, 0, imageWidth, imageHeight);
	path.addRoundedRect(rect, radius, radius);
	painter.setClipPath(path);
	painter.drawPixmap(0, 0, imageWidth, imageHeight, pixmap);
	return destImage;
}

vUserListViewDelegate::vUserListViewDelegate()
{
	//movie.setFileName("test.gif");
	//connect(&movie, &QMovie::updated, this, [=] {
	//	m_newImage = movie.currentImage();
	//}); //updated()���ŵ���һ���µ�֡
	//movie.start();
}

void vUserListViewDelegate::setImage(QImage image)
{
	m_newImage = image;
}

void vUserListViewDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QRect rect = option.rect;

	const QAbstractItemModel *pModel = index.model();
	auto info = pModel->data(index, Qt::DisplayRole).value<UserInfo>();

	if (info.userId.isEmpty()) {
		return;
	}

	int x = rect.left();
	int y = rect.top();
	int width = rect.width();
	int height = rect.height();
	painter->save();

	painter->setRenderHint(QPainter::Antialiasing);  // �����;
	painter->setRenderHints(QPainter::SmoothPixmapTransform, true); //ƽ����Ե����	

	painter->restore();

	//gifͷ��
	/*if (QMovie::Running == movie.state()) {*/
		QPixmap logo = QPixmap::fromImage(m_newImage);
		if (!logo.isNull()) {
			logo = generatePixmap(logo, QSize(50, 50), 50);
			painter->drawPixmap(x + 10, y + 10, logo);
		}
	/*}*/

	//�ǳ�
	{
		if (info.nickName.isEmpty())
			info.nickName = info.userId;
		QFont font(QStringLiteral("΢���ź�"));
		font.setPixelSize(14);
		QFontMetrics fm(font);
		QString strElidedText = fm.elidedText(info.nickName, Qt::ElideRight, 144, Qt::TextShowMnemonic);
		painter->setFont(font);
		painter->setPen(QPen(QColor(255, 255, 255)));
		painter->drawText(QRect(x + 68, y + 14, width, height), strElidedText);
	}

	//����ǩ��
	{
		QFont font(QStringLiteral("΢���ź�"));
		font.setPixelSize(14);
		QFontMetrics fm(font);
		QString strElidedText = fm.elidedText(info.userSlogn, Qt::ElideRight, fm.width(info.userSlogn), Qt::TextShowMnemonic);
		painter->setFont(font);
		painter->setPen(QPen(QColor(255, 255, 255)));
		painter->drawText(QRect(x + 68, y + 38, width, height), strElidedText);
	}

}

QSize vUserListViewDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	return QSize(380, 70);
}

bool vUserListViewDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index)
{
	return false;
}
