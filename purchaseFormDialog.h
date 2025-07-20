#ifndef PURCHASEFORMDIALOG_H
#define PURCHASEFORMDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QFormLayout>
#include <QVector>
#include <QDateTime>

struct PurchasedItem
{
    QString itemName;
    QString itemType;
    QDateTime purchaseTimestamp;
    int quantity;
};

class PurchaseFormDialog : public QDialog
{
    Q_OBJECT

public:
    //constructor
    explicit PurchaseFormDialog(const QStringList& customers, QWidget *parent = nullptr);

    //destructor
    ~PurchaseFormDialog();

    //getters for the transaction data
    QString getCustomer() const;
    QVector<PurchasedItem> getPurchasedItem() const;

private slots:
    //slots for controling the buttons of this dialog
    void addItemButtonClicked();
    void doneButtonClicekd();

private:
    //labels
    QLabel *purchaseTitleLabel;
    QLabel *selectCustLabel;
    QLabel *selectItemLabel;
    QLabel *itemTypeLabel;
    QLabel *itemQuantityLabel;

    //dropdown menus
    QComboBox *selectCustCombo;
    QComboBox *selectItemCombo;

    //quantity spinbox
    QSpinBox *itemQuantitySpinner;

    //buttons
    QPushButton *addItemPushbutton;
    QPushButton *completeFormPushbutton;

    //table for the rrecord of purchases/items added.
    QTableWidget *purchaseRecordTable;

    //layouts
    QVBoxLayout *dialogMainLayout;
    QFormLayout *formLayout;
    QHBoxLayout *buttonLayout;

    QVector<PurchasedItem> transactionItems;

    //UI helper and table helper
    void setupUI();
    void setupTable();
};
#endif // PURCHASEFORMDIALOG_H
