#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include "utilsexport.h"
#include "skinmanager.h"

namespace Ui {
class InputDialog;
}

class UTILS_EXPORT InputDialog : public QDialog, public ISkinWidget
{
    Q_OBJECT
    Q_INTERFACES(ISkinWidget)
    
public:
    explicit InputDialog(const QString &themePath, const QString initStr = "",  QWidget *parent = 0);
    ~InputDialog();

    void setTitle(const QString& title);
    void setTip(const QString& tip);
	void setPlaceholderText(const QString& placeholderText);
    void setMaxInputUtf8Length(int len);
    void setMaxInputLength(int len);
    void setLineEditText(const QString &text);

    QString result();
	void setCanEmpty(bool b);

    //ISkinWidget
    virtual QDialog *instance() {return this;}
    virtual bool isResizable() const;
    virtual int resizeBorderWidth() const;
    virtual bool isMaximized() const;
    virtual void setMaximized(const bool bMaximized);
    virtual QRect restoreRect() const;
    virtual void setRestoreRect(const QRect restoreRect);
    virtual SkinWidgetData skinData() const {return m_skinData;}
    virtual void initSkinData();


    //ISkinWidget
signals:
   void widgetDestroyed();
   void maximizeButtonClicked();
   void minimizeButtonClicked();

public slots:
    //virtual void onSkinChanged();

private slots:
	void onTextChanged(const QString &text);
    
private:
    Ui::InputDialog *ui;
	bool m_canEmpty;
    QString m_themePath;
    int m_maxUtf8Length;

    //ISkinWidget
 private:
    SkinWidgetData m_skinData;
    QRect m_restoreRect;
    bool m_bMaximized;
};

#endif // INPUTDIALOG_H
