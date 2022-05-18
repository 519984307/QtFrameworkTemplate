#ifndef MAXLENGTHTEXTEDIT_H
#define MAXLENGTHTEXTEDIT_H

#include <QTextEdit>
#include "utilsexport.h"

class MaxLengthTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit UTILS_EXPORT MaxLengthTextEdit(QWidget *parent = 0);
    void setMaxLength(int maxLength);

signals:

public slots:

private slots:
    void textChanged();

private:
    int m_maxLength;

};

#endif // MAXLENGTHTEXTEDIT_H
