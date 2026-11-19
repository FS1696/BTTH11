/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#ifndef ISENSOR_H
#define ISENSOR_H

// Giao dien chuan de module giam sat doc cac loai cam bien.
class ISensor {
public:
    virtual ~ISensor() {}
    virtual double ReadValue() const = 0;
    virtual const char* GetUnit() const = 0;
};

#endif
