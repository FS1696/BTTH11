/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "EmergencyDevices.h"
#include <iostream>

AlarmController::AlarmController() : active(false) {}
void AlarmController::Activate(AlertSeverity severity) {
    active = true;
    std::cout << "[ALARM] Activated - " << SeverityToString(severity) << std::endl;
}
bool AlarmController::IsActive() const { return active; }

DoorController::DoorController() : locked(true) {}
void DoorController::UnlockEmergencyExit() {
    locked = false;
    std::cout << "[DOOR] Emergency exit UNLOCKED" << std::endl;
}
bool DoorController::IsLocked() const { return locked; }

VentilationController::VentilationController() : running(false) {}
void VentilationController::StartEmergencyExhaust() {
    running = true;
    std::cout << "[VENTILATION] Emergency exhaust STARTED" << std::endl;
}
bool VentilationController::IsRunning() const { return running; }
