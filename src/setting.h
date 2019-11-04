#ifndef SETTING_H
#define SETTING_H

#include "memo.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(Memo &ref, QWidget *parent = 0);
    ~Setting();

private slots:
    void on_theme_white_clicked();
    void on_theme_yellow_clicked();
    void on_theme_pink_clicked();
    void on_theme_blue_clicked();
    void on_theme_green_clicked();
    void on_homepageButton_clicked();
    void on_updateButton_clicked();
    void on_resetButton_clicked();
    void on_fontSizeSpinBox_valueChanged(int arg1);
    void on_autoStartCheckBox_stateChanged(int arg1);

private:
    Ui::Setting *ui;
    Memo &memoRef;
};

#endif // SETTING_H
