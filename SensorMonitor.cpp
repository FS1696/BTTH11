/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include "SensorMonitor.h"
#include <iostream>
#include <stdexcept>

void SensorMonitor::Attach(const std::shared_ptr<IAlertObserver>& observer) {
    if (!observer) {
        throw std::invalid_argument("Observer khong duoc null.");
    }
    // Khong them trung cung mot doi tuong observer.
    for (std::size_t i = 0; i < observers.size(); ++i) {
        if (observers[i].get() == observer.get()) return;
    }
    observers.push_back(observer);
}

void SensorMonitor::Detach(const IAlertObserver* observer) {
    for (std::vector<std::shared_ptr<IAlertObserver> >::iterator it = observers.begin();
         it != observers.end(); ++it) {
        if (it->get() == observer) {
            observers.erase(it);
            return;
        }
    }
}
