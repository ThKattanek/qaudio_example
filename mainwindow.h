#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./audiogenerator.h"

#include <QMainWindow>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define SOUND_BUFFER_SIZE 8192

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    unsigned int bufferSize;
    QAudioDeviceInfo m_device;
    QAudioFormat     m_format;
    QByteArray       m_buffer;
    QAudioOutput    *m_audioOutput;

    AudioGenerator *m_audiogen;
};
#endif // MAINWINDOW_H
