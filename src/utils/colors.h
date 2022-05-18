#ifndef COLORS_H
#define COLORS_H

class QWidget;
#include <QColor>
#include <QPalette>
#include "utilsexport.h"

// namespace Bespin {
namespace Colors
{

const QColor & UTILS_EXPORT bg(const QPalette &pal, const QWidget* w);
int UTILS_EXPORT contrast(const QColor &a, const QColor &b);
QPalette::ColorRole UTILS_EXPORT counterRole(QPalette::ColorRole role);
bool UTILS_EXPORT counterRole(QPalette::ColorRole &from, QPalette::ColorRole &to,
                 QPalette::ColorRole defFrom = QPalette::WindowText,
                 QPalette::ColorRole defTo = QPalette::Window);
QColor UTILS_EXPORT emphasize(const QColor &c, int value = 10);
bool UTILS_EXPORT haveContrast(const QColor &a, const QColor &b);
QColor UTILS_EXPORT light(const QColor &c, int value);
QColor UTILS_EXPORT mid(const QColor &oc1, const QColor &c2, int w1 = 1, int w2 = 1);
int UTILS_EXPORT value(const QColor &c);
QColor UTILS_EXPORT colorFromText(const QString& text);
int UTILS_EXPORT QColorToInt(const QColor& color);





}
// }

#endif //COLORS_H
