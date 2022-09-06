#ifndef WIDGET_SETTINGS_H
#define WIDGET_SETTINGS_H

#include <QWidget>
#include <QDebug>
#include "setting.h"
namespace Ui {
class widget_settings;
}

class widget_settings : public QWidget
{
    Q_OBJECT

Q_SIGNALS:
    void signalChangeSize(int w, int h);
public:
    explicit widget_settings(QWidget *parent = nullptr);
    ~widget_settings();

private slots:
    void on_btn_settingSave_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::widget_settings *ui;
};

#endif // WIDGET_SETTINGS_H
