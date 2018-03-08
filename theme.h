#ifndef THEME_H
#define THEME_H

#include <QWidget>
class QPushButton;

class Theme : public QWidget
{
    Q_OBJECT
public:
    explicit Theme(QWidget *parent = 0);

signals:
    void startClicked();
    void optionsClicked();
    void quitClicked();

private slots:
    void gameStarted();
    void optionsStarted();
    void quitStarted();
private:
    QPushButton *m_startButton;
    QPushButton *m_optionsButton;
    QPushButton *m_quitButton;

    void createConnections();
    void createWidgets();
    void createLayout();
    void createStyleSheet();
};

#endif // THEME_H
