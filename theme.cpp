#include "theme.h"
#include "globalsettings.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>

Theme::Theme(QWidget *parent) : QWidget(parent)
{

    createWidgets();
    createLayout();
    createConnections();
    createStyleSheet();
    translateUi();
}

void Theme::createConnections()
{
    connect(m_startButton, &QPushButton::clicked, [this]
    {
            emit startClicked();
    });

    connect(m_optionsButton, &QPushButton::clicked, [this]
    {
        emit optionsClicked();
    });

    connect(m_quitButton, &QPushButton::clicked, [this]
    {
        qApp->quit();
    });

}

void Theme::createWidgets()
{
    m_startButton = new QPushButton;
    m_startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_startButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_startButton->setDefault(false);
    m_startButton->setAutoDefault(false);

    m_optionsButton = new QPushButton;
    m_optionsButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_optionsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_optionsButton->setDefault(false);
    m_optionsButton->setAutoDefault(false);

    m_quitButton = new QPushButton;
    m_quitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_quitButton->setCursor(QCursor(Qt::PointingHandCursor));
}

void Theme::createLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_startButton);
    mainLayout->addWidget(m_optionsButton);
    mainLayout->addWidget(m_quitButton);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

void Theme::createStyleSheet()
{
    setStyleSheet("QWidget{background-color: black;}"
                  "QPushButton{background-color: #13100a; border-style: solid;  border-width: 1px; border-radius: 10px; color: white; font-size: 20px; font-family: \'Arial\'; font-weight: 500px;}"
                  "QPushButton:hover{background-color: #24211b;}");
    setMinimumSize(QSize(WIDTH, HEIGHT));
}

void Theme::translateUi()
{
    m_startButton->setText(tr("Strart"));
    m_optionsButton->setText(tr("Options"));
    m_quitButton->setText(tr("Quit"));
}
