#include "audiogenerator.h"
#include <QDebug>

AudioGenerator::AudioGenerator(const QAudioFormat &_format, QObject *parent = 0) : QIODevice(parent)
{

}

AudioGenerator::~AudioGenerator()
{

}

void AudioGenerator::start()
{
    open(QIODevice::ReadOnly);
}

void AudioGenerator::stop()
{
    close();
}

qint64 AudioGenerator::readData(char *data, qint64 len)
{
    // QAudioOutput tends to ask large packets of data, which can lead to a
    // large delay between noteOn requests and the generation of audio. Thus,
    // in order to provide more responsive interface, the packet size is
    // limited to 2048 bytes ~ 1024 samples.

    // if (len > 2048) len = 2048;

    //generateData(len);
    memcpy(data, m_buffer.constData(), len);
    //curtime += (qreal)len/(44100*2);

    qDebug() << "Audio Call: " << len;

    return len;
}

// Not used.
qint64 AudioGenerator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);
    return 0;
}

// Doesn't seem to be called by QAudioOutput.
qint64 AudioGenerator::bytesAvailable() const
{
    qDebug() << "bytesAvailable()";
    return m_buffer.size() + QIODevice::bytesAvailable();
}
