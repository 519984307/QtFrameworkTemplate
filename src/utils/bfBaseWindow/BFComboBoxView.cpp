#include "BFComboBoxView.h"
#include <QPainter>
#include "bfskinmodule/bfskinsetting.h"
#include "../bfqtutils.h"
//BFComboBoxViewDelegate::BFComboBoxViewDelegate(QWidget* parent)
//    : QStyledItemDelegate(parent) {}
//
//BFComboBoxViewDelegate::~BFComboBoxViewDelegate() {}
//
//void BFComboBoxViewDelegate::paint(QPainter* painter,
//                                   const QStyleOptionViewItem& option,
//                                   const QModelIndex& index) const {
//  if (index.data().canConvert<QString>()) {
//    QFont font_yahei_13;
//    font_yahei_13.setFamily("Microsoft YaHei");
//    font_yahei_13.setPixelSize(13);
//
//    QString str = index.data().toString();
//
//    QRect r = option.rect;
//    painter->setFont(font_yahei_13);
//    painter->setPen(BFSkinSetting::GetInstance()->GetTextColor(0));
//
//    str = BfQtUtils::FontAdjustWidth(font_yahei_13, option.rect.width() - 30,
//                                     str);
//    painter->drawText(QPoint(20, r.y() + 33), str);
//  }
//}
//
//QSize BFComboBoxViewDelegate::sizeHint(const QStyleOptionViewItem& option,
//                                       const QModelIndex& index) const {
//  QSize size(135, 33);
//
//  //如果是最后一行，高度要多显示20
//  int itemCount = -1;
//  QListView* _listView = dynamic_cast<QListView*>(this->parent());
//  if (_listView) {
//    int i1 = (_listView->model()->rowCount() - 1);
//    int i2 = index.row();
//    if ((_listView->model()->rowCount() - 1) == index.row()) {
//      size = QSize(135, 53);
//    }
//  }
//
//  return size;
//}