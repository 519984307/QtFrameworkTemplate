#ifndef BUTTONWITHMENU_H
#define BUTTONWITHMENU_H

#include "toolbutton.h"
#include "utilsexport.h"

class UTILS_EXPORT ButtonWithMenu : public ToolButton
{
    Q_OBJECT
public:
    struct Item {
        QString text;
        QIcon icon;
        QVariant userData;

        Item(const QString &a = QString(), const QIcon &b = QIcon()) {
            text = a;
            icon = b;
        }

        bool operator==(const Item &a) {
            return (a.text == text) && (a.icon.pixmap(16, 16).toImage() == icon.pixmap(16, 16).toImage());
        }

        bool isEmpty() {
            return (text.isEmpty() &&  icon.isNull());
        }

        void clear() {
            text = QString();
            icon = QIcon();
            userData = QVariant();
        }
    };

    explicit ButtonWithMenu(QWidget* parent = 0);
    ~ButtonWithMenu();

    void addItem(const Item &item);
    void addItems(const QVector<Item> &items);
    void removeItem(const Item &item);
    void setCurrentItem(const Item &item, bool emitSignal = true);

    Item currentItem();
    QVector<Item> allItems() { return m_items; }
    QMenu* menu() const;

signals:
    void activeItemChanged(const ButtonWithMenu::Item &item);
    void itemAdded(const ButtonWithMenu::Item &item);
    void itemRemoved(const ButtonWithMenu::Item &item);

public slots:
    void clearItems();

private slots:
    void setCurrentItem();
    void generateMenu();

private:
    void wheelEvent(QWheelEvent* event);

    QMenu* m_menu;
    QVector<Item> m_items;
    Item m_currentItem;
};

// Hint to QVector to use std::realloc on item moving
Q_DECLARE_TYPEINFO(ButtonWithMenu::Item, Q_MOVABLE_TYPE);

Q_DECLARE_METATYPE(ButtonWithMenu::Item)

#endif // BUTTONWITHMENU_H
