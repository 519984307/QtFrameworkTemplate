#ifndef IGLOBALSETTING_H
#define IGLOBALSETTING_H

#include <definitions/globalsetting.h>


#define GLOBALSETTING_UUID "{2a1c6ff4-9895-4b01-bc20-2115a16bab7b}"

class IGlobalSettingPlugin
{
public:
    virtual QObject *instance() = 0;
};

#define IGlobalSettingPlugin_iid   "Billfish.Plugin.IGlobalSettingPlugin/1.0"
Q_DECLARE_INTERFACE(IGlobalSettingPlugin,IGlobalSettingPlugin_iid)

#endif //IGLOBALSETTING_H
