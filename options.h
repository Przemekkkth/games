#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>


namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private:
    Ui::Options *ui;
    void createConnections();
    void setCurrentLanguage(int);
    void translateUi();
private slots:
    void clickBackToMenu();
signals:
    void backtomenuClicked();
protected:
    void changeEvent(QEvent*);
};

#endif // OPTIONS_H
