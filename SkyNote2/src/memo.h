#ifndef MEMO_H
#define MEMO_H

#include "log.h"
#include "usertext.h"
#include "usersetting.h"

namespace Ui {
class Memo;
}

class Memo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Memo(QWidget *parent = 0);
    void Theme_Load(int num);
    void Font_Load(int size);
    void Start_Position(int x,int y);
    void Min_Check(int a);
    void myResetText();

    Log *getLog();
    UserText *getUserText();
    UserSetting *getUserSetting();
    ~Memo();

private slots:
    void on_settingButton_clicked();
    void on_uploadButton_clicked();
    void on_downloadButton_clicked();
    void on_logButton_clicked();
    void on_exitButton_clicked();
    void on_extendButton_clicked();
    void on_mainTextEdit_textChanged();

private:
    Ui::Memo *ui;
    Log *log;
    UserText *userText;
    UserSetting *userSetting;
    bool isMouseDown;
    bool isExtend = true;
    bool isViewLog = false;
    int custom_x = 50;
    int custom_y = 200;

protected:
   int m_nMouseClick_X_Coordinate;
   int m_nMouseClick_Y_Coordinate;
   void mousePressEvent(QMouseEvent * event);
   void mouseReleaseEvent(QMouseEvent * event);
   void mouseMoveEvent(QMouseEvent * event);
};

#endif // MEMO_H
