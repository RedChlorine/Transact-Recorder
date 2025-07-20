//this is as far as i got..
//Student 64602893 - Vinchelo Theodore Fourie
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addItemDialog.h"
#include "purchaseFormDialog.h"
#include <QIcon>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this); - Not using QtDesigner

    //setting the window app icon
    //icon is in the .qrc resource file
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle("GlassCase - Transaction DB");
    resize(800,600);

    //DEBUG - DUMMY CUSTOMER LIST INITIALISATION
    customerNames << "Zero" << "One" << "Two" << "Three";

    //~~~~~Add Item dialog trigger~~~~~
    QPushButton *shopButton = new QPushButton("Open Shop Dialog", this); // Create the button
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->addWidget(shopButton, 0, Qt::AlignCenter);
    centralLayout->addStretch(); // Push the button to the top/center
    setCentralWidget(centralWidget);

    // Connect the button's clicked signal to your slot
    connect(shopButton, &QPushButton::clicked, this, &MainWindow::addItemDialogTriggered);

    //~~~~~Purchase dialog trigger~~~~~
    //Create button and add it to the central layout
    QPushButton *purchaseButton = new QPushButton("Open Purchase Form", this);
    centralLayout ->addWidget(purchaseButton, 0, Qt::AlignCenter);

    //connecting the button to the slot
    connect(purchaseButton, &QPushButton::clicked, this, &MainWindow::purchaseDialogTriggered);

    //adjusting layout of main window
    centralLayout -> addStretch();
    setCentralWidget(centralWidget);

    //making a menu bar...
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    //adding "File" to the menu bar
    QMenu *fileMenu = menuBar -> addMenu("File");

    //adding an exit option to the file menu and the adjoining slot for the action
    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{

}

//Handler for the addItem dialog
void MainWindow::addItemDialogTriggered()
{
    AddItemDialog addItemDialog(this);

    int result = addItemDialog.exec();

    if(result == QDialog::Accepted)
    {
        QString itemType = addItemDialog.getItemType();
        QString itemName = addItemDialog.getItemName();
        QMessageBox::information(this, "Item Added",
                                 QString("Added Item:\nType: %1\nName: %2")
                                     .arg(itemType)
                                     .arg(itemName));
    }

    else
    {
        QMessageBox::information(this, "Item Addition", "Item addition was canceled.");
    }
}


//Handler fo the purchase form dialog
void MainWindow::purchaseDialogTriggered()
{
    PurchaseFormDialog purchaseDialog(customerNames, this);

    int result = purchaseDialog.exec(); //show the dialog

    if(result == QDialog::Accepted)
    {
        QString selectedCustomer = purchaseDialog.getCustomer();
        QVector<PurchasedItem> purchasedItems = purchaseDialog.getPurchasedItem();

        if(purchasedItems.isEmpty())
        {
            QMessageBox::information(this, "Purchase Complete",
                                     QString("Customer '%1' completed transaction with no items.").arg(selectedCustomer));
        }

        else
        {
            QString summary = QString("Purchase for Customer: %1\n").arg(selectedCustomer);
            summary += "Items:\n";

            for (const PurchasedItem& item : purchasedItems)
            {
                summary += QString("- %1 (%2) x %3\n").arg(item.itemName).arg(item.itemType).arg(item.quantity);
            }
        }
    }
    else
    {
        QMessageBox::information(this, "Purchase Canceled", "Purchase transaction was canceled.");
    }
}
