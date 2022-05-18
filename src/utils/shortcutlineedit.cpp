#include "shortcutlineedit.h"

#include <QKeyEvent>

ShortcutLineEdit::ShortcutLineEdit(QWidget *parent) :
    FilterLineEdit(parent),
    m_keyNum(0)
{
    m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;

    connect(this, SIGNAL(buttonClicked(FancyLineEdit::Side)), SLOT(clearKeySequence()));
	setPlaceholderText(QString());
}

QKeySequence ShortcutLineEdit::keySequence() const
{
    return QKeySequence(text());
}

void ShortcutLineEdit::setKeySequence(const QKeySequence &key)
{
    m_keyNum = m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    m_keyNum = key.count();
    for (int i = 0; i < m_keyNum; ++i) {
        m_key[i] = key[i];
    }

    setText(key.toString());
}

void ShortcutLineEdit::clearKeySequence()
{
    m_keyNum = m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    m_keyNum = 0;
    FilterLineEdit::clear();
}

bool ShortcutLineEdit::event(QEvent *e)
{
    if ( e->type() == QEvent::Shortcut || e->type() == QEvent::KeyRelease ) {
        if(e->type() == QEvent::KeyRelease)
        {
            static int keyNum = 0;
            keyNum++;
            if(keyNum >= m_keyNum)
            {
                m_keyNum = 0;
                keyNum = 0;
            }
        }
        return true;
    }

    if (e->type() == QEvent::ShortcutOverride) {
        // for shortcut overrides, we need to accept as well
        e->accept();
        return true;
    }

    return QLineEdit::event(e);
}

void ShortcutLineEdit::keyPressEvent(QKeyEvent *e)
{
    int nextKey = e->key();
    if ( m_keyNum > 3 ||
         nextKey == Qt::Key_Control ||
         nextKey == Qt::Key_Shift ||
         nextKey == Qt::Key_Meta ||
         nextKey == Qt::Key_Alt )
         return;
    else if(m_keyNum >= m_maxKeyNum)
        return;

    nextKey |= translateModifiers(e->modifiers(), e->text());
    switch (m_keyNum) {
        case 0:
            m_key[0] = nextKey;
            break;
        case 1:
            m_key[1] = nextKey;
            break;
        case 2:
            m_key[2] = nextKey;
            break;
        case 3:
            m_key[3] = nextKey;
            break;
        default:
            break;
    }
    m_keyNum++;
    QKeySequence ks(m_key[0], m_key[1], m_key[2], m_key[3]);
    setText(ks.toString());
    e->accept();
}

int ShortcutLineEdit::translateModifiers(Qt::KeyboardModifiers state, const QString &text)
{
    int result = 0;
    // The shift modifier only counts when it is not used to type a symbol
    // that is only reachable using the shift key anyway
    if ((state & Qt::ShiftModifier) && (text.size() == 0
                                        || !text.at(0).isPrint()
                                        || text.at(0).isLetterOrNumber()
                                        || text.at(0).isSpace()))
        result |= Qt::SHIFT;
    if (state & Qt::ControlModifier)
        result |= Qt::CTRL;
    if (state & Qt::MetaModifier)
        result |= Qt::META;
    if (state & Qt::AltModifier)
        result |= Qt::ALT;
    return result;
}

void ShortcutLineEdit::setMaxKeyNum(int maxKeyNum)
{
    if(maxKeyNum <= 0)
        m_maxKeyNum = 1;
    else if(maxKeyNum > 4)
        m_maxKeyNum = 4;
    else
        m_maxKeyNum = maxKeyNum;
}
