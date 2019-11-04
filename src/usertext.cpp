#include "usertext.h"

UserText::UserText()
{
    file = new QFile;
    file->setFileName(fileName);
    if(isExist())
    {
        this->load();
    }
}

bool UserText::isExist()
{
    bool result = false;
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result = true;
    }
    file->close();
    return result;
}

void UserText::save()
{
    file->open(QIODevice::WriteOnly);
    QTextStream out(file);
    out.setCodec("UTF-8");
    out << text;
    file->close();
}

void UserText::load()
{
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    in.setCodec("UTF-8");
    text = in.readAll();
    file->close();
}

void UserText::setText(QString text)
{
    this->text = text;
}

QString UserText::getText()
{
    return text;
}

QString UserText::getFileName()
{
    return fileName;
}
