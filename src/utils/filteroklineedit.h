#ifndef FILTEROKLINEEDIT_H
#define FILTEROKLINEEDIT_H

#include "utilsexport.h"

#include "fancylineedit.h"

class UTILS_EXPORT FilterOkLineEdit : public FancyLineEdit
{
	Q_OBJECT

public:
	explicit FilterOkLineEdit(QWidget *parent = 0);
	void setClearRightButton();
	void setOkRightButton();
    void setThemePath(const QString &path);

signals:
	void filterChanged(const QString &);

private slots:
	void slotTextChanged();

private:
	QString m_lastFilterText;
    QString m_themePath;
};

#endif // FILTEROKLINEEDIT_H
