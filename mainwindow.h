#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AddItemDialog;
class PurchaseDialog;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addItemDialogTriggered();
    void purchaseDialogTriggered();

private:
    Ui::MainWindow *ui;
    QStringList customerNames; //DEBUG - FOR LATER USE

    //menus
    QMenuBar *menuBar;
    QMenu *fileMenu;

};
#endif // MAINWINDOW_H
