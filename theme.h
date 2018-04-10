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
protected:
    void changeEvent(QEvent*);
private:
    QPushButton *m_startButton;
    QPushButton *m_optionsButton;
    QPushButton *m_quitButton;

    void createConnections();
    void createWidgets();
    void createLayout();
    void createStyleSheet();
    void translateUi();
};

#endif // THEME_H
