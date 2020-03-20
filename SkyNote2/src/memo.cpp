#include "memo.h"
#include "ui_memo.h"
#include "setting.h"
#include "updownform.h"

Memo::Memo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Memo)
{
    setWindowFlags(Qt::FramelessWindowHint);

    ui->setupUi(this);

    log = new Log();
    userText = new UserText();
    userSetting = new UserSetting();

    if(userText->isExist())
    {
        ui->mainTextEdit->setPlainText(userText->getText());
    }

    move(userSetting->getWindowPosX(), userSetting->getWindowPosY());
    Theme_Load(userSetting->getToolbarColor());
    Font_Load(userSetting->getFontSize());
    Min_Check(userSetting->getToolbarExtend());
}

Memo::~Memo()
{
    userSetting->save();
    delete ui;
}

void Memo::myResetText()
{
    ui->mainTextEdit->setPlainText("");
}

void Memo::Min_Check(int a)
{
    QPropertyAnimation *text_animation = new QPropertyAnimation(ui->mainTextEdit, "geometry");
    QPropertyAnimation *button_animation = new QPropertyAnimation(ui->extendButton, "geometry");

    switch (a) {
    case 2:
        custom_x = 50;

        text_animation->setDuration(200);
        text_animation->setStartValue(
                    QRect(
                        ui->mainTextEdit->geometry().x(),
                        ui->mainTextEdit->geometry().y(),
                        ui->mainTextEdit->geometry().width(),
                        ui->mainTextEdit->geometry().height()
                        )
                    );
        text_animation->setEndValue(
                    QRect(
                        ui->mainTextEdit->geometry().x()+80,
                        ui->mainTextEdit->geometry().y(),
                        ui->mainTextEdit->geometry().width()-80,
                        ui->mainTextEdit->geometry().height()
                        )
                    );
        text_animation->setEasingCurve(QEasingCurve::BezierSpline);

        button_animation->setDuration(200);
        button_animation->setStartValue(
                    QRect(
                        ui->extendButton->geometry().x(),
                        ui->extendButton->geometry().y(),
                        ui->extendButton->geometry().width(),
                        ui->extendButton->geometry().height()
                        )
                    );
        button_animation->setEndValue(
                    QRect(
                        ui->extendButton->geometry().x()+80,
                        ui->extendButton->geometry().y(),
                        ui->extendButton->geometry().width(),
                        ui->extendButton->geometry().height()
                        )
                    );
        button_animation->setEasingCurve(QEasingCurve::BezierSpline);

        text_animation->start();
        button_animation->start();

        isExtend = true;
        ui->settingButton->setText(" Setting");
        ui->uploadButton->setText(" Upload");
        ui->downloadButton->setText(" Download");
        ui->exitButton->setText(" Exit");
        ui->logButton->setText(" Log");

        ui->extendButton->setText("<");
        break;
    case 1:
        custom_x = 10;

        text_animation->setDuration(200);
        text_animation->setStartValue(
                    QRect(
                        ui->mainTextEdit->geometry().x(),
                        ui->mainTextEdit->geometry().y(),
                        ui->mainTextEdit->geometry().width(),
                        ui->mainTextEdit->geometry().height()
                        )
                    );
        text_animation->setEndValue(
                    QRect(
                        ui->mainTextEdit->geometry().x()-80,
                        ui->mainTextEdit->geometry().y(),
                        ui->mainTextEdit->geometry().width()+80,
                        ui->mainTextEdit->geometry().height()
                        )
                    );
        text_animation->setEasingCurve(QEasingCurve::BezierSpline);

        button_animation->setDuration(200);
        button_animation->setStartValue(
                    QRect(
                        ui->extendButton->geometry().x(),
                        ui->extendButton->geometry().y(),
                        ui->extendButton->geometry().width(),
                        ui->extendButton->geometry().height()
                        )
                    );
        button_animation->setEndValue(
                    QRect(
                        ui->extendButton->geometry().x()-80,
                        ui->extendButton->geometry().y(),
                        ui->extendButton->geometry().width(),
                        ui->extendButton->geometry().height()
                        )
                    );
        button_animation->setEasingCurve(QEasingCurve::BezierSpline);

        text_animation->start();
        button_animation->start();

        isExtend = false;
        ui->settingButton->setText(" S...");
        ui->uploadButton->setText(" U...");
        ui->downloadButton->setText(" D...");
        ui->exitButton->setText(" E...");
        ui->logButton->setText(" L...");

        ui->extendButton->setText(">");
        break;
    case 0:
        break;
    }
}

