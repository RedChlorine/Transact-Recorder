#include "purchaseFormDialog.h"
#include <QMessageBox>
#include <QHeaderView>

// Constructor
PurchaseFormDialog::PurchaseFormDialog(const QStringList& customers, QWidget *parent)
    :QDialog(parent)
{
    //default sizing and appearance setup of dialog
    setWindowTitle("GlassCase - Customer Purchase");
    setMinimumSize(450,400);
    setMaximumSize(650,600);

    //Initialise the UI and table of transaction records
    setupUI();
    setupTable();

    //populating the customer combobox and setting default values
    selectCustCombo -> addItems(customers);
    if (!customers.isEmpty())//if the list is not null then populate and start at first cust
    {
        selectCustCombo -> setCurrentIndex(0);
    }
    else//if no customers are present or list couldnt be populated then disable submission of transactions
    {
        selectCustCombo -> addItem("No customers available");
        selectCustCombo -> setEnabled(false);
        addItemPushbutton ->setEnabled(false); // This is also correct
    }

    //populates the item type combo box

    selectItemCombo -> addItem("Book");
    selectItemCombo -> addItem("Magazine");

    //setting the default quantities for the combo box

    itemQuantitySpinner -> setRange(1,9999);//min,max
    itemQuantitySpinner -> setValue(1); //default value

    //connecting custom signals and slots
    connect(addItemPushbutton, &QPushButton::clicked, this, &PurchaseFormDialog::addItemButtonClicked);
    connect(completeFormPushbutton, &QPushButton::clicked, this, &PurchaseFormDialog::doneButtonClicekd);
}

//destructor - parent-child control
PurchaseFormDialog::~PurchaseFormDialog()
{
    //memory management - widgets are children of this and are deleted when out of scope.
}

//helper function to set up the ui of this -purchase form- dialog
void PurchaseFormDialog::setupUI()
{
    //~~~~~creating the widgets of this form~~~~~
    //title label
    purchaseTitleLabel = new QLabel("Please complete the form below", this);
    purchaseTitleLabel -> setAlignment(Qt::AlignCenter);
    purchaseTitleLabel -> setFont(QFont("Arial",11, QFont::Bold));

    //select customer label & combo box selection
    selectCustLabel = new QLabel("Select Customer", this);
    selectCustCombo = new QComboBox(this);

    //item type and item combo box
    selectItemLabel = new QLabel("Item Type:", this);
    selectItemCombo = new QComboBox(this);

    //quantity label and combobox
    itemQuantityLabel    = new QLabel("Item Quantity:", this);
    itemQuantitySpinner = new QSpinBox(this);

    //add items push button and done push button
    addItemPushbutton     = new QPushButton("Add Item",this);
    completeFormPushbutton  = new QPushButton("Done", this);

    //table of transaction records
    purchaseRecordTable = new QTableWidget(this);
    //~~~~~Widget creation complete~~~~~


    //~~~~~Creating layouts~~~~~
    dialogMainLayout = new QVBoxLayout(this);
    formLayout       = new QFormLayout();
    buttonLayout     = new QHBoxLayout();

    //Adding the widgets to the form layout
    formLayout -> addRow(selectCustLabel, selectCustCombo);//select cust
    formLayout -> addRow(selectItemLabel, selectItemCombo);//select item
    formLayout -> addRow(itemQuantityLabel, itemQuantitySpinner);//item quant

    //Adding widgets to the button layout
    buttonLayout -> addStretch(); //moves add item button to right
    buttonLayout -> addWidget(addItemPushbutton);
    buttonLayout -> addWidget(completeFormPushbutton);
    buttonLayout -> addStretch(); // centers the done button

    //Adding sub layouts to the main layout
    dialogMainLayout -> addWidget(purchaseTitleLabel);
    dialogMainLayout -> addSpacing(15);
    dialogMainLayout -> addLayout(formLayout);
    dialogMainLayout -> addWidget(purchaseRecordTable);
    dialogMainLayout -> addSpacing(10);
    dialogMainLayout -> addLayout(buttonLayout);
    //~~~~~Layout Complete~~~~~

    //~~~~~UI Setup Complete~~~~~
    setLayout(dialogMainLayout);
}

//Setting up the table for transaction records
void PurchaseFormDialog::setupTable()
{
    //headings
    purchaseRecordTable -> setColumnCount(3);
    purchaseRecordTable -> setHorizontalHeaderLabels({"Item Name", "Type", "Quantity"}); //Headings names
    purchaseRecordTable->horizontalHeader()->setStretchLastSection(true); //Last column stretches
    purchaseRecordTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //Make table read-only
    purchaseRecordTable->setSelectionBehavior(QAbstractItemView::SelectRows); //Select entire rows
    purchaseRecordTable->verticalHeader()->setVisible(true); //Show row numbers
}

QString PurchaseFormDialog::getCustomer() const
{
    return selectCustCombo -> currentText();
}

QVector<PurchasedItem> PurchaseFormDialog::getPurchasedItem() const
{
    return transactionItems;
}

//Signals and Slots implementation
void PurchaseFormDialog::addItemButtonClicked()
{
    //Get current selections, assume empty at first
    QString itemName = "PlaceHolder";
    QString itemType = selectItemCombo  -> currentText();
    int     quantity = itemQuantitySpinner -> value();

    //check that quantity is always at least 1
    if (quantity <= 0)
    {
        QMessageBox::warning(this, "Input Error", "Quantity must be greater than zero");
        return;
    }

    //generating a new PurchasedItem struct
    PurchasedItem newItem;
    newItem.itemName = itemName;
    newItem.itemType = itemType;
    newItem.quantity = quantity;

    //Adding the new struct to the list of purchased items
    transactionItems.append(newItem);

    //Adding the transactions to the table widget for record keeping
    int row = purchaseRecordTable -> rowCount();
    purchaseRecordTable -> insertRow(row);
    purchaseRecordTable -> setItem(row, 0, new QTableWidgetItem(newItem.itemName));
    purchaseRecordTable -> setItem(row, 1, new QTableWidgetItem(newItem.itemType));
    purchaseRecordTable -> setItem(row, 2, new QTableWidgetItem(QString::number(newItem.quantity)));

    //return inputs to default values for the next item.
    selectItemCombo     -> setCurrentIndex(0); //reset to first item type
    itemQuantitySpinner -> setValue(1);        //rest quantity to 1

    //confirmation of item added to list
    QMessageBox::information(this, "Item Added", QString("'%1' (Quantity: %2) added to current transaction.").arg(newItem.itemType).arg(newItem.quantity));
}

void PurchaseFormDialog::doneButtonClicekd()
{
    if(transactionItems.isEmpty())
    {
        QMessageBox::warning(this, "No Items", "No items have been added to the transaction lsit. Please add items or cancel");
    }
    accept(); //closes dialog.
}
//~~~~~End of Signals and Slots~~~~~
