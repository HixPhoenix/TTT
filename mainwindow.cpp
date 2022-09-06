#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setting();

    w_setting = new widget_settings;
    connect(w_setting, &widget_settings::signalChangeSize, this, [&](int w, int h){
        this->setMinimumSize(w, h);
        this->setMaximumSize(w + 100, h + 100);
    });

    ui->menubar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete w_setting;
    delete field;
}

bool winning(Matrix<Moves, SIZE_BOARD> &board, PLAYERS player)
{
    if((board.at(0).plType == player && board.at(1).plType == player && board.at(2).plType == player) ||
            (board.at(3).plType == player && board.at(4).plType == player && board.at(5).plType == player)||
            (board.at(6).plType == player && board.at(7).plType == player && board.at(8).plType == player)||
            (board.at(0).plType == player && board.at(3).plType == player && board.at(6).plType == player)||
            (board.at(1).plType == player && board.at(4).plType == player && board.at(7).plType == player)||
            (board.at(2).plType == player && board.at(5).plType == player && board.at(8).plType == player)||
            (board.at(0).plType == player && board.at(4).plType == player && board.at(8).plType == player)||
            (board.at(2).plType == player && board.at(4).plType == player && board.at(6).plType == player))
    {
        qDebug() << "Победа: " << player;
        return true;
    }
    else
        return false;
}

QList<int> emptyID(Matrix<Moves, SIZE_BOARD> &board)
{
    QList<int> emptyCells;
    for(size_t i = 0; i <= SECTIONS::NINTH; i++){
        if(board.at(i).id == UNDEFINED){
            emptyCells.append(i);
        }
    }
    return emptyCells;
}



int score(Matrix<Moves, SIZE_BOARD> newBoard)
{
    if(winning(newBoard, PLAYER))
        return 10;
    else if(winning(newBoard, AI))
        return -10;
    else
        return 0;
}
SECTIONS AI_Move(Matrix<Moves, SIZE_BOARD> &board){
    return FIRST;
}

