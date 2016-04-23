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
    void BasicValueSetting();
    void MenuSetting();
    void ImageListInit();
    void ImagePrintInit();

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
//    void resizeEvent(QResizeEvent *event);

public:
    // 슬롯에 대한 함수
    void process_open();
    void print_developer();

public slots:
    // 슬롯 함수
    void open();    // 파일 오픈 슬롯
    void developer();
};

#endif // MAINWINDOW_H
