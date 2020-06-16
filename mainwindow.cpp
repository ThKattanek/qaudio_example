#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bufferSize = SOUND_BUFFER_SIZE * 2;

    m_format.setSampleRate(44100);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::Float);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }
    m_device = QAudioDeviceInfo::defaultOutputDevice();
    m_buffer = QByteArray(bufferSize*2, 0);

    m_audioOutput = new QAudioOutput(m_device, m_format, this);
    m_audioOutput->setBufferSize(bufferSize);
    m_audiogen = new AudioGenerator(m_format, this);
    m_audiogen->start();
    m_audioOutput->start(m_audiogen);

    m_audioOutput->setVolume(1);

}

MainWindow::~MainWindow()
{
    m_audioOutput->stop();
    delete m_audioOutput;

    delete ui;
}
