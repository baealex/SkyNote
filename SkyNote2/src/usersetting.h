#ifndef USERSETTING_H
#define USERSETTING_H

#include "main.h"

class UserSetting
{
    int toolbarColor;
    int toolbarExtend;
    int fontSize;
    int windowPosX;
    int windowPosY;
    int autoStart;

    QString fileName = "config.sky";
    QFile *file;
public:
    UserSetting();
    void save();
    void load();

    void setToolbarColor(int color);
    void setToolbarExtend(int extend);
    void setFontSize(int size);
    void setWindowPosX(int x);
    void setWindowPosY(int y);
    void setAutoStart(int autoStart);

    int getToolbarColor();
    int getToolbarExtend();
    int getFontSize();
    int getWindowPosX();
    int getWindowPosY();
    int getAutoStart();
    QString getFileName();
};

#endif // USERSETTING_H
