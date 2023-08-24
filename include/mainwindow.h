#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_SetSerial_clicked();

    void on_Quit_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_SelectProgrammer_currentIndexChanged(int index);

    void on_ButtonFuse_clicked();

    void on_ButtonDiscovery_clicked();

    void on_ButtonNanitInfo_clicked();

    void on_ButtonConfig_clicked();

    void on_ButtonSerial_clicked();

    void on_ButtonWipe_clicked();

    void on_ButtonClear_clicked();

    void on_PortBox_clicked();

    void on_SelectPort_currentIndexChanged(int index);

    void on_SelectPort_activated(int index);

private:
    void _steps();
    Ui::MainWindow *ui;
    uint8_t Step=0;
    bool EXTRA=true;
};
#endif // MAINWINDOW_H
