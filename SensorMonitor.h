/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef SENSOR_MONITOR_H
#define SENSOR_MONITOR_H

#include <memory>
#include <vector>
#include <string>
#include "ISensor.h"
#include "IAlertObserver.h"

// Subject quan ly danh sach observer va quyet dinh nguong canh bao.
class SensorMonitor {
private:
    std::vector<std::shared_ptr<IAlertObserver> > observers;
    void Notify(const AlertEvent& alertEvent) const;

public:
    void Attach(const std::shared_ptr<IAlertObserver>& observer);
    void Detach(const IAlertObserver* observer);
    bool CheckSensor(const std::string& sensorName, const ISensor& sensor) const;
    std::size_t ObserverCount() const;
};

#endif
