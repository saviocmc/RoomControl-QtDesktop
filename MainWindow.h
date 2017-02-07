#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QDebug>
#include <QLabel>
#include <McuConnector.h>
#include <SwitchButton.h>
#include <Titlebar.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private slots:
    void exitRoomControl(){close();}

private:
    Ui::MainWindow *ui;
    McuConnector *mcuConnector;
    SwitchButton *switchButton;
    QProgressBar *lumProgBar;
    QLabel lamp,lumLevel;
    Titlebar *titlebar;
};

#endif // MAINWINDOW_H
