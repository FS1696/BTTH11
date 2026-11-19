/****************/
// Ma sinh vien: <DIEN MA SINH VIEN>
// Ho ten: <DIEN HO TEN>
/****************/
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "LegacySmokeDetector.h"
#include "SmokeSensorAdapter.h"
#include "SensorMonitor.h"
#include "Observers.h"
#include "EmergencyDevices.h"
#include "EmergencyMediator.h"

// Observer nho dung rieng cho kiem thu, luu so lan nhan va muc do cuoi.
class RecordingObserver : public IAlertObserver {
public:
    int count;
    AlertSeverity lastSeverity;
    RecordingObserver() : count(0), lastSeverity(AlertSeverity::WARNING) {}
    void Update(const AlertEvent& event) {
        ++count;
        lastSeverity = event.GetSeverity();
    }
};

class ThrowingObserver : public IAlertObserver {
public:
    void Update(const AlertEvent&) { throw std::runtime_error("Test observer exception"); }
};

class SelfDetachingObserver : public IAlertObserver {
private:
    SensorMonitor& monitor;
public:
    int count;
    explicit SelfDetachingObserver(SensorMonitor& m) : monitor(m), count(0) {}
    void Update(const AlertEvent&) {
        ++count;
        monitor.Detach(this);
    }
};

