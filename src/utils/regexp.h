#ifndef REGEXP_H
#define REGEXP_H

#include <QObject> // Needed for QT_VERSION

#if (QT_VERSION < 0x050000)
// Qt 4 - use QRegExp directly
#include <QRegExp>
#define RegExp QRegExp
#else // Qt 5
#include <QRegularExpression>
#include <QStringList>

#include "utilsexport.h"

class UTILS_EXPORT RegExp : public QRegularExpression
{
public:
    RegExp();
    RegExp(const QString &pattern, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    RegExp(const RegExp &re);

    void setMinimal(bool minimal);
    int indexIn(const QString &str, int offset = 0) const;
    int matchedLength() const;
    QString cap(int nth = 0) const;

private:
    QStringList m_capturedTexts;
    int m_matchedLength;

};
#endif // Qt 5

#endif

