/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef EMERGENCY_MEDIATOR_H
#define EMERGENCY_MEDIATOR_H

#include "IEmergencyMediator.h"
#include "EmergencyDevices.h"

// Mediator la dau moi duy nhat dieu phoi cac thiet bi ung pho.
class EmergencyMediator : public IEmergencyMediator {
private:
    AlarmController& alarm;
    DoorController& door;
    VentilationController& ventilation;

public:
    EmergencyMediator(AlarmController& alarmController,
                      DoorController& doorController,
                      VentilationController& ventilationController);
    void HandleEmergency(const AlertEvent& alertEvent);
};

#endif