int main() {
    int passed = 0;
    int failed = 0;

    // Ham chay tung test case va thong ke PASS/FAIL.
    const auto runTest = [&passed, &failed](const std::string& name, bool result) {
        if (result) {
            ++passed;
            std::cout << "[PASS] " << name << std::endl;
        } else {
            ++failed;
            std::cout << "[FAIL] " << name << std::endl;
        }
    };

    // T1: Adapter doi thang do 735/10 = 73.5 va don vi % smoke.
    {
        LegacySmokeDetector legacy(735);
        SmokeSensorAdapter adapter(legacy);
        runTest("T1 - Adapter converts 735 to 73.5 % smoke",
                adapter.ReadValue() == 73.5 && std::string(adapter.GetUnit()) == "% smoke");
    }

    // T2: Adapter doc truc tiep trang thai moi nhat tu doi tuong cu.
    {
        LegacySmokeDetector legacy(735);
        SmokeSensorAdapter adapter(legacy);
        legacy.SetSmokeLevel(600);
        runTest("T2 - Adapter reads updated legacy state without copying",
                adapter.ReadValue() == 60.0);
    }

    // T3: Legacy detector gioi han du lieu trong khoang 0..1000.
    {
        LegacySmokeDetector legacy(1500);
        bool upper = legacy.GetSmokeLevel() == 1000;
        legacy.SetSmokeLevel(-10);
        runTest("T3 - Legacy detector clamps values to 0..1000",
                upper && legacy.GetSmokeLevel() == 0);
    }

    // T4: Gia tri duoi 50% khong phat canh bao.
    {
        LegacySmokeDetector legacy(499);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<RecordingObserver> observer(new RecordingObserver());
        monitor.Attach(observer);
        bool notified = monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T4 - Value below 50% produces no alert", !notified && observer->count == 0);
    }

    // T5: Muc 50% bat dau WARNING va observer nhan du lieu dung.
    {
        LegacySmokeDetector legacy(500);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<RecordingObserver> observer(new RecordingObserver());
        monitor.Attach(observer);
        monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T5 - 50% boundary creates WARNING", observer->count == 1 &&
                observer->lastSeverity == AlertSeverity::WARNING);
    }

    // T6: Muc 70% bat dau CRITICAL.
    {
        LegacySmokeDetector legacy(700);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<RecordingObserver> observer(new RecordingObserver());
        monitor.Attach(observer);
        monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T6 - 70% boundary creates CRITICAL", observer->count == 1 &&
                observer->lastSeverity == AlertSeverity::CRITICAL);
    }

    // T7: Cung mot observer khong bi dang ky trung.
    {
        LegacySmokeDetector legacy(550);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<RecordingObserver> observer(new RecordingObserver());
        monitor.Attach(observer);
        monitor.Attach(observer);
        monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T7 - Duplicate observer registration is ignored",
                monitor.ObserverCount() == 1 && observer->count == 1);
    }

    // T8: Observer da Detach khong nhan canh bao sau do.
    {
        LegacySmokeDetector legacy(550);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<RecordingObserver> observer(new RecordingObserver());
        monitor.Attach(observer);
        monitor.Detach(observer.get());
        monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T8 - Detached observer receives no alert", observer->count == 0);
    }

    // T9: Duyet ban sao cho phep observer tu go bo minh khi dang nhan tin.
    {
        LegacySmokeDetector legacy(550);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<SelfDetachingObserver> self(new SelfDetachingObserver(monitor));
        std::shared_ptr<RecordingObserver> later(new RecordingObserver());
        monitor.Attach(self);
        monitor.Attach(later);
        monitor.CheckSensor("Smoke sensor", adapter);
        bool firstPass = self->count == 1 && later->count == 1 && monitor.ObserverCount() == 1;
        monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T9 - Observer can detach itself during notification",
                firstPass && self->count == 1 && later->count == 2);
    }

    // T10: Observer loi khong ngan can cac observer tiep theo.
    {
        LegacySmokeDetector legacy(550);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<ThrowingObserver> bad(new ThrowingObserver());
        std::shared_ptr<RecordingObserver> good(new RecordingObserver());
        monitor.Attach(bad);
        monitor.Attach(good);
        monitor.CheckSensor("Smoke sensor", adapter);
        runTest("T10 - One failing observer does not block later observers",
                good->count == 1);
    }

    // T11: WARNING chi kich hoat coi, khong mo cua/khong bat hut khi theo chinh sach mo phong.
    {
        AlarmController alarm;
        DoorController door;
        VentilationController ventilation;
        EmergencyMediator mediator(alarm, door, ventilation);
        AlertEvent warning("Smoke sensor", 55.0, "% smoke", AlertSeverity::WARNING);
        mediator.HandleEmergency(warning);
        runTest("T11 - WARNING activates alarm only",
                alarm.IsActive() && door.IsLocked() && !ventilation.IsRunning());
    }

    // T12: CRITICAL kich hoat day du cac thiet bi ung pho.
    {
        AlarmController alarm;
        DoorController door;
        VentilationController ventilation;
        EmergencyMediator mediator(alarm, door, ventilation);
        AlertEvent critical("Smoke sensor", 75.0, "% smoke", AlertSeverity::CRITICAL);
        mediator.HandleEmergency(critical);
        runTest("T12 - CRITICAL activates alarm, unlocks exit and starts exhaust",
                alarm.IsActive() && !door.IsLocked() && ventilation.IsRunning());
    }

    // T13: EmergencyBridgeObserver chuyen canh bao toi Mediator.
    {
        AlarmController alarm;
        DoorController door;
        VentilationController ventilation;
        EmergencyMediator mediator(alarm, door, ventilation);
        EmergencyBridgeObserver bridge(mediator);
        AlertEvent critical("Smoke sensor", 80.0, "% smoke", AlertSeverity::CRITICAL);
        bridge.Update(critical);
        runTest("T13 - Emergency bridge forwards alert to mediator",
                alarm.IsActive() && !door.IsLocked() && ventilation.IsRunning());
    }

    // T14: Audit observer luu lai lich su canh bao.
    {
        LegacySmokeDetector legacy(550);
        SmokeSensorAdapter adapter(legacy);
        SensorMonitor monitor;
        std::shared_ptr<AuditLogObserver> audit(new AuditLogObserver());
        monitor.Attach(audit);
        monitor.CheckSensor("Room 204 smoke", adapter);
        bool ok = audit->Entries().size() == 1 &&
                  audit->Entries()[0].find("WARNING") != std::string::npos;
        runTest("T14 - Audit observer records alert history", ok);
    }

    std::cout << "\n===== TEST SUMMARY =====" << std::endl;
    std::cout << "PASS: " << passed << std::endl;
    std::cout << "FAIL: " << failed << std::endl;
    std::cout << "TOTAL: " << (passed + failed) << std::endl;

    // Demo luong day du: adapter -> monitor -> observer -> mediator -> thiet bi ung pho.
    std::cout << "\n===== CAMPUS SAFETY HUB DEMO =====" << std::endl;
    LegacySmokeDetector legacy(735);
    SmokeSensorAdapter smokeSensor(legacy);
    AlarmController alarm;
    DoorController door;
    VentilationController ventilation;
    EmergencyMediator mediator(alarm, door, ventilation);
    SensorMonitor monitor;
    monitor.Attach(std::shared_ptr<IAlertObserver>(new DashboardObserver()));
    monitor.Attach(std::shared_ptr<IAlertObserver>(new EmailAlertObserver()));
    monitor.Attach(std::shared_ptr<IAlertObserver>(new AuditLogObserver()));
    monitor.Attach(std::shared_ptr<IAlertObserver>(new EmergencyBridgeObserver(mediator)));
    monitor.CheckSensor("Computer Lab Smoke Detector", smokeSensor);

    return failed == 0 ? 0 : 1;
}
