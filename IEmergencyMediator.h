/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef I_EMERGENCY_MEDIATOR_H
#define I_EMERGENCY_MEDIATOR_H

#include "AlertEvent.h"

// Hop dong de observer cau noi khong phu thuoc lop mediator cu the.
class IEmergencyMediator {
public:
    virtual ~IEmergencyMediator() {}
    virtual void HandleEmergency(const AlertEvent& alertEvent) = 0;
};

#endif
