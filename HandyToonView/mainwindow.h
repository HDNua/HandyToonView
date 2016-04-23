////////////////////////////////////////////////////////////////////
// File Name : MainWindow.h
// Date : 2016/04/23
// Compiler : g++ 4.6.3
// Os : Ubuntu 12.04.4 LTS
// Author : DoYeong Han
// =================================================================
// ver : 2.0.0
// Description : MainWindow declaration
// Etc.. : 어디까지가 버전 1인지 아닌지 모르겠어서 그냥 이전까지를
//  다 1로 치고 지금부터 2버전으로 간다
////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui>

class QDir;
class QLabel;
class QImage;
class QMenuBar;
class QMenu;
class QFileDialog;
class QString;
class QStringList;



////////////////////////////////////////////////////////////////////
// template
// -----------------------------------------------------------------
// Purpose:
//  <describe here>
// Input:
//  <describe here>
// Return:
//  <describe here>
////////////////////////////////////////////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // 화면 관리

    // 메뉴 관리
    QMenuBar *_menuBar;

    // 파일 관리
    QDir _dir;
    QString _fileName;
    QFileDialog *_fd;
    QStringList _filters;

    // 이미지 목록 관리
    int _first;
    int _last;
    int _index;
    QImage **_list;
    QStringList _entryList;

    // 이미지 출력
    QLabel *_node;
    QImage *_image;

private:
    // 초기화 함수
    void initWindow();
    void initMenu();
    void initImageList();
    void initControl();



    void initFields();





public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // 추가 메서드
    void glance();
    void printImage();
    void changeImageToLeft();
    void changeImageToRight();

    // 이벤트 처리
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    // 슬롯에 대한 함수
    void beginView();
    void printDeveloper();

public slots:
    // 슬롯 함수
    void slotOpen();    // 파일 오픈 슬롯
    void slotDeveloper();
};

#endif // MAINWINDOW_H
