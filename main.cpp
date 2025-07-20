////Student 64602893 - Vinchelo Theodore Fourie
#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
//#include <QTimer>  -  DEPRICATED
#include <QThread>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //~~~~~START OF SPLASH SCREEN~~~~~

    //Load the image from the Qt Resource System
    //The path starts with ":/" followed by the filename in .qrc
    QPixmap splashImg(":/images/Splash Screen.png");

    //Check if the pixmap loaded successfully
    if (splashImg.isNull())
    {
        //Debug message to see if it failed
        qDebug() << "Error: Splash image not found in resources.";
    }

    //Shows the splashscreen.
    QSplashScreen splash(splashImg);
    splash.show();

    //shows my student info as a copyright - academic integrity(center top, in white text)
    splash.showMessage("Made by Vinchelo THeodore Fourie\nStudent:64602893", 45, QColorConstants::White);
    QThread::msleep(4000); //used to block the thread to add time to the splash screen - single use.

    //~~~~~END OF SPLASH SCREEN~~~~~~




    MainWindow window;

    splash.finish(&window);
    window.show();

    return app.exec();
}
