#include "updownform.h"
#include "ui_updownform.h"

#include <QMessageBox>

UpDownForm::UpDownForm(Memo &ref, QString mode, QWidget *parent) : QDialog(parent), ui(new Ui::UpDownForm), memoRef(ref)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    Theme_Load(memoRef.getUserSetting()->getToolbarColor());

    if(mode == "upload")
    {
        isUpload = true;
    }
    else
    {
        isUpload = false;
    }

    ftpServer.setUserName(FTP_SERVER_USER);
    ftpServer.setPassword(FTP_SERVER_PASSWD);
    ftpServer.setPort(FTP_SERVER_PORT);

    QFile *file = new QFile("cache.sky");
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    ui->userNameLine->setText(in.readLine());
    file->close();

    networkAccessManager = new QNetworkAccessManager(this);
    if(isUpload)
    {
        move(
            memoRef.getUserSetting()->getWindowPosX() + 10,
            memoRef.getUserSetting()->getWindowPosY() + 50
        );

        ui->titleLabel->setText("Name the file and press the button.");
        ui->actionButton->setText("Upload");

        connect(networkAccessManager, &QNetworkAccessManager::finished, this, &UpDownForm::uploadFinished);
    }
    else
    {
        move(
            memoRef.getUserSetting()->getWindowPosX() + 10,
            memoRef.getUserSetting()->getWindowPosY() + 80
        );

        ui->titleLabel->setText("Enter a name and press the button.");
        ui->actionButton->setText("Download");

        connect(networkAccessManager, &QNetworkAccessManager::finished, this, &UpDownForm::downloadFinished);
    }
}

void UpDownForm::Theme_Load(int num)
{
    QString qss;
    QString color1;
    switch (num) {
    case 1:
        color1 = "#5AAEFF";
        break;
    case 2:
        color1 = "#FFBB00";
        break;
    case 3:
        color1 = "#FFB4FF";
        break;
    case 4:
        color1 = "#87CE00";
        break;
    case 5:
        color1 = "#9536FF";
        break;
    }
    qss = "QDialog {background-color: "+color1+";border: 1px solid black;}";
    this->setStyleSheet(qss);
}

UpDownForm::~UpDownForm()
{
    delete ui;
}

void UpDownForm::uploadFinished(QNetworkReply *reply)
{
    if (!reply->error())
    {
        file->close();
        file->deleteLater();
        reply->deleteLater();

        ui->actionButton->setText("Error!");
        ui->actionButton->setEnabled(true);

        complete = 2;
    }

    complete = 1;
    ui->titleLabel->setText("Press the button to close the window.");
    ui->actionButton->setText("Success!");
    ui->actionButton->setEnabled(true);
}

void UpDownForm::downloadFinished(QNetworkReply *reply)
{
    QFile *file = new QFile(memoRef.getUserText()->getFileName());
    if(file->open(QIODevice::Append))
    {
        memoRef.getUserText()->setText(reply->readAll());
        file->close();
    }
    delete file;

    complete = 1;
    ui->titleLabel->setText("Press the button to close the window.");
    ui->actionButton->setText("Success!");
    ui->actionButton->setEnabled(true);
}

void UpDownForm::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    ui->progressBar->setValue(100 * bytesSent/bytesTotal);
}

void UpDownForm::downloadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    ui->progressBar->setValue(100 * bytesSent/bytesTotal);
}

void UpDownForm::on_closeButton_clicked()
{
    close();
}

void UpDownForm::on_actionButton_clicked()
{
    if(isUpload) {
        if(ui->userNameLine->text()=="Admin" ||
           ui->userNameLine->text()=="admin" ||
           ui->userNameLine->text()=="Hello" ||
           ui->userNameLine->text()=="hello")
        {
            QMessageBox::information(this, "Error!", "Use Another UserName!","OK");
            return;
        }
    }

    if(ui->userNameLine->text().length()==0)
    {
        QMessageBox::information(this, "Error!", "Cannot Empty UserName!","OK");
        return;
    }
    else
    {
        QFile *file = new QFile("cache.sky");
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << ui->userNameLine->text();
        file->close();
        delete file;
    }

    if(ui->fileNameLine->text().length()==0)
    {
        QMessageBox::information(this, "Error!", "Cannot Empty FileName!", "OK");
        return;
    }

    if(complete == 0)
    {
        if(isUpload)
        {
            file = new QFile(memoRef.getUserText()->getFileName());

            ftpServer.setUrl(FTP_SERVER_URL + '/' + ui->userNameLine->text() + FTP_FILE_IDENTY + ui->fileNameLine->text() + ".txt");

            ui->titleLabel->setText("Uploading...");
            ui->actionButton->setText("Wait...");
            ui->actionButton->setEnabled(false);

            QDateTime *date = new QDateTime;
            QDateTime realTime=date->currentDateTime();
            QString DateView = "["+realTime.toString()+"]";
            memoRef.getLog()->append(DateView + "File : \"" +ui->fileNameLine->text()+ "\" were uploaded from the User : \""+ui->userNameLine->text()+"\"");

            if (file->open(QIODevice::ReadOnly))
            {
                QNetworkReply *reply = networkAccessManager->put(QNetworkRequest(ftpServer), file);
                connect(reply, &QNetworkReply::uploadProgress, this, &UpDownForm::uploadProgress);
            }
        }
        else
        {
            ftpServer.setUrl(FTP_SERVER_URL + '/' + ui->userNameLine->text() + FTP_FILE_IDENTY + ui->fileNameLine->text() + ".txt");

            ui->titleLabel->setText("Downloading...");
            ui->actionButton->setText("Wait...");
            ui->actionButton->setEnabled(false);

            QDateTime *date = new QDateTime;
            QDateTime realTime=date->currentDateTime();
            QString DateView = "["+realTime.toString()+"]";
            memoRef.getLog()->append(DateView + "User : \"" +ui->userNameLine->text()+ "\" downloaded the file : \""+ui->fileNameLine->text()+"\"");

            QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(ftpServer));
            connect(reply, &QNetworkReply::downloadProgress, this, &UpDownForm::downloadProgress);
        }
    }
    else
    {
        close();
    }
}

void UpDownForm::on_nameViewCheckBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(ui->userNameLine->echoMode()==QLineEdit::Password)
    {
        ui->userNameLine->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->userNameLine->setEchoMode(QLineEdit::Password);
    }
}
