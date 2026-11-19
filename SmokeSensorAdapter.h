/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef SMOKE_SENSOR_ADAPTER_H
#define SMOKE_SENSOR_ADAPTER_H

#include "ISensor.h"
#include "LegacySmokeDetector.h"

// Adapter chuyen giao dien/thang do cu sang ISensor va khong sao chep trang thai.
class SmokeSensorAdapter : public ISensor {
private:
    LegacySmokeDetector* legacy;

public:
    explicit SmokeSensorAdapter(LegacySmokeDetector& detector);
    double ReadValue() const;
    const char* GetUnit() const;
};

#endif
