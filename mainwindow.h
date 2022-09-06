#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "setting.h"
#include "widget_settings.h"
#include "shape.h"
#include <QMainWindow>
#include <matrix.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

///////////////// Graphics Inteface ///////////////////////////
class Playground : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Playground(QWidget *parent = nullptr);
    ~Playground();
    void draw(QGraphicsItem *figure);
    bool redraw();

    void start();
    bool clear(const DELETE variant);
    void update();
private:
    void set();

    SECTIONS pressed(QMouseEvent *event);
    bool clear(QGraphicsItemGroup *group);

    Matrix<Moves, SIZE_BOARD> _board;
    QGraphicsScene *_scene{nullptr};
    QGraphicsItemGroup *groupMarkup{nullptr};
    QGraphicsItemGroup *groupShapes{nullptr};
    PLAYERS firstMove;
    Moves player;
    QRandomGenerator randomValue;
Q_SIGNALS:
    void signalRecordMoves(Moves p);
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
};


/////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_btn_startGame_clicked();

    void on_btn_exit_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_5_triggered();

    void on_action_3_triggered();

    void on_btn_settings_clicked();
private:
    bool isPlayerMove();
private:
    Ui::MainWindow *ui;
    void setting();
    Playground *field{nullptr};

    QRandomGenerator randomValue;
    PLAYERS firstMove;
    Matrix<Moves, SIZE_BOARD> *board{nullptr};
    widget_settings *w_setting{nullptr};

};
#endif // MAINWINDOW_H
