#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
class QLabel;
class QPushButton;
class QComboBox;

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);
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
