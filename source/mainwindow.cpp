#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include "Configuration.h"
#include "IntelHex.hpp"
#include <fstream>
#include <curl/curl.h>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
// #include <QtSerialPort/QSerialPortInfo>


void MainWindow::_steps(){

//    !="wiring");
    ui->BootLoaderCheck->setEnabled(strcmp(ui->SelectProgrammer->currentText().toStdString().c_str(),"wiring"));
    ui->InputSerial->setEnabled(EXTRA);
    if(EXTRA && (-1!=ui->SelectPort->currentIndex())){
        ui->Step1Box->setEnabled(EXTRA);
        ui->Step2Box->setEnabled(EXTRA);
        ui->Step3Box->setEnabled(EXTRA);
        ui->Step4Box->setEnabled(EXTRA);
        ui->ExtraBox->setEnabled(EXTRA);
    }else
    switch (Step) {
    case 1:

        ui->Step4Box->setEnabled(false);
        ui->Step1Box->setEnabled(true);
        break;
    case 2:
        ui->BootLoaderCheck->setEnabled(false);
        ui->Step1Box->setEnabled(false);
        ui->Step2Box->setEnabled(true);
        break;
    case 3:

        ui->Step2Box->setEnabled(false);
        ui->Step3Box->setEnabled(true);
        break;
    case 4:
        ui->Step3Box->setEnabled(false);
        ui->Step4Box->setEnabled(true);
        break;
    default:

        ui->Step1Box->setEnabled(false);
        ui->Step2Box->setEnabled(false);
        ui->Step3Box->setEnabled(false);
        ui->Step4Box->setEnabled(false);
        ui->ExtraBox->setEnabled(false);
        break;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->SetSerial->setText("Test set testx");
    try{
        _steps();
    int err=system(avrdude.c_str());
        if(err){
            QMessageBox msgBox;
            msgBox.setText(NoInstall);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            QCoreApplication::quit();
        }
        else{
            for( auto item=0;item<sizeof(ProgramerList)/sizeof(ProgramerList[0]);++item)
            ui->SelectProgrammer->addItem(ProgramerList[item]);
            ui->SelectProgrammer->setCurrentIndex(-1);
            //update port list
        }
    }
    catch(...){}
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_SetSerial_clicked()
{
//    ui->textEdit->setText("<b>TEST</b>");
}


void MainWindow::on_Quit_clicked()
{
//    MainWindow::close();
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
//    ui->textEdit->setText(ui->lineEdit->text());
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

}


void MainWindow::on_SelectProgrammer_currentIndexChanged(int index)
{
    ui->PortBox->setEnabled(-1!=ui->SelectProgrammer->currentIndex());

//    auto infos = QSerialPortInfo::availablePorts();
//    for (const QSerialPortInfo &info : infos){
//        ui->SelectPort->addItem(info.portName());
//    }


    ui->SelectPort->setCurrentIndex(-1);
    Step=0;
    _steps();
}

/**
 * @brief Палимо фюзи
 * Перший крок
 */
void MainWindow::on_ButtonFuse_clicked()
{

//    avrdude -c usbtiny -p m2560 -U efuse:w:0xFD:m  -U hfuse:w:0xD8:m  -U lfuse:w:0xFF:m
//    avrdude + " -c "+ui->SelectProgrammer->currentText() +CPUchip+ALLfuses
    int err=system(std::string(avrdude + " -c "+ui->SelectProgrammer->currentText().toStdString() +CPUchip+ALLfuses).c_str());
    if(err){
        QMessageBox msgBox;
        switch (err) {
        case 256:
            msgBox.setText("Code: "+QString::number(err)+" Check the cable connections");
            break;
        default:
            msgBox.setText("An unfamiliar error"+QString::number(err));
            break;
        }
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
    else
    {
        Step=2;
        _steps();
    }
}

/**
 * другий крок
 * Пишемо прошивку
 */
void MainWindow::on_ButtonDiscovery_clicked()
{
    std::string Prog{avrdude + " -c "+ui->SelectProgrammer->currentText().toStdString()+CPUchip +" -U flash:w:"+DiscoveryFile+((ui->BootLoaderCheck->isChecked())?(BootFile):(Ext))+":i"};
//    -U flash:w:NanitInfo.ino.with_bootloader.hex:i
    int err=system(Prog.c_str());
    if(err){
        QMessageBox msgBox;
        switch (err) {
        case 256:
            msgBox.setText("Code: "+QString::number(err)+" Check the cable connections");
            break;
        default:
            msgBox.setText("An unfamiliar error"+QString::number(err));
            break;
        }
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
        else
    {        Step=3;
        _steps();
    }
//    if(ui->BootLoaderCheck->isChecked())
//    system(QString(avrdude+help).toStdString().c_str());
//    else system(QString(avrdude+help).toStdString().c_str());
}

/**
 * другий крок
 * Пишемо прошивку
 */

void MainWindow::on_ButtonNanitInfo_clicked()
{
    std::string Prog{NanitInfoFile+((ui->BootLoaderCheck->isChecked())?(BootFile):(Ext))};
    Step=3;
    _steps();
//    if(ui->BootLoaderCheck->isChecked())
//    system(QString(avrdude+help).toStdString().c_str());
//    else system(QString(avrdude+help).toStdString().c_str());
}

/**
 * Третій крок завантажуємо конфігурацію
 */
void MainWindow::on_ButtonConfig_clicked()
{
    Step=4;
    _steps();
//    system(QString(avrdude+help).toStdString().c_str());
}


static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}
/**
 * четвертий крок пишемо серійний
 */
void MainWindow::on_ButtonSerial_clicked()
{
    Step=1;
    _steps();
    CURL *curl;
    CURLcode res;
    // #ifndef NANIT_SERIAL_NUMBER_URL
    // #error NO URLS
    // #else
    std::string readBuffer;
    // #endif
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,
                         "https://docs.ieu.edu.ua/seriynyk.php?SN=1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        int64_t serial_number = std::stoll(readBuffer);

//        if (k_max_uint32_t < serial_number) {
//            //   std::cout << "To big";
//            return EX_IOERR;
//        }
//        if (k_max_corect_number < serial_number) {
//            //   std::cout << "big";
//            return EX_IOERR;
//        }
//        if (k_min_corect_number > serial_number) {
//            //   std::cout << "small";
//            return EX_IOERR;
//        }
        union {
        uint32_t sn;
        char bytes[sizeof(sn)];
    };
        sn = serial_number;
    try{
        std::ofstream Ihex_file;
        Ihex_file.open(NumberFile);
        Ihex_file << IHEX_RECORD(uint16_t(0xfff) - sizeof(sn) + 1, bytes,
                                 sizeof(sn), DATA_TYPE::RECORD_DAT)
                  << IHEX_RECORD();
        Ihex_file.close();
        }
        catch(...){}
    }













        system("pwd");
}

/**
 * Екстра очищення
 */
void MainWindow::on_ButtonWipe_clicked()
{
    try{
    std::ofstream Ihex_file;
    Ihex_file.open(WipeFile);
    Ihex_file<< IHEX_CLEAR(FLASH_BEGIN,FLASH_SIZE,REC_LEN);
    Ihex_file.close();
    }
        catch(...){}
//    system(QString(avrdude+help).toStdString().c_str());
}


void MainWindow::on_ButtonClear_clicked()
{
    try{
    std::ofstream Ihex_file;
    Ihex_file.open(ClearFile);
    Ihex_file<< IHEX_CLEAR(E2PROM_BEGIN,E2PROM_SIZE,REC_LEN);
    Ihex_file.close();
    }
    catch(...){}
//    system(QString(avrdude+help).toStdString().c_str());
}


void MainWindow::on_PortBox_clicked()
{

}


void MainWindow::on_SelectPort_currentIndexChanged(int index)
{
    Step=1;
    _steps();
}


void MainWindow::on_SelectPort_activated(int index)
{

}

