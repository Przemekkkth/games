#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTranslator>
#include "options/options.h"
#include <QEvent>
#include <QMessageBox>
#include <QFile>
extern QTranslator *qTranslator;
extern QPair<int, QTranslator*> language;
Options::Options(QWidget *parent) : QWidget(parent)
{
	createWidgets();
	createLayout();
	translateUi();
	createConnections();
	createStyleSheet();

    language.second->load(":/languages/english");
}

void Options::createWidgets()
{
	
	
	m_TitleLabel = new QLabel();
	m_LanguagesLabel = new QLabel();
	m_WLabel = new QLabel();
	m_DLabel = new QLabel();
	m_SLabel = new QLabel();
	m_ALabel = new QLabel();
	m_PLabel = new QLabel();
	m_SpaceLabel = new QLabel();
	
	m_BackButton = new QPushButton();
	m_ChangeLangComboBox = new QComboBox();
	for(int i = 0 ; i < 4; i++)
	{
		m_ChangeLangComboBox->addItem("");
	}
}

void Options::createLayout()
{
	resize(306, 300);
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(m_TitleLabel);
	layout->addWidget(m_LanguagesLabel);
	layout->addWidget(m_ChangeLangComboBox);
	layout->addWidget(m_WLabel);
	layout->addWidget(m_DLabel);
	layout->addWidget(m_SLabel);
	layout->addWidget(m_ALabel);
	layout->addWidget(m_PLabel);
	layout->addWidget(m_SpaceLabel);
	layout->addWidget(m_BackButton);	
	setLayout(layout);
}

void Options::translateUi()
{
	m_TitleLabel->setText( tr("Game Options") );
    m_LanguagesLabel->setText( tr("Languages:") );
	
	
    m_ChangeLangComboBox->setItemText(0, tr("English") );
    m_ChangeLangComboBox->setItemText(1, tr("Polski") );
    m_ChangeLangComboBox->setItemText(2, tr("Deutsch") );
    m_ChangeLangComboBox->setItemText(3, tr("русский") );
	
	m_WLabel->setText( tr("1.W - up") );
	m_DLabel->setText( tr("2.D - right") );
	m_SLabel->setText( tr("3.S - down") );
	m_ALabel->setText( tr("4.A - left") );
	m_PLabel->setText( tr("5.P - pause") );
	m_SpaceLabel->setText( tr("6.Space - start") );
	
	m_BackButton->setText( tr("Back") );
}

void Options::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange )
    {
        translateUi();
    }
    else
    {
        QWidget::changeEvent(e);
    }
}

void Options::createConnections()
{
	connect(m_ChangeLangComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setCurrentLanguage(int)));
    connect(m_BackButton, SIGNAL(clicked(bool)), this, SLOT(goBack()));
}

void Options::setCurrentLanguage(int choice_)
{
	
	    switch (choice_) {
    case 0:
        language.first = 0;
        language.second->load(":/languages/en_EN.qm");
        //language.second->load("C:\\FolderQt\\gamesV01\\games\\en_EN.qm");
		break;
    case 1:
        language.first = 1;
        language.second->load(":/languages/pl_PL.qm");
        //language.second->load("C:\\FolderQt\\gamesV01\\games\\pl_PL.qm");
        break;
    case 2:
        language.first = 2;
        language.second->load(":/languages/ger_GER.qm");
        //language.second->load("C:\\FolderQt\\gamesV01\\games\\ger_GER.qm");
        break;
    case 3:
        language.first = 3;
        language.second->load(":/languages/rus_RUS.qm");
        //language.second->load("C:\\FolderQt\\gamesV01\\games\\rus_RUS.qm");
		break;
    }
}

void Options::createStyleSheet()
{
	setStyleSheet("QPushButton{background-color: #13100a; border-style: solid;  border-width: 1px; border-radius: 10px; color: white; font-size: 20px; font-family: 'Arial'; font-weight: 500px;} QPushButton:hover{background-color: #24211b;}");
    m_TitleLabel->setStyleSheet("font-size: 25px; font-weight: 800");
    m_TitleLabel->setAlignment(Qt::AlignCenter);
    m_LanguagesLabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
	m_ChangeLangComboBox->setStyleSheet("background-color: black; color: red; font: italic 12pt \"Cambria\" ");
	m_WLabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
	m_DLabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
	m_SLabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
	m_ALabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
	m_PLabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
	m_SpaceLabel->setStyleSheet("font: italic 12pt \"Cambria\" ");
    m_BackButton->setCursor(Qt::PointingHandCursor);
}

void Options::goBack()
{
    emit backtomenuClicked();
}
