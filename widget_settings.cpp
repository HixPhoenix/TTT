#include "widget_settings.h"
#include "ui_widget_settings.h"

widget_settings::widget_settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_settings)
{
    ui->setupUi(this);

    ui->lin_widgetSizeH->setDisabled(true);
    ui->lin_widgetSizeW->setDisabled(true);
}

widget_settings::~widget_settings()
{
    delete ui;
}

void widget_settings::on_btn_settingSave_clicked()
{
    int index = ui->cbSizeWidget->currentIndex();

    if(ui->cbSizeWidget->isEnabled())
        switch (index) {
        case 0:
            emit signalChangeSize(MIN_WINDOW_WIDTH,MIN_WINDOW_HEIGHT);
            break;
        case 1:
            emit signalChangeSize(600,600);
            break;
        case 2:
            emit signalChangeSize(800,800);
            break;
        case 3:
            emit signalChangeSize(1000,1000);
            break;
        default:
            ;
        }

    if(!ui->cbSizeWidget->isEnabled())
        emit signalChangeSize(ui->lin_widgetSizeW->text().toInt(), ui->lin_widgetSizeH->text().toInt());

    this->hide();

}


void widget_settings::on_checkBox_clicked(bool checked)
{
    ui->lin_widgetSizeH->setDisabled(!checked);
    ui->lin_widgetSizeW->setDisabled(!checked);
    ui->cbSizeWidget->setDisabled(checked);
}

