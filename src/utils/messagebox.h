#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "utilsexport.h"
#include <QDialogButtonBox>
#include "skinmanager.h"
#include <QDialog>

namespace Ui {
class MessageBox;
}

class UTILS_EXPORT WidgetMessageBox : public QDialog, public ISkinWidget
{
    Q_OBJECT
    Q_INTERFACES(ISkinWidget)
    
public:
    enum Type{
        Success,
        Failed,
        Question,
        Information,
		Warning
   };

    explicit WidgetMessageBox(Type type, const QString& tip, QDialogButtonBox::StandardButtons btns, const QString &themePath,
                              const QString& title = tr("Warm tips"), QWidget *parent = 0);
    ~WidgetMessageBox();
    QDialogButtonBox::ButtonRole clickedButtonRole(){return m_clickedRole;}

    void setButtonText(QDialogButtonBox::StandardButton which, const QString& text);

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

protected slots:
    void buttonClicked(QAbstractButton * button);

protected:
    void initTheme();
    
private:
    Ui::MessageBox *ui;
    QDialogButtonBox::ButtonRole m_clickedRole;

    //ISkinWidget
 private:
    SkinWidgetData m_skinData;
    QRect m_restoreRect;
    bool m_bMaximized;

private:
    QString m_themePath;
    Type m_type;
};

#endif // MESSAGEBOX_H
