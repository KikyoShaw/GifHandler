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
	// 无效图片不处理
	if (src.isNull()) {
		return src;
	}

	//获取图片尺寸
	int imageWidth = size.width();
	int imageHeight = size.height();

	// 缩放图片
	QPixmap pixmap = scaledPixmap(src, imageWidth, imageHeight);

	QPixmap destImage(imageWidth, imageHeight);
	destImage.fill(Qt::transparent);
	QPainter painter(&destImage);
	// 抗锯齿 + 平滑边缘处理
	painter.setRenderHints(QPainter::Antialiasing, true);
	painter.setRenderHints(QPainter::SmoothPixmapTransform, true);

	// 裁剪为圆角
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
	//}); //updated()播放到了一个新的帧
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

	painter->setRenderHint(QPainter::Antialiasing);  // 反锯齿;
	painter->setRenderHints(QPainter::SmoothPixmapTransform, true); //平滑边缘处理	

	painter->restore();

	//gif头像
	/*if (QMovie::Running == movie.state()) {*/
		QPixmap logo = QPixmap::fromImage(m_newImage);
		if (!logo.isNull()) {
			logo = generatePixmap(logo, QSize(50, 50), 50);
			painter->drawPixmap(x + 10, y + 10, logo);
		}
	/*}*/

	//昵称
	{
		if (info.nickName.isEmpty())
			info.nickName = info.userId;
		QFont font(QStringLiteral("微软雅黑"));
		font.setPixelSize(14);
		QFontMetrics fm(font);
		QString strElidedText = fm.elidedText(info.nickName, Qt::ElideRight, 144, Qt::TextShowMnemonic);
		painter->setFont(font);
		painter->setPen(QPen(QColor(255, 255, 255)));
		painter->drawText(QRect(x + 68, y + 14, width, height), strElidedText);
	}

	//个性签名
	{
		QFont font(QStringLiteral("微软雅黑"));
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
