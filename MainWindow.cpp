#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(exitRoomControl()));

    //titlebar = new Titlebar(this);
    //titlebar->setParent(this);

    lamp.setParent(this);
    lamp.setPixmap(QPixmap(":/lamp"));
    lamp.setGeometry(10,10,222,47);

    lumLevel.setParent(this);
    lumLevel.setPixmap(QPixmap(":/lumLevel"));
    lumLevel.setGeometry(20,80,300,46);

    lumProgBar = new QProgressBar(this);
    lumProgBar->setGeometry(10,130,330,30);

    switchButton = new SwitchButton(this,lamp.width() + 20,10);

    mcuConnector = new McuConnector(this);

    connect(switchButton,SIGNAL(clicked(bool)),this->mcuConnector,SLOT(setRelayState(bool)));
    connect(mcuConnector,SIGNAL(relayStateChanged(bool)),switchButton,SLOT(setState(bool)));
    connect(mcuConnector,SIGNAL(statusMessenger(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
    connect(mcuConnector,SIGNAL(lumLevelChanded(int)),lumProgBar,SLOT(setValue(int)));

    this->setGeometry(500,250,lamp.width()+switchButton->QpixOn.width() + 30,200);

    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::Tool);

    mcuConnector->startConnection();
}

MainWindow::~MainWindow()
{
    delete lumProgBar;
    delete switchButton;
    delete mcuConnector;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    //hide();
    //event->ignore();
}
