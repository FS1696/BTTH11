/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "EmergencyMediator.h"

EmergencyMediator::EmergencyMediator(AlarmController& alarmController,
                                     DoorController& doorController,
                                     VentilationController& ventilationController)
    : alarm(alarmController), door(doorController), ventilation(ventilationController) {}

void EmergencyMediator::HandleEmergency(const AlertEvent& alertEvent) {
    // Chinh sach mo phong cua bai: WARNING bat coi; CRITICAL bat coi, mo cua va hut khi.
    alarm.Activate(alertEvent.GetSeverity());
    if (alertEvent.GetSeverity() == AlertSeverity::CRITICAL) {
        door.UnlockEmergencyExit();
        ventilation.StartEmergencyExhaust();
    }
}
