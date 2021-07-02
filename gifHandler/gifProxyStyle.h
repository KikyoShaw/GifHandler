#pragma once

#include <QProxyStyle>

// gif��̬ͼ��Բ����ʽ
class GifProxyStyle : public QProxyStyle
{
public:
	explicit GifProxyStyle(QStyle* style = Q_NULLPTR);
	~GifProxyStyle();

	//���ô�С��Բ�Ƿ�Χ
	void setGifSize(const QSize& size);
	//����Բ��
	void setGifRadius(int radius);

protected:
	//�����¼�
	virtual void drawItemPixmap(QPainter *painter, const QRect &rect, int alignment, const QPixmap &pixmap) const;

private:
	int m_radius;
	QSize m_gifSize = QSize(400, 400);
};

