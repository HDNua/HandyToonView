#include "mainwindow.h"

#include <Qt>
#include <QtCore>
#include <QtGui>

#include <iostream>

// 한 번의 초기화 이후에 다시 그 값을 설정하지 않음


#define ADD_ACTION_TO_MENU(MENU, ACTION_NAME, SIG, SLT) \
     action = new QAction(tr(ACTION_NAME), this);       \
     connect(action, SIGNAL(SIG), this, SLOT(SLT));     \
     MENU->addAction(action)

#define ADD_ACTION_TO_MENU_WITH_SHORTCUT(MENU, ACTION_NAME, SIG, SLT, SC) \
    ADD_ACTION_TO_MENU(MENU, ACTION_NAME, SIG, SLT); action->setShortcut(SC)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /******* 기본 값 설정 *******/
    this->BasicValueSetting();

    /******* 메뉴 *******/
    this->MenuSetting();

    /******* 이미지 목록 관리 *******/
    this->ImageListInit();

    /******* 이미지 출력 *******/
    this->ImagePrintInit();
}

MainWindow::~MainWindow()
{

}

// 내부 메서드
void MainWindow::BasicValueSetting()
{
    this->showMaximized();
    this->setMaximumSize(1215, 747);
    this->setMinimumSize(this->maximumSize());

    std::cout<<this->maximumHeight()<<std::endl;

//    this->setBackgroundRole(QPalette::color());
    _dir = "/home";
    _fd = new QFileDialog(this);
    _fd->setDirectory(_dir);

    // 확장자 설정
    _filters << "Image files (*.png *.xpm *.jpg)";
    _fd->setNameFilters(_filters);
//    _fd->setOption(QFileDialog::ShowDirsOnly, true);
}
void MainWindow::MenuSetting()
{
    QMenu *menu;
    QAction *action;

    // 메뉴 초기화
    _menuBar = menuBar();

    menu = new QMenu(tr("&File"));
    _menuBar->addMenu(menu);
//    ADD_ACTION_TO_MENU(menu, "&Open", triggered(), open());
//    ADD_ACTION_TO_MENU(menu, "E&xit", triggered(), close());
    ADD_ACTION_TO_MENU_WITH_SHORTCUT(menu, "&Open", triggered(), open(), QKeySequence::Open);
    ADD_ACTION_TO_MENU_WITH_SHORTCUT(menu, "E&xit", triggered(), close(), QKeySequence::Quit);

    menu->addSeparator();

    menu = new QMenu(tr("&Setting"));
    _menuBar->addMenu(menu);

    ADD_ACTION_TO_MENU(menu, "De&veloper", triggered(), developer());
}
void MainWindow::ImageListInit()
{
    _first = -1;
    _last = -1;
    _index = -1;
    _list = 0;
}
void MainWindow::ImagePrintInit()
{
    _node = new QLabel(this);
    _image = new QImage();
}

// 추가 메서드
void MainWindow::glance()
{

//    const char *str = _dir.path().toUtf8();
//    std::cout<<str<<std::endl;

//    _max = _dir.count();
    _entryList = _dir.entryList();

    /*
    int i;
    std::cout<<"Count = "<<_entryList.count()<<std::endl;
    std::cout<<"Enumerate Start"<<std::endl;
    for (i=0; i<_entryList.count(); ++i)
    {
        const char *str = _entryList.value(i).toUtf8();
        std::cout<<str<<std::endl;
    }
    std::cout<<"Enumberate End"<<std::endl;
    */

    _last  = _entryList.count() - 2;            // ., ..과 같은 것도 경로로 치는 모양이다.
    _index = _entryList.indexOf(_fileName);
    _first = _index;

    std::cout<<"First: "<<_first<<std::endl;
    std::cout<<"Index: "<<_index<<std::endl;
    std::cout<<"Last : "<<_last<<std::endl;
}
void MainWindow::printImage()
{
    QString fileName = _entryList.value(_index);
//    const char *str = fileName.toUtf8();
//    std::cout<<str<<std::endl;

    fileName = _dir.absoluteFilePath(fileName);
    if( _image->load(fileName) )
    {
        double d_width = _image->width();
        double d_height = _image->height();

        double ratio = d_width/d_height;
        d_height = this->maximumHeight();
        d_width = ratio * d_height;

        int width = d_width;
        int height = d_height;

//        std::cout<<"Image's width = "<<width<<std::endl;
//        std::cout<<"Image's height = "<<height<<std::endl;

//        _image->scaledToHeight(747, Qt::FastTransformation);

        QImage image = _image->scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        this->setGeometry(0, 0, this->geometry().width(), this->geometry().height());

        _node->setPixmap(QPixmap::fromImage(image));
        _node->setGeometry(this->geometry().width()/2 - width/2,
                           this->geometry().height()/2 - height/2,
                           width,
                           height);
        _node->show();
    }
}
void MainWindow::changeImageToLeft()
{
    if( --_index<_first )
        _index = _last;

    std::cout<<"First: "<<_first<<std::endl;
    std::cout<<"Index: "<<_index<<std::endl;
    std::cout<<"Last : "<<_last<<std::endl;
    this->printImage();
}
void MainWindow::changeImageToRight()
{
    if( ++_index>_last)
        _index = _first;

    std::cout<<"First: "<<_first<<std::endl;
    std::cout<<"Index: "<<_index<<std::endl;
    std::cout<<"Last : "<<_last<<std::endl;
    this->printImage();
}

// 이벤트 처리
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

//    std::cout<<key<<std::endl;
//    printf("%0x\n", key);

    switch (key)
    {
    // 방향키에 대한 이벤트 설정
    case Qt::Key_Up:
//        std::cout<<"Up"<<std::endl;
        this->showMaximized();
        break;
    case Qt::Key_Right:
//        std::cout<<"Right"<<std::endl;
        this->changeImageToRight();
        break;
    case Qt::Key_Down:
//        std::cout<<"Down"<<std::endl;
        this->showMinimized();
        break;
    case Qt::Key_Left:
//        std::cout<<"Left"<<std::endl;
        this->changeImageToLeft();
        break;

    // 기타 키에 대한 이벤트
    case Qt::Key_Return:
    case Qt::Key_Enter:
//        std::cout<<"Enter"<<std::endl;
        this->process_open();
        break;
    }
}
/*
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();

    std::cout<<size.width()<<std::endl;
    std::cout<<size.height()<<std::endl;

    // (1215, 747) / (1215, 776)
}*/

// 슬롯에 대한 함수
void MainWindow::process_open()
{
    QString filePath = _fd->getOpenFileName(this);
    if( !filePath.isNull() )
    {
        QDir dir = QFileInfo(filePath).absoluteDir();
        _dir = dir;
        _fileName = _dir.relativeFilePath(filePath);

        this->glance();
        this->printImage();
    }
}
void MainWindow::print_developer()
{
}

// 슬롯 메서드
void MainWindow::open()
{
    this->process_open();
}
void MainWindow::developer()
{
    this->print_developer();
}
