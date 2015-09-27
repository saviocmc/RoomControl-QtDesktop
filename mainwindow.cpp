#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(exit_room_control()));

//    titlebar = new Titlebar(this);
//    titlebar->setParent(this);

    lamp.setParent(this);
    lamp.setPixmap(QPixmap(":/lamp"));
    lamp.setGeometry(10,10,222,47);

    lumLevel.setParent(this);
    lumLevel.setPixmap(QPixmap(":/lumLevel"));
    lumLevel.setGeometry(20,80,300,46);

    lumProgBar = new QProgressBar(this);
    lumProgBar->setGeometry(10,130,330,30);

    switchButton = new SwitchButton(this,lamp.width() + 20,10);

    mcu_Connector = new MCU_Connector(this);

    connect(switchButton,SIGNAL(clicked(bool)),this->mcu_Connector,SLOT(switchClicked(bool)));
    connect(mcu_Connector,SIGNAL(relayStateChanged(bool)),switchButton,SLOT(setState(bool)));
    connect(mcu_Connector,SIGNAL(statusMessenger(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
    connect(mcu_Connector,SIGNAL(lumLevelChanded(int)),lumProgBar,SLOT(setValue(int)));

    this->setGeometry(500,250,lamp.width()+switchButton->QpixOn.width() + 30,200);

    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::Tool);

    mcu_Connector->startConnection();
}

MainWindow::~MainWindow()
{
    delete lumProgBar;
    delete switchButton;
    delete mcu_Connector;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    //hide();
    //event->ignore();
}
