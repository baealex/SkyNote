#include "log.h"

Log::Log()
{
    file = new QFile;
    file->setFileName("sky.log");

    if(isExist())
    {
        load();
    }
}

bool Log::isExist()
{
    bool result = false;
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result = true;
    }
    file->close();
    return result;
}

QString Log::getText()
{
    return text;
}

void Log::save()
{
    file->open(QIODevice::WriteOnly);
    QTextStream out(file);
    out.setCodec("UTF-8");
    out << text;
    file->close();
}

void Log::load()
{
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    in.setCodec("UTF-8");
    text = in.readAll();
    file->close();
}

void Log::append(QString text)
{
    this->text = text + "\n" + this->text;
    save();
}

QString Log::getFileName()
{
    return fileName;
}