void Memo::Theme_Load(int num)
{
    QString color1, color2, color3;
    switch (num) {
    case 1:
        color1 = "#5AAEFF";
        color2 = "#489CFF";
        //color3 = "#C6FFFF";
        break;
    case 2:
        color1 = "#FFBB00";
        color2 = "#EDA900";
        //color3 = "#FFFFC6";
        break;
    case 3:
        color1 = "#FFB4FF";
        color2 = "#FFA2FF";
        //color3 = "#FFF1FF";
        break;
    case 4:
        color1 = "#87CE00";
        color2 = "#75BC00";
        //color3 = "#D1FFCA";
        break;
    case 5:
        color1 = "#9536FF";
        color2 = "#8324FF";
        //color3 = "#FFFFF1";
        break;
    }
    QString qss = "QPushButton {background-color: "+color1+";color: #FFFFFF;text-align: left;border-radius: 2px;}QMainWindow {background-color: "+color2+";}";
    this->setStyleSheet(qss);
    //ui->mainTextEdit->setStyleSheet("BackGround : "+color3);
}

void Memo::Font_Load(int size)
{
    QFont font;
    font.setPixelSize(size);
    ui->mainTextEdit->setFont(font);
}

void Memo::on_exitButton_clicked()
{
    close();
}

void Memo::on_downloadButton_clicked()
{
    ui->downloadButton->setStyleSheet("Color : #FFE400;");
    UpDownForm down(*this , "download");
    down.exec();

    ui->downloadButton->setStyleSheet("Color : White;");
    ui->mainTextEdit->setPlainText(userText->getText());

    isViewLog = false;
    ui->mainTextEdit->setEnabled(true);
    ui->logButton->setStyleSheet("Color : White;");
}

void Memo::on_uploadButton_clicked()
{
    ui->uploadButton->setStyleSheet("Color : #FFE400;");
    UpDownForm up(*this, "upload");
    up.exec();
    ui->uploadButton->setStyleSheet("Color : White;");
}

void Memo::on_settingButton_clicked()
{
    ui->settingButton->setStyleSheet("Color : #FFE400;");
    Setting s(*this, this);
    s.exec();
    ui->settingButton->setStyleSheet("Color : White;");
}

void Memo::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
       m_nMouseClick_X_Coordinate = event->x();
       m_nMouseClick_Y_Coordinate = event->y();
       isMouseDown = true;
    }
}

void Memo::mouseReleaseEvent(QMouseEvent *event) {
   isMouseDown = false;
   userSetting->setWindowPosX(event->globalX() - m_nMouseClick_X_Coordinate);
   userSetting->setWindowPosY(event->globalY() - m_nMouseClick_Y_Coordinate);
   userSetting->save();
}

void Memo::mouseMoveEvent(QMouseEvent *event) {
    if (isMouseDown == true) {
       move(
            event->globalX()-m_nMouseClick_X_Coordinate,
            event->globalY()-m_nMouseClick_Y_Coordinate
       );
    }
}

void Memo::on_mainTextEdit_textChanged()
{
    if(!isViewLog)
    {
        userText->setText(ui->mainTextEdit->toPlainText());
        userText->save();
    }
}

void Memo::on_extendButton_clicked()
{
    if(isExtend)
    {
        Min_Check(1);
        userSetting->setToolbarExtend(1);
    }
    else
    {
        Min_Check(2);
        userSetting->setToolbarExtend(0);
    }
}

void Memo::on_logButton_clicked()
{
    if(!isViewLog)
    {
        isViewLog = !isViewLog;
        ui->mainTextEdit->setEnabled(false);
        ui->logButton->setStyleSheet("Color : #FFE400;");

        ui->mainTextEdit->setPlainText(log->getText());
        ui->mainTextEdit->setPlaceholderText("Content does not exist.");
    }
    else
    {
        isViewLog = !isViewLog;
        ui->mainTextEdit->setEnabled(true);
        ui->logButton->setStyleSheet("Color : White;");

        ui->mainTextEdit->setPlainText(userText->getText());
        ui->mainTextEdit->setPlaceholderText("Start the memo.");
    }
}

Log *Memo::getLog()
{
    return log;
}

UserText *Memo::getUserText()
{
    return userText;
}

UserSetting *Memo::getUserSetting()
{
    return userSetting;
}
