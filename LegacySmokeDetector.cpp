/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "LegacySmokeDetector.h"

// Dam bao du lieu noi bo cua cam bien cu nam trong khoang 0..1000.
LegacySmokeDetector::LegacySmokeDetector(int initialLevel)
    : smokeLevel(initialLevel < 0 ? 0 : (initialLevel > 1000 ? 1000 : initialLevel)) {}

int LegacySmokeDetector::GetSmokeLevel() const {
    return smokeLevel;
}

const char* LegacySmokeDetector::GetDescription() const {
    return "Legacy smoke detector";
}

void LegacySmokeDetector::SetSmokeLevel(int value) {
    if (value < 0) value = 0;
    if (value > 1000) value = 1000;
    smokeLevel = value;
}
