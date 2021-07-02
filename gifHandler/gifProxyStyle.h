#pragma once

#include <QProxyStyle>

// gif动态图的圆角样式
class GifProxyStyle : public QProxyStyle
{
public:
	explicit GifProxyStyle(QStyle* style = Q_NULLPTR);
	~GifProxyStyle();

	//设置大小和圆角范围
	void setGifSize(const QSize& size);
	//设置圆角
	void setGifRadius(int radius);

protected:
	//绘制事件
	virtual void drawItemPixmap(QPainter *painter, const QRect &rect, int alignment, const QPixmap &pixmap) const;

private:
	int m_radius;
	QSize m_gifSize = QSize(400, 400);
};

