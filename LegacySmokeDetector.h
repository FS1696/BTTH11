/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef LEGACY_SMOKE_DETECTOR_H
#define LEGACY_SMOKE_DETECTOR_H

// Lop cam bien cu: giu nguyen giao dien va thang do 0..1000.
class LegacySmokeDetector {
private:
    int smokeLevel;

public:
    explicit LegacySmokeDetector(int initialLevel);
    int GetSmokeLevel() const;
    const char* GetDescription() const;
    void SetSmokeLevel(int value);
};

#endif
