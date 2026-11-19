/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef I_ALERT_OBSERVER_H
#define I_ALERT_OBSERVER_H

#include "AlertEvent.h"

// Observer chi nhan su kien; doi tuong AlertEvent duoc truyen read-only.
class IAlertObserver {
public:
    virtual ~IAlertObserver() {}
    virtual void Update(const AlertEvent& alertEvent) = 0;
};

#endif
