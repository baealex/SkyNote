#ifndef USERTEXT_H
#define USERTEXT_H

#include "main.h"

class UserText
{
    QString text;

    QString fileName = "memo.sky";
    QFile *file;
public:
    UserText();
    bool isExist();
    void save();
    void load();

    void setText(QString text);
    QString getText();
    QString getFileName();
};

#endif // USERTEXT_H
