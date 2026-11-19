/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "SmokeSensorAdapter.h"
#include <stdexcept>

// Luu tham chieu den doi tuong cu; moi lan doc se lay gia tri moi nhat.
SmokeSensorAdapter::SmokeSensorAdapter(LegacySmokeDetector& detector)
    : legacy(&detector) {}

double SmokeSensorAdapter::ReadValue() const {
    return legacy->GetSmokeLevel() / 10.0;
}

const char* SmokeSensorAdapter::GetUnit() const {
    return "% smoke";
}
