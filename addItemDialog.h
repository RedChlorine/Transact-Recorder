#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

class AddItemDialog : public QDialog
{
    Q_OBJECT //for signals and slots

public:
    //constructor
    explicit AddItemDialog(QWidget *parent = nullptr);
    //destructor
    ~AddItemDialog();

    //Public getters for info from the dialog
    QString getItemType() const;
    QString getItemName() const;

private slots:
    //slot for the "add item" button
    void addItemButtonClicked();

private:
    //declaratoin of the widgets
    QLabel *titleLabel;
    QLabel *itemTypeLabel;
    QLabel *itemNameLabel;

    QComboBox *itemTypeCombo;
    QLineEdit *itemNameLineEdit;

    QPushButton *addItemButton;

    //screen layouts
    QVBoxLayout *dialogLayout;
    QFormLayout *formLayout;

    //helper function to set UI
    void setupUI();
};

#endif // ADDITEMDIALOG_H
