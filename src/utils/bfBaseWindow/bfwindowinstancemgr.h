#ifndef BFWINDOWINSTANCEMGR_H
#define BFWINDOWINSTANCEMGR_H

#include <QObject>

class BfWindowInstanceMgr
{
public:
    static void SetMainWindow(QObject* p);

private:
    QObject* m_pMainWindow = nullptr;
};

#endif // BFWINDOWINSTANCEMGR_H
