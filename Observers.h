/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef OBSERVERS_H
#define OBSERVERS_H

#include <string>
#include <vector>
#include "IAlertObserver.h"
#include "IEmergencyMediator.h"

class DashboardObserver : public IAlertObserver {
public:
    void Update(const AlertEvent& alertEvent);
};

// Chi mo phong viec gui email, khong gui email that.
class EmailAlertObserver : public IAlertObserver {
public:
    void Update(const AlertEvent& alertEvent);
};

class AuditLogObserver : public IAlertObserver {
private:
    std::vector<std::string> entries;
public:
    void Update(const AlertEvent& alertEvent);
    const std::vector<std::string>& Entries() const;
};

// Bridge chuyen alert tu Observer sang hop dong Mediator.
class EmergencyBridgeObserver : public IAlertObserver {
private:
    IEmergencyMediator& mediator;
public:
    explicit EmergencyBridgeObserver(IEmergencyMediator& emergencyMediator);
    void Update(const AlertEvent& alertEvent);
};

#endif
