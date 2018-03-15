#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);
    //nizej nalezy posortowac
private:
	void createWidgets();
	void createLayout();
	void createConnections();
	void createStyleSheet();
	void translateUi();
	QLabel *m_TitleLabel, *m_LanguagesLabel, *m_WLabel, *m_DLabel,
			*m_SLabel, *m_ALabel, *m_PLabel, *m_SpaceLabel;
	QPushButton *m_BackButton;
	QComboBox *m_ChangeLangComboBox;
protected:
    void changeEvent(QEvent*);
private slots:
	void setCurrentLanguage(int);
    void goBack();
signals:
    void backtomenuClicked();

};

#endif // THEME_H
