#include "addItemDialog.h"
#include <QMessageBox>

AddItemDialog::AddItemDialog(QWidget *parent):QDialog(parent)
{
    //window set up
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowTitle("GlassCase - Add Item Form");
    setMinimumSize(200, 100);
    setMaximumSize(450, 350);

    //ui setup helper
    setupUI();
}

AddItemDialog::~AddItemDialog()
{
    //Qt parent-child deletion
}

void AddItemDialog::setupUI()
{
    //Creating the widgets for the dialog
    //Heading
    titleLabel = new QLabel("Please fill in this form", this);
    titleLabel -> setAlignment(Qt::AlignCenter);
    titleLabel -> setFont(QFont("Arial",11,QFont::Bold));

    //Combobox
    itemTypeLabel = new QLabel("Item type:", this);
    itemTypeCombo = new QComboBox(this);
    itemTypeCombo ->addItem("Book");
    itemTypeCombo ->addItem("Magazine");

    //Line edit
    itemNameLabel = new QLabel("Name of item:", this);
    itemNameLineEdit = new QLineEdit(this);
    itemNameLineEdit -> setPlaceholderText("e.g. Vogue, AutoTrader");

    //Pushbutton
    addItemButton = new QPushButton("Add Item", this);

    //initializing the layouts so that they aren't null
    QFormLayout* formLayout = new QFormLayout();
    QVBoxLayout* dialogLayout = new QVBoxLayout(this);

    //Creating the layout for the widgets
    formLayout -> addRow(itemTypeLabel,itemTypeCombo);
    formLayout -> addRow(itemNameLabel,itemNameLineEdit);

    dialogLayout -> addWidget(titleLabel);
    dialogLayout -> addSpacing(15);

    dialogLayout -> addLayout(formLayout);
    dialogLayout -> addStretch();

    dialogLayout -> addWidget(addItemButton,0,Qt::AlignCenter);
    dialogLayout -> addSpacing(10);

    //Setting the main dialog layout
    setLayout(dialogLayout);

    //Signals and Slots
    //PushButton sends a signal when clicked and calls addItemButtonClicked() custom slot
    connect(addItemButton, &QPushButton::clicked, this, &AddItemDialog::addItemButtonClicked);
}

//Getters
//Returns the current item type
QString AddItemDialog::getItemType() const
{
    return itemTypeCombo -> currentText();
}

//Returns the current item name, without leanding or trailing WS.
QString AddItemDialog::getItemName() const
{
    return itemNameLineEdit -> text().trimmed();
}

void AddItemDialog::addItemButtonClicked()
{
    //checking if user is tryiong to add empty fields
    if(itemNameLineEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Input Error","Please enter a name for the item.");
        //resets focus on the item name field;
        itemNameLineEdit -> setFocus();
        return;
    }

    //if field is not null, emit accept sigal.
    accept();
}