int minimax(Matrix<Moves, SIZE_BOARD> newBoard, Moves p)
{

}
void MainWindow::setting()
{

    this->setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
    this->setMaximumSize(MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
}

Playground::~Playground()
{
    if(!items().isEmpty())
        for(auto it : items())
            delete it;
}

void Playground::draw(QGraphicsItem *figure)
{
    if(groupShapes){
        groupShapes->addToGroup(figure);
        _scene->update();
    }
    else {
        qDebug() << "ERROR: " << ERRORS::FAILED_TO_DRAW_SHAPE << ": " << SCENE_NOT_DEFINED;
        delete figure;
    }
}

void Playground::update()
{
    if(_scene)
        _scene->update();
    else
        qDebug() << "ERROR: " << ERRORS::SCENE_NOT_DEFINED;

    qDebug() << groupShapes->childItems();

}

Playground::Playground(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали

    set();

}

void Playground::set()
{ 
    _scene = new QGraphicsScene(rect());

    groupMarkup = new QGraphicsItemGroup;
    groupShapes = new QGraphicsItemGroup;


    this->setScene(_scene);

    _scene->addItem(groupMarkup);
    _scene->addItem(groupShapes);

}

bool Playground::clear(QGraphicsItemGroup *group)
{
    if(!group)
        return false;
    for(auto it : _scene->items())
        if(it->group() == group){
            delete it;
        }
    return true;
}

bool Playground::clear(const DELETE variant)
{
    switch (variant) {
    case MARKUP:
        return clear(groupMarkup);
    case GRAPHICS_BOARD:
        return clear(groupShapes);
    case DATA_BOARD:
        //        if(_board)
        //            for(int i = 0; i <= SECTIONS::NINTH; i++)
        //                if(_board->at(i).id != UNDEFINED)
        //                    _board->at(i).clear();

        return true;
        ;
    }
    return false;
}


SECTIONS Playground::pressed(QMouseEvent *event)
{
    int w = width();
    int h = height();

    if((event->x() < w / 3 && event->y() < h / 3))
        return FIRST;

    else if((event->x() > w / 3 && event->y() < h / 3) &&
            (event->x() < w / 1.5 && event->y() < h / 3))
        return SECOND;

    else if(event->x() > w / 1.5 && event->y() < h / 3)
        return THIRD;

    else if((event->x() < w / 3 && event->y() > h / 3) &&
            (event->x() < width() / 3 && event->y() < h / 1.5))
        return FOURTH;

    else if((event->x() > w / 3 && event->y() > h / 3) &&
            (event->x() < w/ 1.5 && event->y() > h / 3) &&
            (event->x() > w / 3 && event->y() < h/ 1.5) &&
            (event->x() < w / 1.5 && event->y() < h / 1.5))
        return FIFTH;

    else if(event->x() > w / 1.5 && event->y() > h / 3 &&
            (event->x() > w / 1.5 && event->y() < h / 1.5))
        return SIXTH;

    else if((event->x() < w / 3 && event->y() > h / 1.5))
        return SEVENTH;

    else if((event->x() > w / 3 && event->y() > h / 1.5) &&
            (event->x() < w / 1.5 && event->y() > h / 1.5))
        return EIGHTH;

    else if((event->x() > w / 1.5 && event->y() > h / 1.5))
        return NINTH;

    else{
        qDebug() << "ERROR:" << SECTIONS::UNDEFINED;
        return SECTIONS::UNDEFINED;
    }
}

bool Playground::redraw()
{
    /// рисовка разметки игрового поля;

    groupMarkup->addToGroup(_scene->addLine(width()/ 3 - 3, height(), width() / 3 - 3, 0, QPen(Qt::black, 2)));
    groupMarkup->addToGroup(_scene->addLine(width()/ 1.5 - 3, height(), width() / 1.5 - 3, 0, QPen(Qt::black, 2)));
    groupMarkup->addToGroup(_scene->addLine(width(), height() / 3 - 3, 0, height() / 3 - 3, QPen(Qt::black, 2)));
    groupMarkup->addToGroup(_scene->addLine(width(), height() / 1.5 - 3, 0, height() / 1.5 - 3, QPen(Qt::black, 2)));

    return _scene->items().size() > 5 + SECTIONS::NINTH + ALL_GROUPS? false : true;
}

void Playground::start()
{
    firstMove = (randomValue.global()->bounded(0, INVOLVED)) == 0 ? PLAYER : AI;

    if(firstMove == AI){
        // Пусть компьютер первый ход делает случайным. Так как все поля с первым ходом пусты - дополнительных проверок не требуется.
        int randSection = randomValue.global()->bounded(0, emptyID(_board).length());

        player = {AI, (SECTIONS)randSection, CROSS};
        _board.at(randSection) = player;
        draw(new Shapes(CROSS, Pos(width(),height(),(SECTIONS)randSection)));
    }

    qDebug() << "Игрок: " << firstMove;
}

void Playground::resizeEvent(QResizeEvent *event)
{

    _scene->setSceneRect(rect());
    clear(GRAPHICS_BOARD);
    clear(MARKUP);

    for(int i = 0; i <= SECTIONS::NINTH; i++)
        if(_board.at(i).id != UNDEFINED)
            draw(new Shapes(_board.at(i).shape, Pos(width(),height(),(SECTIONS)i)));


    redraw();
}

void Playground::mousePressEvent(QMouseEvent *event)
{  
    // Проверка состояния игры:
    if(winning(_board, PLAYER) || winning(_board, AI)){
        qDebug() << "Игра окончена, стооооопеее!!";
        return;
    }
    else{
        // При нажатии отрабатывается два хода: игрока и компьютера.
        // Ход игрока:
        SECTIONS s = pressed(event);

        // Проверка на свободное поле:
        if(_board.at(s).id == UNDEFINED){
            player = {PLAYER, s, player.shape == CROSS ? CIRCLE : CROSS};
            _board.at(s) = player;
            draw(new Shapes(_board.at(s).shape, Pos(width(), height(), s)));
        }
        // Если игрок не выиграл после своего хода - ход предоставляется компьютеру.
        if(!winning(_board, PLAYER)){
            //Ход компьютера:
            SECTIONS sAI = AI_Move(_board);
            if(_board.at(sAI).id == UNDEFINED){
                player = {AI, sAI, player.shape == CROSS ? CIRCLE : CROSS};
                _board.at(sAI) = player;
                draw(new Shapes(_board.at(sAI).shape, Pos(width(), height(), sAI)));
                // Проверка на выигрыш хода компьютера.
                winning(_board, AI);
            }
        }

    }



    update();
}

void MainWindow::on_pushButton_clicked()
{
    field->clear(GRAPHICS_BOARD);
    field->clear(DATA_BOARD);
    field->update();
}

void MainWindow::on_btn_startGame_clicked()
{
    field = new Playground;
    field->start();

    ui->verticalLayout_2->addWidget(field);
    ui->menubar->setVisible(true);
    ui->stackedWidget->setCurrentIndex(GAME);
}


void MainWindow::on_btn_exit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_action_triggered()
{
    delete field;
    field = nullptr;
    ui->stackedWidget->setCurrentIndex(MENU);
    ui->menubar->setVisible(false);

}


void MainWindow::on_action_2_triggered()
{
    on_action_triggered();
    on_btn_startGame_clicked();
}


void MainWindow::on_action_5_triggered()
{
    QApplication::quit();
}


void MainWindow::on_action_3_triggered()
{
    w_setting->show();
}


void MainWindow::on_btn_settings_clicked()
{
    w_setting->show();
}

