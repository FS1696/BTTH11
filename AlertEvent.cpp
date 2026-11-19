/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "AlertEvent.h"

AlertEvent::AlertEvent(const std::string& name, double reading,
                       const std::string& measurementUnit, AlertSeverity level,
                       std::time_t time)
    : sensorName(name), value(reading), unit(measurementUnit),
      severity(level), occurredAt(time) {}

const std::string& AlertEvent::GetSensorName() const { return sensorName; }
double AlertEvent::GetValue() const { return value; }
const std::string& AlertEvent::GetUnit() const { return unit; }
AlertSeverity AlertEvent::GetSeverity() const { return severity; }
std::time_t AlertEvent::GetOccurredAt() const { return occurredAt; }

const char* SeverityToString(AlertSeverity severity) {
    return severity == AlertSeverity::CRITICAL ? "CRITICAL" : "WARNING";
}
