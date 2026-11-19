/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef ALERT_EVENT_H
#define ALERT_EVENT_H

#include <ctime>
#include <string>

enum class AlertSeverity {
    WARNING,
    CRITICAL
};

// AlertEvent chi cung cap getter const, khong co ham thay doi du lieu.
class AlertEvent {
private:
    const std::string sensorName;
    const double value;
    const std::string unit;
    const AlertSeverity severity;
    const std::time_t occurredAt;

public:
    AlertEvent(const std::string& name, double reading,
               const std::string& measurementUnit, AlertSeverity level,
               std::time_t time = std::time(NULL));

    const std::string& GetSensorName() const;
    double GetValue() const;
    const std::string& GetUnit() const;
    AlertSeverity GetSeverity() const;
    std::time_t GetOccurredAt() const;
};

const char* SeverityToString(AlertSeverity severity);

#endif
