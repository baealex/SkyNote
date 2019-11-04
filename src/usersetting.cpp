#include "usersetting.h"

UserSetting::UserSetting()
{
    file = new QFile;
    file->setFileName(fileName);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        toolbarColor = 2;
        toolbarExtend = 0;
        fontSize = 12;
        windowPosX = 300;
        windowPosY = 200;
        autoStart = 0;
    }
    else
    {
        this->load();
    }
    file->close();
}

void UserSetting::save()
{
    file->open(QIODevice::WriteOnly);
    QTextStream out(file);
    out << toolbarColor << "\n"
        << toolbarExtend << "\n"
        << fontSize << "\n"
        << windowPosX << "\n"
        << windowPosY << "\n"
        << autoStart;
    file->close();
}

void UserSetting::load()
{
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    toolbarColor = in.readLine().toInt();
    toolbarExtend = in.readLine().toInt();
    fontSize = in.readLine().toInt();
    windowPosX = in.readLine().toInt();
    windowPosY = in.readLine().toInt();
    autoStart = in.readLine().toInt();
    file->close();
}

void UserSetting::setToolbarColor(int color)
{
    this->toolbarColor = color;
}

void UserSetting::setToolbarExtend(int extend)
{
    this->toolbarExtend = extend;
}

void UserSetting::setFontSize(int size)
{
    this->fontSize = size;
}

void UserSetting::setWindowPosX(int x)
{
    this->windowPosX = x;
}

void UserSetting::setWindowPosY(int y)
{
    this->windowPosY = y;
}

void UserSetting::setAutoStart(int autoStart)
{
    this->autoStart = autoStart;
}

int UserSetting::getToolbarColor()
{
    return toolbarColor;
}

int UserSetting::getToolbarExtend()
{
    return toolbarExtend;
}

int UserSetting::getFontSize()
{
    return fontSize;
}

int UserSetting::getWindowPosX()
{
    return windowPosX;
}

int UserSetting::getWindowPosY()
{
    return windowPosY;
}

int UserSetting::getAutoStart()
{
    return autoStart;
}

QString UserSetting::getFileName()
{
    return fileName;
}
