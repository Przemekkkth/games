#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>

class QLabel;
class QDialogButtonBox;
class QLineEdit;
class QPushButton;

class ConfigurationDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QString player1Name READ player1Name WRITE setPlayer1Name)
    Q_PROPERTY(QString player2Name READ player2Name WRITE setPlayer2Name)
public:
    explicit ConfigurationDialog(QWidget *parent = 0);
    ~ConfigurationDialog();
    void setPlayer1Name(const QString& p1name);
    void setPlayer2Name(const QString &p2name);
    QString player1Name() const;
    QString player2Name() const;

public slots:
    void updateOKButtonState();

private:
	QLineEdit *m_player1NameEdit;
	QLineEdit *m_player2NameEdit;
	QLabel *m_player1Label;
	QLabel *m_player2Label;
	QPushButton *m_AcceptButton;
	
	
	void createWidgets();
	void createLayouts();
	void createConnections();
	void translateUi();
};

#endif // CONFIGURATIONDIALOG_H
