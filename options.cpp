#include "options.h"
#include "ui_options.h"
#include <QMessageBox>
#include <QEvent>
#include <QDebug>

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    ui->m_OptionsTitle->setStyleSheet("font-size: 20px;");
    createConnections();
}

Options::~Options()
{
    delete ui;
}


void Options::clickBackToMenu()
{
    emit backtomenuClicked();
}

void Options::changeEvent(QEvent *e)
{
 /*   if(ui->choiceComboBox->currentIndex() == 0)
    {
        qDebug() << "Test" ;
    }*/
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
    connect(ui->m_BackToMenuButton, SIGNAL(clicked(bool)), this, SLOT(clickBackToMenu()));
}

void Options::translateUi()
{
    int choice = ui->choiceComboBox->currentIndex();
    setCurrentLanguage(choice);
}

void Options::setCurrentLanguage(int choice)
{
    switch (choice) {
    case 1:
        QMessageBox::information(0,"Test", "Polski");
        break;
    case 2:
        QMessageBox::information(0,"Test", "Polski");
        break;
    default:
        break;
    }
}
