#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include <QLineEdit>
#include "utilsexport.h"
class UTILS_EXPORT CLineEdited : public QLineEdit {
    Q_OBJECT
public:
    explicit CLineEdited(QWidget *parent = 0);
    ~CLineEdited();

protected:
	void focusInEvent(QFocusEvent* event);
	bool eventFilter(QObject* obj, QEvent* event);
	void paintEvent(QPaintEvent *);

signals:
	void signFocusIn();

public slots:
};

#endif // CBASEWIDGET_H
