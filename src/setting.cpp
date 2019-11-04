#include "setting.h"
#include "ui_setting.h"
#include "memo.h"
#include "ui_memo.h"

Setting::Setting(Memo &ref, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting),
    memoRef(ref)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    /* UI init */
    ui->fontSizeSpinBox->setValue(memoRef.getUserSetting()->getFontSize());
    if(memoRef.getUserSetting()->getAutoStart() == 1)
    {
        ui->autoStartCheckBox->setChecked(true);
    }
}

Setting::~Setting()
{
    memoRef.getUserSetting()->save();
    delete ui;
}

void Setting::on_theme_white_clicked()
{
    memoRef.Theme_Load(1);
    memoRef.getUserSetting()->setToolbarColor(1);
}

void Setting::on_theme_yellow_clicked()
{
    memoRef.Theme_Load(2);
    memoRef.getUserSetting()->setToolbarColor(2);
}

void Setting::on_theme_pink_clicked()
{
    memoRef.Theme_Load(3);
    memoRef.getUserSetting()->setToolbarColor(3);
}

void Setting::on_theme_blue_clicked()
{
    memoRef.Theme_Load(4);
    memoRef.getUserSetting()->setToolbarColor(4);
}

void Setting::on_theme_green_clicked()
{
    memoRef.Theme_Load(5);
    memoRef.getUserSetting()->setToolbarColor(5);
}

void Setting::on_homepageButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://baejino.com"));
}

void Setting::on_updateButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.dropbox.com/sh/t5f4y8v8lvmdsez/AAC9pKrbXGZOatorYsRxyBDGa?dl=0"));
}

void Setting::on_resetButton_clicked()
{
    QFile *file = new QFile;
    file->setFileName(memoRef.getLog()->getFileName());
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)) file->remove();
    file->setFileName(memoRef.getUserText()->getFileName());
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)) file->remove();
    file->setFileName(memoRef.getUserSetting()->getFileName());
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)) file->remove();
    file->setFileName("cache.sky");
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)) file->remove();
    file->close();
    delete file;

    memoRef.Theme_Load(2);
    memoRef.Font_Load(12);
    memoRef.myResetText();
    close();
}

void Setting::on_fontSizeSpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    memoRef.Font_Load(arg1);
    memoRef.getUserSetting()->setFontSize(arg1);
}

void Setting::on_autoStartCheckBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    QString startDir =
            QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)
            + QDir::separator() + "Startup"
            + QDir::separator() + fileInfo.completeBaseName() + ".lnk";

    if(memoRef.getUserSetting()->getAutoStart() == 0)
    {
        QFile::link(QCoreApplication::applicationFilePath(),startDir);
        memoRef.getUserSetting()->setAutoStart(1);
    }
    else
    {
        QFile file(startDir);
        file.remove();
        memoRef.getUserSetting()->setAutoStart(0);
    }
}
