#ifndef UPDOWNFORM_H
#define UPDOWNFORM_H

#include "memo.h"

namespace Ui {
class UpDownForm;
}

class UpDownForm : public QDialog
{
    Q_OBJECT

public:
    explicit UpDownForm(Memo &ref, QString mode, QWidget *parent = 0);
    void Theme_Load(int num);
    ~UpDownForm();

private slots:
    void uploadFinished(QNetworkReply *reply);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void downloadFinished(QNetworkReply *reply);
    void downloadProgress(qint64 bytesSent, qint64 bytesTotal);
    void on_closeButton_clicked();
    void on_actionButton_clicked();
    void on_nameViewCheckBox_stateChanged(int arg1);

private:
    const QString FTP_FILE_IDENTY = "___";
    const QString FTP_SERVER_URL = "ftp://SERVER_IP/SERVER_DIR";
    const QString FTP_SERVER_USER = "SERVER_USER_ID";
    const QString FTP_SERVER_PASSWD = "SERVER_USER_PASSWD";
    const int FTP_SERVER_PORT = 21;

    Ui::UpDownForm *ui;
    bool isUpload;
    QNetworkAccessManager *networkAccessManager;
    QFile *file;
    QUrl ftpServer;
    int complete = 0;
    Memo &memoRef;
};

#endif // UPDOWNFORM_H
