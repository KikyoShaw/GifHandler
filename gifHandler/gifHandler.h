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
	void sltOpen(); //打开文件
	void sltGoToFrame(int frame); //跳转到指定帧
	void sltFitToWindow(); //是否填充满尺寸
	void sltUpdateButtons(); //更新按钮状态
	void sltUpdateFrameSlider(int frameNumber); //更新滑动条值
	void sltPausedOrPlay(); //暂停与播放
	void sltCutImage(); //截图当前帧gif
	void sltClearGif(); //清空gif
	void sltSetGifRadius(); //设置gif圆角

private:
    Ui::gifHandlerClass ui;
	QMovie movie;
	//记录gif路径
	QString m_filePath;
	//记录Gif帧数
	int m_GifFrameCount;
	// gif动态图的圆角样式
	QSharedPointer<GifProxyStyle> m_GifProxyStyle = nullptr;
};
