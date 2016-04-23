////////////////////////////////////////////////////////////////////
// File Name : MainWindow.cpp
// Date : 2016/04/23
// Compiler : g++ 4.6.3
// Os : Ubuntu 12.04.4 LTS
// Author : DoYeong Han
// =================================================================
// ver : 2.0.0
// Description : MainWindow Implementation
// Etc.. : 어디까지가 버전 1인지 아닌지 모르겠어서 그냥 이전까지를
//  다 1로 치고 지금부터 2버전으로 간다
////////////////////////////////////////////////////////////////////
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



////////////////////////////////////////////////////////////////////
// MainWindow::MainWindow
// -----------------------------------------------------------------
// Purpose:
//  constructor
// Input:
//  (QWidget *parent) -> parent widget object
////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    this->initWindow();
    this->initMenu();

    this->initFields();
    this->initImageList();
    this->initControl();
}
////////////////////////////////////////////////////////////////////
// MainWindow::~MainWindow
// -----------------------------------------------------------------
// Purpose:
//  destructor
////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow() {

}



////////////////////////////////////////////////////////////////////
// MainWindow::initWindow
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
void MainWindow::initWindow() {
    this->showMaximized();
    this->setMaximumSize(1215, 747);
    this->setMinimumSize(this->maximumSize());
///    std::cout<<this->maximumHeight()<<std::endl;
///    this->setBackgroundRole(QPalette::color());
}
////////////////////////////////////////////////////////////////////
// MainWindow::initFields
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
void MainWindow::initFields() {
    _dir = "/home";
    _fd = new QFileDialog(this);
    _fd->setDirectory(_dir);

    // 확장자 설정
    _filters << "Image files (*.png *.xpm *.jpg)";
    _fd->setNameFilters(_filters);
///    _fd->setOption(QFileDialog::ShowDirsOnly, true);
}
////////////////////////////////////////////////////////////////////
// MainWindow::initMenu
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
void MainWindow::initMenu() {
    QMenu *menu;
    QAction *action;

    // 메뉴 초기화
    _menuBar = menuBar();

    menu = new QMenu(tr("&File"));
    _menuBar->addMenu(menu);
//    ADD_ACTION_TO_MENU(menu, "&Open", triggered(), open());
//    ADD_ACTION_TO_MENU(menu, "E&xit", triggered(), close());
    ADD_ACTION_TO_MENU_WITH_SHORTCUT(menu, "&Open", triggered(), slotOpen(), QKeySequence::Open);
    ADD_ACTION_TO_MENU_WITH_SHORTCUT(menu, "E&xit", triggered(), close(), QKeySequence::Quit);

    menu->addSeparator();

    menu = new QMenu(tr("&Setting"));
    _menuBar->addMenu(menu);

    ADD_ACTION_TO_MENU(menu, "De&veloper", triggered(), slotDeveloper());
}
////////////////////////////////////////////////////////////////////
// MainWindow::initImageList
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
void MainWindow::initImageList() {
    _first = -1;
    _last = -1;
    _index = -1;
    _list = 0;
}
////////////////////////////////////////////////////////////////////
// MainWindow::initControl
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
void MainWindow::initControl() {
    _node = new QLabel(this);
    _image = new QImage();
}










////////////////////////////////////////////////////////////////////
// MainWindow::glance
// -----------------------------------------------------------------
// Purpose:
//  glance entry list before traverse
// Input:
//  none
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::glance() {

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

    _last  = _entryList.count() - 2; // ., ..과 같은 것도 경로로 치는 모양이다.
    _index = _entryList.indexOf(_fileName);
    _first = _index;

    std::cout<<"First: "<<_first<<std::endl;
    std::cout<<"Index: "<<_index<<std::endl;
    std::cout<<"Last : "<<_last<<std::endl;
}
////////////////////////////////////////////////////////////////////
// MainWindow::printImage
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
void MainWindow::printImage() {
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
////////////////////////////////////////////////////////////////////
// MainWindow::changeImageToLeft
// -----------------------------------------------------------------
// Purpose:
//  change showing image to left
// Input:
//  none
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::changeImageToLeft() {
    if( --_index<_first )
        _index = _last;

    std::cout<<"First: "<<_first<<std::endl;
    std::cout<<"Index: "<<_index<<std::endl;
    std::cout<<"Last : "<<_last<<std::endl;
    this->printImage();
}
////////////////////////////////////////////////////////////////////
// MainWindow::changeImageToRight
// -----------------------------------------------------------------
// Purpose:
//  change showing image to right
// Input:
//  none
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::changeImageToRight() {
    if( ++_index>_last)
        _index = _first;

    std::cout<<"First: "<<_first<<std::endl;
    std::cout<<"Index: "<<_index<<std::endl;
    std::cout<<"Last : "<<_last<<std::endl;
    this->printImage();
}










////////////////////////////////////////////////////////////////////
// virtual MainWindow::keyPressEvent
// -----------------------------------------------------------------
// Purpose:
//  key event handler
// Input:
//  (QKeyEvent *event) -> key press event object
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch (key) {
        case Qt::Key_Up:
            this->showMaximized();
            break;
        case Qt::Key_Right:
            this->changeImageToRight();
            break;
        case Qt::Key_Down:
            this->showMinimized();
            break;
        case Qt::Key_Left:
            this->changeImageToLeft();
            break;

        case Qt::Key_Return:
        case Qt::Key_Enter:
            this->beginView();
            break;
    }
}
////////////////////////////////////////////////////////////////////
// virtual MainWindow::resizeEvent
// -----------------------------------------------------------------
// Purpose:
//  resize event handler
// Input:
//  (QResizeEvent *event) -> resize event object
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize size = event->size();
    std::cout<<size.width()<<std::endl;
    std::cout<<size.height()<<std::endl;

/// (1215, 747) / (1215, 776)
}










////////////////////////////////////////////////////////////////////
// MainWindow::beginView
// -----------------------------------------------------------------
// Purpose:
//  begin to view manga
// Input:
//  none
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::beginView() {
    QString filePath = _fd->getOpenFileName(this);



    if( !filePath.isNull() ) {
        QDir dir = QFileInfo(filePath).absoluteDir();
        _dir = dir;
        _fileName = _dir.relativeFilePath(filePath);

        this->glance();
        this->printImage();
    }
}
////////////////////////////////////////////////////////////////////
// MainWindow::printDeveloper
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  none
// Return:
//  none
////////////////////////////////////////////////////////////////////
void MainWindow::printDeveloper() {

}










////////////////////////////////////////////////////////////////////
// MainWindow::slotOpen
// -----------------------------------------------------------------
// Purpose:
//  slot method; open menu item clicked
////////////////////////////////////////////////////////////////////
void MainWindow::slotOpen() {
    this->beginView();
}
////////////////////////////////////////////////////////////////////
// MainWindow::slotDeveloper
// -----------------------------------------------------------------
// Purpose:
//  slot method; open developer dialog
////////////////////////////////////////////////////////////////////
void MainWindow::slotDeveloper() {
    this->printDeveloper();
}
