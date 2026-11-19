/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef EMERGENCY_DEVICES_H
#define EMERGENCY_DEVICES_H

#include "AlertEvent.h"

// Cac thiet bi ung pho doc lap, khong biet den nhau.
class AlarmController {
private:
    bool active;
public:
    AlarmController();
    void Activate(AlertSeverity severity);
    bool IsActive() const;
};

class DoorController {
private:
    bool locked;
public:
    DoorController();
    void UnlockEmergencyExit();
    bool IsLocked() const;
};

class VentilationController {
private:
    bool running;
public:
    VentilationController();
    void StartEmergencyExhaust();
    bool IsRunning() const;
};

#endif
