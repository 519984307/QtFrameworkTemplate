#pragma once
#include <QString>

class BFObserver {
 public:
  BFObserver(){};
  virtual ~BFObserver(){};
};

class BFShortcutObserver : public BFObserver {
 public:
  BFShortcutObserver() : m_scType(-1){};
  virtual ~BFShortcutObserver(){};

 public:
  //////////////////////////////////////////////////////////////////////////
  /// 设置快捷键观察者类型</summary>
  /// <param name="type">类型</param>
  void setType(int type) { m_scType = type; }

  //////////////////////////////////////////////////////////////////////////
  /// 获得快捷键观察者类型</summary>
  /// <returns>类型</returns>
  int getType() { return m_scType; }

  //////////////////////////////////////////////////////////////////////////
  /// 快捷键观察者更新快捷键</summary>
  /// <param name="type">快捷键类型</param>
  /// <param name="sc">快捷键值</param>
  virtual void updateObserver(int type, QString sc){};

 private:
  //快捷键类型
  int m_scType;
};
