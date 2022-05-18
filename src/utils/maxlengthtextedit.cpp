#include "maxlengthtextedit.h"

MaxLengthTextEdit::MaxLengthTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    m_maxLength = 3000;
    connect(this, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void MaxLengthTextEdit::setMaxLength(int maxLength)
{
    m_maxLength = maxLength;
}

void MaxLengthTextEdit::textChanged() {
    QString textContent = this->toPlainText();
    int length = textContent.count();
    if(length > m_maxLength) {
        int position = this->textCursor().position();
        QTextCursor textCursor = this->textCursor();
        textContent.remove(position-(length-m_maxLength), length-m_maxLength);
        this->setText(textContent);
        textCursor.setPosition(position-(length-m_maxLength));
        this->setTextCursor(textCursor);
    }
}
