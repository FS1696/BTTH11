/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "Observers.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

void DashboardObserver::Update(const AlertEvent& alertEvent) {
    std::cout << "[DASHBOARD] " << alertEvent.GetSensorName() << ": "
              << std::fixed << std::setprecision(1) << alertEvent.GetValue()
              << alertEvent.GetUnit() << " [" << SeverityToString(alertEvent.GetSeverity())
              << "]" << std::endl;
}

void EmailAlertObserver::Update(const AlertEvent& alertEvent) {
    std::cout << "[EMAIL SIMULATED] Alert for " << alertEvent.GetSensorName()
              << " - " << SeverityToString(alertEvent.GetSeverity()) << std::endl;
}

void AuditLogObserver::Update(const AlertEvent& alertEvent) {
    std::ostringstream line;
    line << alertEvent.GetSensorName() << " | "
         << std::fixed << std::setprecision(1) << alertEvent.GetValue()
         << alertEvent.GetUnit() << " | " << SeverityToString(alertEvent.GetSeverity())
         << " | timestamp=" << static_cast<long long>(alertEvent.GetOccurredAt());
    entries.push_back(line.str());
}

const std::vector<std::string>& AuditLogObserver::Entries() const {
    return entries;
}

EmergencyBridgeObserver::EmergencyBridgeObserver(IEmergencyMediator& emergencyMediator)
    : mediator(emergencyMediator) {}

void EmergencyBridgeObserver::Update(const AlertEvent& alertEvent) {
    mediator.HandleEmergency(alertEvent);
}
