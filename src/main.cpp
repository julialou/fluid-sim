#include <QtGui/QApplication>
#include "MainWindow.h"

/// \file main.cpp
/// \brief main
/// \author Julia Lou
/// Revision History :
/// based on ngl demos
/// Initial Version 10/10/10 (Binary day ;-0 )
/* this code runs the basic main window and is created by the Qt Creator app */
int main(int argc, char *argv[])
{
  if(argc<2)
  {
    std::cerr << "Usage: FluidSim [name]\n";
    exit(EXIT_FAILURE);
  }


  // make an instance of the QApplication
  QApplication a(argc, argv);


  // Create a new MainWindow
  MainWindow w(argv[1]);
  // show it
  w.show();
  // hand control over to Qt framework
  return a.exec();
}
