#ifndef LOG_H
#define LOG_H

#include "main.h"

class Log
{
private:
    QString text;

    QString fileName = "log.sky";
    QFile *file;
public:
    Log();
    bool isExist();
    void save();
    void load();
    void append(QString text);
    QString getText();
    QString getFileName();
};

#endif // LOG_H
