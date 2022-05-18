#ifndef FILTERLINEEDIT_H
#define FILTERLINEEDIT_H

#include "utilsexport.h"
#include "fancylineedit.h"
#



class UTILS_EXPORT FilterLineEdit : public FancyLineEdit
{
    Q_OBJECT

public:
    explicit FilterLineEdit(QWidget *parent = 0);
    void setThemePath(const QString &path);

signals:
    void filterChanged(const QString &);

private slots:
    void slotTextChanged();

private:
    QString m_lastFilterText;
    QString m_themePath;
};

#endif // FILTERLINEEDIT_H
