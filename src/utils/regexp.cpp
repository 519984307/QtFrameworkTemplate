#include "regexp.h"

#if (QT_VERSION >= 0x050000)
RegExp::RegExp()
    : QRegularExpression(QString(), QRegularExpression::DotMatchesEverythingOption)
    , m_matchedLength(-1)
{
}

RegExp::RegExp(const QString &pattern, Qt::CaseSensitivity cs)
    : QRegularExpression(pattern, QRegularExpression::DotMatchesEverythingOption)
    , m_matchedLength(-1)
{
    if (cs == Qt::CaseInsensitive) {
        setPatternOptions(patternOptions() | QRegularExpression::CaseInsensitiveOption);
    }
}

RegExp::RegExp(const RegExp &re)
    : QRegularExpression(re)
    , m_matchedLength(-1)
{
}

void RegExp::setMinimal(bool minimal)
{
    QRegularExpression::PatternOptions opt;

    if (minimal) {
        opt = patternOptions() | QRegularExpression::InvertedGreedinessOption;
    }
    else {
        opt = patternOptions() & ~QRegularExpression::InvertedGreedinessOption;
    }

    setPatternOptions(opt);
}

int RegExp::indexIn(const QString &str, int offset) const
{
    RegExp* that = const_cast<RegExp*>(this);
    QRegularExpressionMatch m = match(str, offset);

    if (!m.hasMatch()) {
        that->m_matchedLength = -1;
        that->m_capturedTexts.clear();
        return -1;
    }

    that->m_matchedLength = m.capturedLength();
    that->m_capturedTexts = m.capturedTexts();
    return m.capturedStart();
}

int RegExp::matchedLength() const
{
    return m_matchedLength;
}

QString RegExp::cap(int nth) const
{
    if (nth < 0 || nth >= m_capturedTexts.count()) {
        return QString();
    }

    return m_capturedTexts.at(nth);
}
#endif // (QT_VERSION >= 0x050000)

