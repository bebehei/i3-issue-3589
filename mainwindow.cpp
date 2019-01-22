#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTimer>
#include <iostream>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , trayIcon(new QSystemTrayIcon(this))
{
  QTimer *timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(trayavail()));
  timer->start(500);

  // Tray icon menu
  auto menu = this->createMenu();
  this->trayIcon->setContextMenu(menu);

  // App icon
  auto appIcon = QIcon(":/icons/heart.png");
  this->trayIcon->setIcon(appIcon);
  this->setWindowIcon(appIcon);

  // Displaying the tray icon
  this->trayIcon->show();     // Note: without explicitly calling show(), QSystemTrayIcon::activated signal will never be emitted!

  // Interaction
  connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
}

QMenu* MainWindow::createMenu()
{
  // App can exit via Quit menu
  auto quitAction = new QAction("&Quit", this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

  auto menu = new QMenu(this);
  menu->addAction(quitAction);

  return menu;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
    this->trayIcon->showMessage("Hello", "You clicked me!");
    break;
  default:
    ;
  }
}

void MainWindow::trayavail(void)
{
  std::cout << "Is available: " << this->trayIcon->isSystemTrayAvailable() << std::endl;
}
