#include "configurationdialog.h"
#include "ui_configurationdialog.h"
#include <QPushButton>
ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    updateOKButtonState();
    connect(ui->player1Name, SIGNAL(textChanged(QString)), this, SLOT(updateOKButtonState()));
    connect(ui->player2Name, SIGNAL(textChanged(QString)), this, SLOT(updateOKButtonState()));
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::setPlayer1Name(const QString& p1name)
{
    ui->player1Name->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(const QString &p2name)
{
    ui->player2Name->setText(p2name);
}

QString ConfigurationDialog::player1Name() const
{
    return ui->player1Name->text();
}

QString ConfigurationDialog::player2Name() const
{
    return ui->player2Name->text();
}

void ConfigurationDialog::updateOKButtonState()
{
    bool p1NameEmpty = ui->player1Name->text().isEmpty();
    bool p2NameEmpty = ui->player2Name->text().isEmpty();
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDisabled(p1NameEmpty || p2NameEmpty);
}
