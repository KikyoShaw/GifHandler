#include "gifHandler.h"
#include <QFileDialog>
#include <QDebug>
#include <QClipboard>
#include <QMessageBox>
#include "gifProxyStyle.h"
#include <QPainter>

constexpr char* Property_state = "state";

//当做Image图片处理
static QSize getGifSize(const QString & fileName)
{
	QImageReader reader(fileName);
	reader.setDecideFormatFromContent(true);
	if (!reader.canRead()) {
		qInfo() << QStringLiteral("[%1][file cant read]:").arg(__FUNCTION__) << fileName;
		return QSize();
	}
	int width = reader.size().width();
	int height = reader.size().height();
	return QSize(width, height);
}

gifHandler::gifHandler(QWidget *parent)
	: QWidget(parent)
	, m_filePath(".gif")
	, m_GifFrameCount(0)
{
    ui.setupUi(this);

	//setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);

	//设置QMovie的缓存模式
	movie.setCacheMode(QMovie::CacheAll);

	ui.label_movies->setAlignment(Qt::AlignCenter);
	ui.label_movies->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui.label_movies->setBackgroundRole(QPalette::Shadow);
	ui.label_movies->setAutoFillBackground(true);

	QValidator *validator = new QRegExpValidator(QRegExp("[0-9]+$"));
	ui.lineEdit->setValidator(validator);

	//初始化数据
	clearUI();

	// gif动态图的圆角样式
	m_GifProxyStyle = QSharedPointer<GifProxyStyle>(new GifProxyStyle());
	ui.label_movies->setStyle(m_GifProxyStyle.data());

	connect(ui.pushButton_open, &QPushButton::clicked, this, &gifHandler::sltOpen);
	connect(ui.horizontalSlider, &QSlider::valueChanged, this, &gifHandler::sltGoToFrame);
	connect(ui.checkBox, &QCheckBox::clicked, this, &gifHandler::sltFitToWindow);
	connect(ui.spinBox, QOverload<int>::of(&QSpinBox::valueChanged), &movie, &QMovie::setSpeed);
	connect(&movie, &QMovie::frameChanged, this, &gifHandler::sltUpdateFrameSlider);
	//connect(&movie, &QMovie::updated, this, &gifHandler::sltUpdateFrameSlider); //updated()播放到了一个新的帧
	connect(ui.pushButton_play, &QPushButton::clicked, this, &gifHandler::sltPausedOrPlay);
	connect(ui.pushButton_cut, &QPushButton::clicked, this, &gifHandler::sltCutImage);
	connect(ui.pushButton_dele, &QPushButton::clicked, this, &gifHandler::sltClearGif);
	connect(ui.pushButton_radius, &QPushButton::clicked, this, &gifHandler::sltSetGifRadius);
	connect(&movie, SIGNAL(stateChanged(QMovie::MovieState)),this, SLOT(sltUpdateButtons()));
}

gifHandler::~gifHandler()
{
}

void gifHandler::clearUI()
{
	ui.pushButton_play->setText(QStringLiteral("播放"));
	ui.pushButton_play->setProperty(Property_state, false);
	m_GifFrameCount = 0;
	ui.label_gifNum->setText(QString::number(m_GifFrameCount));
	ui.label_gifNum_now->setText(QString::number(m_GifFrameCount));
	ui.horizontalSlider->setValue(m_GifFrameCount);
	ui.lineEdit->setText(0);
}

void gifHandler::sltOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Movie"), m_filePath);
	if (fileName.isEmpty()) {
		qInfo() << "open movie error " << fileName;
		return;
	}

	m_filePath = QFileInfo(fileName).path();
	movie.stop();
	ui.label_movies->setMovie(&movie);
	movie.setFileName(fileName);
	m_GifFrameCount = movie.frameCount();
	ui.label_gifNum->setText(QString::number(m_GifFrameCount));
	QSize _size = getGifSize(fileName);
	ui.label_height->setText(QString::number(_size.height()));
	ui.label_width->setText(QString::number(_size.width()));
	//if (m_GifProxyStyle) {
	//	//设置gif尺寸
	//	m_GifProxyStyle->setGifSize(_size);
	//}
	movie.start();
}

void gifHandler::sltGoToFrame(int frame)
{
	if (QMovie::NotRunning == movie.state()) {
		ui.horizontalSlider->setValue(0);
		return;
	}

	//跳转到指定的帧
	movie.jumpToFrame(frame);
}

void gifHandler::sltFitToWindow()
{
	//填充满
	ui.label_movies->setScaledContents(ui.checkBox->isChecked());
}

void gifHandler::sltUpdateButtons()
{
	if (QMovie::Running == movie.state()) {
		//ui.pushButton_play->setEnabled(true);
		ui.pushButton_play->setText(QStringLiteral("暂停"));
		ui.pushButton_play->setProperty(Property_state, true);
	}
	else if (QMovie::Paused == movie.state()) {
		//ui.pushButton_play->setEnabled(true);
		ui.pushButton_play->setText(QStringLiteral("播放"));
		ui.pushButton_play->setProperty(Property_state, false);
	}
	//else if (QMovie::NotRunning == movie.state()) {
	//	ui.pushButton_play->setEnabled(false);
	//}
}

void gifHandler::sltUpdateFrameSlider(int frameNumber)
{
	bool hasFrames = (frameNumber >= 0);
	if (hasFrames){
		if (m_GifFrameCount > 0)
		{
			ui.horizontalSlider->setMaximum(m_GifFrameCount - 1);
		}
		else{
			if (frameNumber > ui.horizontalSlider->maximum())
				ui.horizontalSlider->setMaximum(frameNumber);
		}
		ui.horizontalSlider->setValue(frameNumber);
		//获取当前帧
		//int _nowFrame = movie.currentFrameNumber();
		ui.label_gifNum_now->setText(QString::number(frameNumber));
	}
	else{
		ui.horizontalSlider->setMaximum(0);
	}
	ui.horizontalSlider->setEnabled(hasFrames);
}

void gifHandler::sltPausedOrPlay()
{
	if (QMovie::NotRunning == movie.state()) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("当前没有gif"));
		return;
	}

	bool _state = ui.pushButton_play->property(Property_state).toBool();
	movie.setPaused(_state);
}

void gifHandler::sltCutImage()
{
	if (QMovie::NotRunning == movie.state()) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("当前没有gif"));
		return;
	}

	//截取当前帧图片
	//如果需要截取某一帧/指定帧,可以通过frameCount()获取总帧数，然后在指定范围内获取
	QImage _image = movie.currentImage();
	QClipboard *board = QApplication::clipboard();
	board->setImage(_image);
	QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("截取成功,已复制到剪贴板"));
}

void gifHandler::sltClearGif()
{
	if (QMovie::NotRunning == movie.state()) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("当前没有gif"));
		return;
	}

	movie.stop();
	movie.setFileName(QString());
	ui.label_movies->setMovie(NULL);
	update();
	clearUI();
}

void gifHandler::sltSetGifRadius()
{
	if (QMovie::NotRunning == movie.state()) {
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("当前没有gif"));
		return;
	}

	if (m_GifProxyStyle) {
		int _radius = ui.lineEdit->text().toInt();
		m_GifProxyStyle->setGifRadius(_radius);
		ui.label_movies->setStyleSheet(QString("background-color: rgba(0, 0, 0, 0.6);border-radius:%1px;").arg(ui.lineEdit->text()));
	}
}
