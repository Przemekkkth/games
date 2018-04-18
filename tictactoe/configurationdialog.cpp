#include "configurationdialog.h"
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>


ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent)
{
	createWidgets();
	createLayouts();
    updateOKButtonState();
	translateUi();
	createConnections();
	updateOKButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    
}

void ConfigurationDialog::setPlayer1Name(const QString& p1name)
{
   m_player1NameEdit->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(const QString &p2name)
{
   m_player2NameEdit->setText(p2name);
}

QString ConfigurationDialog::player1Name() const
{
    return m_player1NameEdit->text();
}

QString ConfigurationDialog::player2Name() const
{
    return m_player2NameEdit->text();
}

void ConfigurationDialog::updateOKButtonState()
{
	bool p1NameEmpty = m_player1NameEdit->text().isEmpty();
    bool p2NameEmpty = m_player2NameEdit->text().isEmpty();
    m_AcceptButton->setDisabled(p1NameEmpty || p2NameEmpty);
}

void ConfigurationDialog::createWidgets()
{
	m_player1NameEdit = new QLineEdit;
	m_player2NameEdit = new QLineEdit;
	m_player1Label = new QLabel;
	m_player2Label = new QLabel;
	m_AcceptButton = new QPushButton;
	
}

void ConfigurationDialog::createLayouts()
{
	QHBoxLayout *hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(m_player1Label );
	hlayout1->addWidget(m_player1NameEdit);
	
	QHBoxLayout *hlayout2 = new QHBoxLayout;
	hlayout2->addWidget(m_player2Label);
	hlayout2->addWidget(m_player2NameEdit);
	
	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addSpacing(10);
	vlayout->addWidget(m_AcceptButton);
	setLayout(vlayout);
}

void ConfigurationDialog::translateUi()
{
	m_player1Label->setText(tr("Player1: "));
	m_player2Label->setText(tr("Player2: "));	
	m_AcceptButton->setText(tr("OK"));
}

void ConfigurationDialog::createConnections()
{
	connect(m_player1NameEdit, SIGNAL(textChanged(QString)), this, SLOT(updateOKButtonState()));
    connect(m_player2NameEdit, SIGNAL(textChanged(QString)), this, SLOT(updateOKButtonState()));
    connect(m_AcceptButton, SIGNAL(clicked(bool)), this , SLOT(accept()));
}
