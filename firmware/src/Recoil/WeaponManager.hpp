#pragma once
#include <ArduinoBLE.h>
#define RECOIL_DYNAMIC_NAME

#ifndef RECOIL_NAME
#ifndef RECOIL_DYNAMIC_NAME
#error "Could not determine weapon UUID and RECOIL_DYNAMIC_UUID was not defined"
#endif
#endif
enum GunModel {
    Rifle=1,
    Pistol
};

struct GunInfo {
    uint16_t FirmwareVersion;
    std::string UUID;
    GunModel gunModel;
    uint32_t ConfigCRC;
    uint16_t BootloaderVersion;    
};
class WeaponManager {
public:
#ifndef RECOIL_DYNAMIC_NAME
    WeaponManager();
#else
    WeaponManager(const char* WeaponName[22]);
#endif
    ~WeaponManager();
    void init();
    void poll();
    GunInfo Properties = GunInfo();
protected:
#ifndef RECOIL_DYNAMIC_NAME
    const char* TargetName = RECOIL_NAME;
#else
    const char* TargetName;
#endif
    BLEDevice AttachedWeapon;
    BLEService RecoilGunService;
private:
    bool scanning = false;
};