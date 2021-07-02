#pragma once

#include <QtWidgets/QWidget>
#include "ui_gifHandler.h"
#include <QMovie>

class GifProxyStyle;

class gifHandler : public QWidget
{
    Q_OBJECT

public:
    gifHandler(QWidget *parent = Q_NULLPTR);
	~gifHandler();

private:
	void clearUI();

private slots:
	void sltOpen(); //���ļ�
	void sltGoToFrame(int frame); //��ת��ָ��֡
	void sltFitToWindow(); //�Ƿ�������ߴ�
	void sltUpdateButtons(); //���°�ť״̬
	void sltUpdateFrameSlider(int frameNumber); //���»�����ֵ
	void sltPausedOrPlay(); //��ͣ�벥��
	void sltCutImage(); //��ͼ��ǰ֡gif
	void sltClearGif(); //���gif
	void sltSetGifRadius(); //����gifԲ��

private:
    Ui::gifHandlerClass ui;
	QMovie movie;
	//��¼gif·��
	QString m_filePath;
	//��¼Gif֡��
	int m_GifFrameCount;
	// gif��̬ͼ��Բ����ʽ
	QSharedPointer<GifProxyStyle> m_GifProxyStyle = nullptr;
};
