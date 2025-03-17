#include "WeaponManager.hpp"

#ifndef RECOIL_DYNAMIC_NAME
WeaponManager::WeaponManager() {

}
#else
WeaponManager::WeaponManager(const char* WeaponName[22]) {
    if (!BLE.begin())
        return;//FIX
}
#endif
WeaponManager::~WeaponManager() {

}
void WeaponManager::init() {
    BLE.scanForName(this->TargetName);
    this->scanning = true;
}
void WeaponManager::poll() {
    BLE.poll();
    if (this->scanning) {
        BLEDevice Discovered = BLE.available();
        if (Discovered.connect()) {
            this->AttachedWeapon = Discovered;
            BLE.stopScan();
            this->scanning = false;
            this->RecoilGunService = this->AttachedWeapon.service("E6F59D10-8230-4a5c-B22F-C062B1D329E3");
            if (!this->RecoilGunService.characteristic("E6F59D11-8230-4a5c-B22F-C062B1D329E3").read()) {
                this->AttachedWeapon.disconnect();
                this->scanning = true;
                BLE.scanForName(this->TargetName);
            }
            std::array<uint8_t, 8> uuid = {};
            const uint8_t* identity = this->RecoilGunService.characteristic("E6F59D11-8230-4a5c-B22F-C062B1D329E3").value();
            std::copy(identity, identity + 8, uuid.begin());
            this->Properties.FirmwareVersion = identity[0] << 0x8 | identity[1];
            this->Properties.UUID = "";
            for (uint8_t character : uuid) {
                //TODO
            }
        }
    }
    if (!this->scanning && this->AttachedWeapon && !this->AttachedWeapon.connected()) {
        BLE.scanForName(this->TargetName);
        this->scanning = true;
    }
}