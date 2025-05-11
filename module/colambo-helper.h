#ifndef __COLAMBO_H__
#define __COLAMBO_H__

#include <psp2/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#pragma pack(push, 1)

  typedef struct {
    uint32_t minFw; //Minimal firmware version
    uint32_t curFw;
    uint32_t prevFw;

    uint32_t socRev;
    uint32_t bootloaderRev;

    uint32_t hwInfo;
    uint8_t hwInfo2[0x10];

    uint32_t sleepFactor;
    uint32_t wakeupFactor;
    uint32_t udcdStatus;
    uint32_t powerInfo;

    uint8_t consoleId[0x10];

    uint8_t openPSID[0x10];
    uint8_t pscode[0x10];

    uint8_t qaFlags[0x10];
    uint8_t bootFlags[0x10];
    uint8_t dipSwitches[0x20];

    uint8_t diagnosticsRun; // leaf 104 present

    // leaf 80
    char str1[0x100+1];
    char str2[0x100+1];

    // leaf 102
    char gcpId[0x20 + 1];
    char productId[0x20 + 1];

    char productTypeInfo[0x10+1]; // leaf 115
    uint8_t colorVariation[4]; // leaf 116
    uint8_t temperatureThreshhold[4]; // leaf 117

    uint8_t simPackNum;   //Prepaid SIM card
    uint8_t comType;
    uint32_t contentsVer;  //spkgInfo.version from sceSblUsGetSpkgInfo(0x18)

    char imeiBarcode[32 + 1];
    char imei[32 + 1]; // from leaf 0x113
    char partsNoBarcode[16 + 1];
    char imsi[16 + 1];
    char iccId[20 + 1];

    //Version of the software executed on the unit
    //during manufacturing. Each element of the array
    //corresponds to a different program.
    uint32_t softVer[3];

    // todo: get from syscon too
    uint32_t ernieHwInfo;
    uint32_t ernieFwVersion;
    uint32_t ernieDlVersion;
    uint16_t ernieCfgVersion;

    uint8_t emmcFwVersion[0x8];
    uint8_t emmcFwVersion2[0x8];
    uint16_t elmoFWVer;
    uint16_t cookieFWVer;

    uint16_t barkleyFwVersion;
    uint16_t barkleyHwInfo;

    uint16_t abbyHWVersion;
    uint16_t abbyFWVersion;
    uint16_t abbyDFVersion;

    uint16_t batteryVoltageCalib;
    uint16_t batteryCurrentCalib;
    // end todo

    uint16_t tpFrontVendorID;
    uint16_t tpFrontFirmwareRev;
    uint16_t tpRearVendorID;
    uint16_t tpRearFirmwareRev;

    uint16_t tpFrontCfgVersion;
    uint16_t tpRearCfgVersion;

    uint8_t tpFrontLotInfo[0x8];
    uint8_t tpRearLotInfo[0x8];

    uint32_t wlanBtHWRevision;

    uint8_t wlanMacAddress[6];
    uint8_t btMacAddress[6];
    uint8_t ethMacAddress[6];

    char batteryLotInfo[0x20 + 1];
    char unkInfo[0x64 + 1];
    char oledLotInfo[0x10 + 1];
    char unkInfo2[0x10 + 1];
    char lcdLotInfo[0x20 + 1];
    uint8_t kibanId[0x20];

  } infodata_t;

  typedef struct {
    uint32_t multicnState;
    uint32_t microusbState;
    uint8_t usb0State;
    uint8_t usb1State;
    uint8_t usb2State;
    uint16_t cookieReg01; // charge/ac status
    uint16_t cookieReg02; // usb detect
    uint8_t hpremoteMic;
    uint8_t hpremoteDock;
    uint8_t hpremoteHp;
    uint8_t hpremoteRemote;

    uint16_t voltageCalibRam;
    uint16_t voltageCalib;
    uint16_t currentCalibRam;
    uint16_t currentCalib;
    uint16_t abbyRegSOH; // 0x20
    uint16_t abbyRegFlags; // 0x0A
    uint16_t abbyRegStatus; // 0x00
    uint16_t abbyRegRC; // 0x10
    uint16_t abbyRegFCC; // 0x12
    uint16_t abbyUpdateStatus;
  } monitor_t;

#pragma pack(pop)

  int colamboGetInfo(infodata_t* info);
  int colamboGetMonitorData(monitor_t* info);
  int colamboGetDumpProgress();
  int colamboDumpIdstorage();
  int colamboDumpAbbyRegisters();
  int colamboDumpAbbyDataflash();
  int colamboDumpCookieRegisters();
  int colamboDumpElmoRegisters();
  int colamboDumpNvs();
  int colamboDumpInfo();
  int colamboResetAbby();


#ifdef __cplusplus
}
#endif

#endif // __VIXEN_H__
