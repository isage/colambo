#include "idstorage.h"
#include "kblparam.h"
#include "../colambo-helper.h"

#include <psp2kern/ctrl.h>
#include <psp2kern/io/fcntl.h>
#include <psp2kern/io/stat.h>
#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/ssmgr.h>
#include <psp2kern/kernel/suspend.h>
#include <psp2kern/kernel/sysclib.h>
#include <psp2kern/kernel/sysmem/data_transfers.h>
#include <psp2kern/kernel/sysroot.h>
#include <psp2kern/kernel/threadmgr.h>
#include <psp2kern/kernel/threadmgr/event_flags.h>
#include <psp2kern/lowio/pervasive.h>
#include <psp2kern/sblaimgr.h>
#include <psp2kern/syscon.h>
#include <psp2kern/usbd.h>
#include <psp2kern/usbserv.h>
#include <psp2kern/idstorage.h>
#include <taihen.h>
#include <string.h>

static infodata_t info = {0};
static monitor_t monitor = {0};
static int _dump_progress = 0;

int ksceSysconGetMultiCnInfo(SceUInt32 *pInfo);
int ksceSysconGetMicroUsbInfo(SceUInt32 *pInfo);

int sceSysconBatteryReadRegForDriver(SceUInt16 reg,SceUInt16 *data);
int sceSysconBatteryWriteRegForDriver(SceUInt16 reg,SceUInt16 data);
int sceSysconBatteryControlCommandForDriver(SceUInt16 reg,SceUInt16 *data);

int sceSysconReadCookieRegForDriver(SceUInt8 reg,SceUInt16 *data);
int sceSysconWriteCookieRegForDriver(SceUInt8 reg,SceUInt16 data);
int sceSysconReadElmoRegForDriver(SceUInt8 reg,SceUInt16 *data);
int sceHprmSetConnectCallbackForDriver(void* connect_cb, void* argp);

int ksceSysconNvsReadData(SceUInt32 offset, void *buffer, SceSize size);


int colamboDumpInfo()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;

  SceUID fd = ksceIoOpen("ux0:data/Colambo/info.txt", SCE_O_WRONLY|SCE_O_CREAT, 0777);
  if (fd >= 0)
  {
    char str[256] = {0};

#define myfprintf(...)        \
        memset(str, 0, 256);       \
        snprintf(str, 256, __VA_ARGS__); \
        ksceIoWrite(fd, str, strlen(str));

    myfprintf("Repair diagnostics run: %s\n", info.diagnosticsRun ? "yes" : "no");

    myfprintf("Product: %s\n", info.productTypeInfo);

    myfprintf("Firmware: min 0x%08X, previous 0x%08X, current 0x%08X\n", info.minFw, info.prevFw, info.curFw);

    myfprintf("SoC revision:\n");
    myfprintf("0x%08X\n", info.socRev);

    myfprintf("BL revision:\n");
    myfprintf("0x%04X\n", info.bootloaderRev);

    myfprintf("HWInfo:\n");
    myfprintf("0x%08X\n", info.hwInfo);

    _dump_progress = 10;

    myfprintf("SleepFactor:\n");
    myfprintf("0x%08X\n", info.sleepFactor);

    myfprintf("WakeupFactor:\n");
    myfprintf("0x%08X\n", info.wakeupFactor);

    myfprintf("UdcdStatus:\n");
    myfprintf("0x%08X\n", info.udcdStatus);

    myfprintf("PowerInfo:\n");
    myfprintf("0x%08X\n", info.powerInfo);

    myfprintf("HWInfo2");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.hwInfo2[0], info.hwInfo2[1], info.hwInfo2[2], info.hwInfo2[3], info.hwInfo2[4], info.hwInfo2[5], info.hwInfo2[6], info.hwInfo2[7], info.hwInfo2[8], info.hwInfo2[9], info.hwInfo2[10], info.hwInfo2[11], info.hwInfo2[12], info.hwInfo2[13], info.hwInfo2[14], info.hwInfo2[15]);

    _dump_progress = 20;

    myfprintf("ConsoleID:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.consoleId[0], info.consoleId[1], info.consoleId[2], info.consoleId[3], info.consoleId[4], info.consoleId[5], info.consoleId[6], info.consoleId[7], info.consoleId[8], info.consoleId[9], info.consoleId[10], info.consoleId[11], info.consoleId[12], info.consoleId[13], info.consoleId[14], info.consoleId[15]);

    myfprintf("openPSID:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.openPSID[0], info.openPSID[1], info.openPSID[2], info.openPSID[3], info.openPSID[4], info.openPSID[5], info.openPSID[6], info.openPSID[7], info.openPSID[8], info.openPSID[9], info.openPSID[10], info.openPSID[11], info.openPSID[12], info.openPSID[13], info.openPSID[14], info.openPSID[15]);

    myfprintf("pscode:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.pscode[0], info.pscode[1], info.pscode[2], info.pscode[3], info.pscode[4], info.pscode[5], info.pscode[6], info.pscode[7], info.pscode[8], info.pscode[9], info.pscode[10], info.pscode[11], info.pscode[12], info.pscode[13], info.pscode[14], info.pscode[15]);

    myfprintf("qaFlags:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.qaFlags[0], info.qaFlags[1], info.qaFlags[2], info.qaFlags[3], info.qaFlags[4], info.qaFlags[5], info.qaFlags[6], info.qaFlags[7], info.qaFlags[8], info.qaFlags[9], info.qaFlags[10], info.qaFlags[11], info.qaFlags[12], info.qaFlags[13], info.qaFlags[14], info.qaFlags[15]);

    myfprintf("bootFlags:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.bootFlags[0], info.bootFlags[1], info.bootFlags[2], info.bootFlags[3], info.bootFlags[4], info.bootFlags[5], info.bootFlags[6], info.bootFlags[7], info.bootFlags[8], info.bootFlags[9], info.bootFlags[10], info.bootFlags[11], info.bootFlags[12], info.bootFlags[13], info.bootFlags[14], info.bootFlags[15]);

    myfprintf("dipSwitches:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.dipSwitches[0], info.dipSwitches[1], info.dipSwitches[2], info.dipSwitches[3], info.dipSwitches[4], info.dipSwitches[5], info.dipSwitches[6], info.dipSwitches[7], info.dipSwitches[8], info.dipSwitches[9], info.dipSwitches[10], info.dipSwitches[11], info.dipSwitches[12], info.dipSwitches[13], info.dipSwitches[14], info.dipSwitches[15]);

    _dump_progress = 30;

    myfprintf("gcpID:\n");
    myfprintf("%s\n", info.gcpId);

    myfprintf("productID:\n");
    myfprintf("%s\n", info.productId);

    myfprintf("Prepackaged sim:\n");
    myfprintf("0x%02X\n", info.simPackNum);

    myfprintf("Com Type:\n");
    myfprintf("0x%02X\n", info.comType);

    myfprintf("spkg 0x18 contents Ver:\n");
    myfprintf("0x%08X\n", info.contentsVer);

    _dump_progress = 40;

    myfprintf("Factory sw ver:\n");
    myfprintf("0x%04X 0x%04X 0x%04X\n", info.softVer[0],info.softVer[1],info.softVer[2]);

    myfprintf("Color variation:\n");
    myfprintf("%02X %02X %02X %02X\n", info.colorVariation[0], info.colorVariation[1], info.colorVariation[2], info.colorVariation[3]);

    myfprintf("Temperature threshold:\n");
    myfprintf("%02X %02X %02X %02X\n", info.temperatureThreshhold[0], info.temperatureThreshhold[1], info.temperatureThreshhold[2], info.temperatureThreshhold[3]);

    _dump_progress = 50;

    myfprintf("%s\n", info.str1);
    myfprintf("%s\n", info.str2);

    myfprintf("Ernie:\n");
    myfprintf("HW: 0x%08X FW: 0x%08X DL: 0x%08X CFG: 0x%04X\n", info.ernieHwInfo, info.ernieFwVersion, info.ernieDlVersion, info.ernieCfgVersion);

    myfprintf("Elmo:\n");
    myfprintf("FW: 0x%04X\n", info.elmoFWVer);
    _dump_progress = 60;


    myfprintf("Cookie:\n");
    myfprintf("FW: 0x%04X\n", info.cookieFWVer);

    myfprintf("Abby:\n");
    myfprintf("HW: 0x%04X FW: 0x%04X DF: 0x%04X\n", info.abbyHWVersion, info.abbyFWVersion, info.abbyDFVersion);

    myfprintf("Battery calibration:\n");
    myfprintf("Volt: 0x%04X Current: 0x%04X\n", info.batteryVoltageCalib, info.batteryCurrentCalib);

    myfprintf("Battery lot:\n");
    myfprintf("%s\n", info.batteryLotInfo);

    myfprintf("EmmcFw:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X\n", info.emmcFwVersion[0], info.emmcFwVersion[1], info.emmcFwVersion[2], info.emmcFwVersion[3], info.emmcFwVersion[4], info.emmcFwVersion[5], info.emmcFwVersion[6], info.emmcFwVersion[7]);

    myfprintf("EmmcFw2:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X\n", info.emmcFwVersion2[0], info.emmcFwVersion2[1], info.emmcFwVersion2[2], info.emmcFwVersion2[3], info.emmcFwVersion2[4], info.emmcFwVersion2[5], info.emmcFwVersion2[6], info.emmcFwVersion2[7]);

    _dump_progress = 70;

    myfprintf("Front touch:\n");
    myfprintf("Vendor: %04X FW: %04X Cfg: %04X Lot: %02X %02X %02X %02X %02X %02X %02X %02X\n", info.tpFrontVendorID, info.tpFrontFirmwareRev, info.tpFrontCfgVersion, info.tpFrontLotInfo[0], info.tpFrontLotInfo[1], info.tpFrontLotInfo[2], info.tpFrontLotInfo[3], info.tpFrontLotInfo[4], info.tpFrontLotInfo[5], info.tpFrontLotInfo[6], info.tpFrontLotInfo[7]);

    myfprintf("Rear touch:\n");
    myfprintf("Vendor: %04X FW: %04X Cfg: %04X Lot: %02X %02X %02X %02X %02X %02X %02X %02X\n", info.tpRearVendorID, info.tpRearFirmwareRev, info.tpRearCfgVersion, info.tpRearLotInfo[0], info.tpRearLotInfo[1], info.tpRearLotInfo[2], info.tpRearLotInfo[3], info.tpRearLotInfo[4], info.tpRearLotInfo[5], info.tpRearLotInfo[6], info.tpRearLotInfo[7]);

    myfprintf("WLANBT:\n");
    myfprintf("HW: %08X WLAN MAC: %02X:%02X:%02X:%02X:%02X:%02X BT MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", info.wlanBtHWRevision, info.wlanMacAddress[0], info.wlanMacAddress[1], info.wlanMacAddress[2], info.wlanMacAddress[3], info.wlanMacAddress[4], info.wlanMacAddress[5], info.btMacAddress[0], info.btMacAddress[1], info.btMacAddress[2], info.btMacAddress[3], info.btMacAddress[4], info.btMacAddress[5]);

    myfprintf("ETH:\n");
    myfprintf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", info.ethMacAddress[0], info.ethMacAddress[1], info.ethMacAddress[2], info.ethMacAddress[3], info.ethMacAddress[4], info.ethMacAddress[5]);

    _dump_progress = 80;


    myfprintf("OLED lot:\n");
    myfprintf("%s\n", info.oledLotInfo);

    myfprintf("LCD lot:\n");
    myfprintf("%s\n", info.lcdLotInfo);

    myfprintf("Unknown lot:\n");
    myfprintf("%s\n", info.unkInfo);

    myfprintf("Unknown lot 2:\n");
    myfprintf("%s\n", info.unkInfo2);

    myfprintf("IMEI:\n");
    myfprintf("%s\n", info.imei);

    _dump_progress = 90;

    myfprintf("IMEI barcode:\n");
    myfprintf("%s\n", info.imeiBarcode);

    myfprintf("Parts barcode:\n");
    myfprintf("%s\n", info.partsNoBarcode);

    myfprintf("IMSI:\n");
    myfprintf("%s\n", info.imsi);

    myfprintf("ICCID:\n");
    myfprintf("%s\n", info.iccId);

    myfprintf("KibanID:\n");
    myfprintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", info.kibanId[0], info.kibanId[1], info.kibanId[2], info.kibanId[3], info.kibanId[4], info.kibanId[5], info.kibanId[6], info.kibanId[7], info.kibanId[8], info.kibanId[9], info.kibanId[10], info.kibanId[11], info.kibanId[12], info.kibanId[13], info.kibanId[14], info.kibanId[15]);


    ksceIoClose(fd);
  }

  _dump_progress = 100;

  EXIT_SYSCALL(state);
  return 0;
}


static int colamboDumpIdstorage_thread(SceSize args, void* argp)
{
  int r = ksceIoMkdir("ux0:data/Colambo/idstorage/", 0777);
  ksceDebugPrintf("ret = 0x%08x\n", r);
  for (int i = 0; i < 300; i++)
  {
    uint8_t buf[0x200]={0};
    int ret = ksceIdStorageReadLeaf(i, buf);
    ksceDebugPrintf("ret = 0x%08x\n", ret);
    if (ret >= 0)
    {
        char path[256];
        snprintf(path, 255, "ux0:data/Colambo/idstorage/leaf_0x%04X.bin", i);
        SceUID fd = ksceIoOpen(path, SCE_O_WRONLY|SCE_O_CREAT, 0777);
        ksceDebugPrintf("fd = 0x%08x\n", fd);

        if (fd >= 0)
        {
            ksceIoWrite(fd, buf, 512);
            ksceIoClose(fd);
        }
    }
    _dump_progress = i / 3;
  }

  if (_dump_progress < 100) _dump_progress = 100;

  // todo: zip? or on client?

  return 0;
}

int colamboDumpIdstorage()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;
  ksceKernelStartThread(ksceKernelCreateThread("ColamboThread", colamboDumpIdstorage_thread, 0x3C, 0x1000, 0, 0x10000, 0), 0,NULL);
  EXIT_SYSCALL(state);
  return 0;
}

static int colamboDumpAbbyRegisters_thread(SceSize args, void* argp)
{
  ksceIoMkdir("ux0:data/Colambo/abby/", 0777);
  for (int i = 0; i < 0xFF; i++)
  {
    uint16_t reg = 0;
    int ret = sceSysconBatteryReadRegForDriver(i,&reg);
    if (ret >= 0)
    {
        char path[256];
        snprintf(path, 255, "ux0:data/Colambo/abby/reg_0x%02X.bin", i);
        SceUID fd = ksceIoOpen(path, SCE_O_WRONLY|SCE_O_CREAT, 0777);
        if (fd >= 0)
        {
            ksceIoWrite(fd, &reg, 2);
            ksceIoClose(fd);
        }
    }
    _dump_progress = ((float)i / 2.5f);
  }

  if (_dump_progress < 100) _dump_progress = 100;

  // todo: zip? or on client?

  return 0;
}


int colamboDumpAbbyRegisters()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;
  ksceKernelStartThread(ksceKernelCreateThread("ColamboThread", colamboDumpAbbyRegisters_thread, 0x3C, 0x1000, 0, 0x10000, 0), 0,NULL);
  EXIT_SYSCALL(state);
  return 0;
}

static int colamboDumpAbbyDataflash_thread(SceSize args, void* argp)
{
  ksceIoMkdir("ux0:data/Colambo/abbydf/", 0777);

  for(int subclass = 0x0;subclass <= 0x70; subclass++)
  {
    char path[256];
    sceSysconBatteryWriteRegForDriver(0x61, 0x0000); // allow dataflash access

    snprintf(path, 255, "ux0:/data/Colambo/abbydf/subclass_0x%02x_block_0-3.bin", subclass);
    int f = ksceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT, 0777);
    SceUInt16 target = 0;

    // block 0
    target = (subclass & 0xFF) << 8 | 0x00;
    sceSysconBatteryWriteRegForDriver(0x3e, target); // subclass, block
    for (int i = 0x40; i < 0x5f; i+=2) // read data
    {
      SceUInt16 data = 0;
      int ret = sceSysconBatteryReadRegForDriver(i,&data);
      ksceIoWrite(f, &data, 2);
    }

    // block 1
    target = (subclass & 0xFF) << 8 | 0x01;
    sceSysconBatteryWriteRegForDriver(0x3e, target); // subclass, block
    for (int i = 0x40; i < 0x5f; i+=2) // read data
    {
      SceUInt16 data = 0;
      int ret = sceSysconBatteryReadRegForDriver(i,&data);
      ksceIoWrite(f, &data, 2);
    }

    // block 2
    target = (subclass & 0xFF) << 8 | 0x02;
    sceSysconBatteryWriteRegForDriver(0x3e, target); // subclass, block
    for (int i = 0x40; i < 0x5f; i+=2) // read data
    {
      SceUInt16 data = 0;
      int ret = sceSysconBatteryReadRegForDriver(i,&data);
      ksceIoWrite(f, &data, 2);
    }
    ksceIoClose(f);

    _dump_progress = ((float)subclass / 1.2f);
  }


  if (_dump_progress < 100) _dump_progress = 100;

  // todo: zip? or on client?

  return 0;
}


int colamboDumpAbbyDataflash()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;
  ksceKernelStartThread(ksceKernelCreateThread("ColamboThread", colamboDumpAbbyDataflash_thread, 0x3C, 0x1000, 0, 0x10000, 0), 0,NULL);
  EXIT_SYSCALL(state);
  return 0;
}

static int colamboDumpCookieRegisters_thread(SceSize args, void* argp)
{
  ksceIoMkdir("ux0:data/Colambo/cookie/", 0777);
  for (int i = 0; i < 0xFF; i++)
  {
    uint16_t reg = 0;
    int ret = sceSysconReadCookieRegForDriver(i,&reg);
    if (ret >= 0)
    {
        char path[256];
        snprintf(path, 255, "ux0:data/Colambo/cookie/reg_0x%02X.bin", i);
        SceUID fd = ksceIoOpen(path, SCE_O_WRONLY|SCE_O_CREAT, 0777);
        if (fd >= 0)
        {
            ksceIoWrite(fd, &reg, 2);
            ksceIoClose(fd);
        }
    }
    _dump_progress = ((float)i / 2.5f);
  }

  if (_dump_progress < 100) _dump_progress = 100;

  // todo: zip? or on client?

  return 0;
}


int colamboDumpCookieRegisters()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;
  ksceKernelStartThread(ksceKernelCreateThread("ColamboThread", colamboDumpCookieRegisters_thread, 0x3C, 0x1000, 0, 0x10000, 0), 0,NULL);
  EXIT_SYSCALL(state);
  return 0;
}

static int colamboDumpElmoRegisters_thread(SceSize args, void* argp)
{
  ksceIoMkdir("ux0:data/Colambo/elmo/", 0777);
  for (int i = 0; i < 0xFF; i++)
  {
    uint16_t reg = 0;
    int ret = sceSysconReadElmoRegForDriver(i,&reg);
    if (ret >= 0)
    {
        char path[256];
        snprintf(path, 255, "ux0:data/Colambo/elmo/reg_0x%02X.bin", i);
        SceUID fd = ksceIoOpen(path, SCE_O_WRONLY|SCE_O_CREAT, 0777);
        if (fd >= 0)
        {
            ksceIoWrite(fd, &reg, 2);
            ksceIoClose(fd);
        }
    }
    _dump_progress = ((float)i / 2.5f);
  }

  if (_dump_progress < 100) _dump_progress = 100;

  // todo: zip? or on client?

  return 0;
}

int colamboDumpElmoRegisters()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;
  ksceKernelStartThread(ksceKernelCreateThread("ColamboThread", colamboDumpElmoRegisters_thread, 0x3C, 0x1000, 0, 0x10000, 0), 0,NULL);
  EXIT_SYSCALL(state);
  return 0;
}

static int colamboDumpNvs_thread(SceSize args, void* argp)
{
  ksceIoMkdir("ux0:data/Colambo/nvs/", 0777);

  if (_dump_progress < 100) _dump_progress = 100;

  // todo: zip? or on client?

  return 0;
}


int colamboDumpNvs()
{
  uint32_t state;
  ENTER_SYSCALL(state);
  _dump_progress = 0;
  ksceKernelStartThread(ksceKernelCreateThread("ColamboThread", colamboDumpNvs_thread, 0x3C, 0x1000, 0, 0x10000, 0), 0,NULL);
  EXIT_SYSCALL(state);
  return 0;
}

int colamboGetDumpProgress()
{
    return _dump_progress;
}


int colamboGetInfo(infodata_t* info_out)
{
  uint32_t state;
  ENTER_SYSCALL(state);

  int ret = ksceKernelMemcpyToUser(info_out, &info, sizeof(infodata_t));

  EXIT_SYSCALL(state);
  return ret;
}

int connect_cb(SceUInt32 event, SceBool is_dock_exist, SceBool is_headphone_exist, SceBool is_remote_exist, SceBool is_microphone_exist, void* monitor)
{
  ((monitor_t*)monitor)->hpremoteMic = is_microphone_exist;
  ((monitor_t*)monitor)->hpremoteDock = is_dock_exist;
  ((monitor_t*)monitor)->hpremoteHp = is_headphone_exist;
  ((monitor_t*)monitor)->hpremoteRemote = is_remote_exist;
}


int colamboGetMonitorData(monitor_t* monitor_out)
{
  uint32_t state;
  ENTER_SYSCALL(state);

  ksceSysconGetMultiCnInfo(&monitor.multicnState);
  ksceSysconGetMicroUsbInfo(&monitor.microusbState);

  monitor.usb0State = ksceUsbServMacGet(0);
  monitor.usb1State = ksceUsbServMacGet(1);
  monitor.usb2State = ksceUsbServMacGet(2);

  sceSysconReadCookieRegForDriver(1, &monitor.cookieReg01);
  sceSysconReadCookieRegForDriver(2, &monitor.cookieReg02);

  monitor.abbyRegSOH = 0;
  monitor.abbyRegFlags = 0;
  monitor.abbyRegStatus = 0;
  monitor.abbyRegRC = 0;
  monitor.abbyRegFCC = 0;
  sceSysconBatteryReadRegForDriver(0x20, &monitor.abbyRegSOH);
  sceSysconBatteryReadRegForDriver(0x0A, &monitor.abbyRegFlags);
  sceSysconBatteryReadRegForDriver(0x10, &monitor.abbyRegRC);
  sceSysconBatteryReadRegForDriver(0x12, &monitor.abbyRegFCC);
  sceSysconBatteryControlCommandForDriver(0x0000, &monitor.abbyRegStatus);

  SceSysconPacket packet = {0};
  packet.tx[0] = 0x04;
  packet.tx[1] = 0;
  packet.tx[2] = 1;

  ksceSysconCmdExec(&packet,0);

  memcpy(&monitor.voltageCalibRam, packet.rx + 4, 2);
  memcpy(&monitor.voltageCalib, packet.rx + 6, 2);
  memcpy(&monitor.currentCalibRam, packet.rx + 8, 2);
  memcpy(&monitor.currentCalib, packet.rx + 10, 2);


  int subclass = 0x52;
  sceSysconBatteryWriteRegForDriver(0x61, 0x0000); // allow dataflash access

  // block 0
  SceUInt16 target = (subclass & 0xFF) << 8 | 0x00;
  sceSysconBatteryWriteRegForDriver(0x3e, target); // subclass, block
  int reg = 0x44;
  SceUInt16 data = 0;
  sceSysconBatteryReadRegForDriver(reg,&data);
  monitor.abbyUpdateStatus = data & 0xFF;

  int ret = ksceKernelMemcpyToUser(monitor_out, &monitor, sizeof(monitor_t));

  EXIT_SYSCALL(state);
  return ret;
}

int colamboResetAbby()
{
  uint32_t state;
  ENTER_SYSCALL(state);

  uint16_t data;
  sceSysconBatteryControlCommandForDriver(0x21, &data);
  sceSysconBatteryControlCommandForDriver(0x41, &data);

  EXIT_SYSCALL(state);
  return 0;
}

int init_thread(SceSize args, void *argp)
{
  // todo: import dumping functions?

  SceUID fd = ksceIoOpen("sdstor0:int-lp-ina-os", SCE_O_RDONLY, 0777);
  if( fd >= 0 )
  {
      char buf[0x100];
      unsigned int previous_fw = -1;
      ksceIoLseek(fd, 0xB000, SCE_SEEK_SET); //0xB000 is first file (always?)
      ksceIoRead(fd, buf, sizeof(buf));
      ksceIoClose(fd);
      info.prevFw = *(unsigned int *)(buf + 0x92); //at 0x92 in file is firmware
  }
  else
      ksceDebugPrintf("prev fw ret = 0x%08x\n", fd);

  info.socRev = kscePervasiveGetSoCRevision();

  kblParam_t *kbl = ksceKernelSysrootGetKblParam();
  if( kbl )
  {
      info.curFw = kbl->fwVer;
      info.minFw = kbl->minFwVer;

      memcpy(info.qaFlags, kbl->qaFlags, 0x10);
      memcpy(info.bootFlags, kbl->bootFlags, 0x10);
      memcpy(info.dipSwitches, kbl->dipSwitches, 0x20);
      memcpy(info.openPSID, kbl->openPSID, 0x10);
      memcpy(info.pscode, kbl->pscode, 0x8);

      info.sleepFactor = kbl->sleepFactor;
      info.wakeupFactor = kbl->wakeupFactor;
      info.udcdStatus = kbl->udcdStatus;
      info.hwInfo = kbl->hwInfo;
      info.powerInfo = kbl->powerInfo;
      memcpy(info.hwInfo2, kbl->hwInfo2, 0x10);
      info.bootloaderRev = kbl->bootloaderRev;
  }

  ksceSblAimgrGetConsoleId((SceConsoleId*)info.consoleId);

  Leaf0x100* l100;
  Leaf0x102* l102;
  Leaf0x103* l103;

  uint8_t buf[0x200];

  int ret = ksceIdStorageReadLeaf(0x100, buf);
  if (ret >= 0)
  {
    l100 = (Leaf0x100*)&buf;
    if (l100->str1[0] != 0xFF)
        strncat(info.str1, l100->str1, 0x100);
    else
        strncat(info.str1, "-", 0x100);

    if (l100->str2[0] != 0xFF)
        strncat(info.str2, l100->str2, 0x100);
    else
        strncat(info.str2, "-", 0x100);
  }
  else
  {
    ksceDebugPrintf("leaf 100 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x102, buf);
  if (ret >= 0)
  {
    l102 = (Leaf0x102*)&buf;

    if (l102->gcpId[0] != 0xFFFFFFFF)
        strncat(info.gcpId, l102->gcpId, 0x20);
    else
        strncat(info.gcpId, "-", 0x20);

    if (l102->productId[0] != 0xFFFFFFFF)
        strncat(info.productId, l102->productId, 0x20);
    else
        strncat(info.productId, "-", 0x20);

    info.simPackNum = l102->simPackNum;
    info.comType = l102->comType;
    info.contentsVer = l102->contentsVer;

    if (l102->imeiBarcode[0] != 0xFFFFFFFF)
        strncat(info.imeiBarcode, l102->imeiBarcode, 0x20);
    else
        strncat(info.imeiBarcode, "-", 0x20);

    if (l102->partsNoBarcode[0] != 0xFFFFFFFF)
        strncat(info.partsNoBarcode, l102->partsNoBarcode, 0x10);
    else
        strncat(info.partsNoBarcode, "-", 0x10);

    if (l102->imsi[0] != 0xFFFFFFFF)
        strncat(info.imsi, l102->imsi, 0x10);
    else
        strncat(info.imsi, "-", 0x10);

    if (l102->iccId[0] != 0xFFFFFFFF)
        strncat(info.iccId, l102->iccId, 0x14);
    else
        strncat(info.iccId, "-", 0x14);

    info.softVer[0] = l102->softVer[0];
    info.softVer[1] = l102->softVer[1];
    info.softVer[2] = l102->softVer[2];
  }
  else
  {
    ksceDebugPrintf("leaf 102 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x103, buf);
  if (ret >= 0)
  {
    l103 = (Leaf0x103*)&buf;

    info.ernieHwInfo = l103->ernieHwInfo;
    info.ernieFwVersion = l103->ernieFwVersion;
    info.ernieDlVersion = l103->ernieDlVersion;
    info.ernieCfgVersion = l103->ernieCfgVersion;

    memcpy(&info.emmcFwVersion, l103->emmcFwVersion, 0x8);
    memcpy(&info.emmcFwVersion2, l103->emmcFwVersion2, 0x8);

    info.elmoFWVer = l103->elmoFWVer;
    info.cookieFWVer = l103->cookieFWVer;

    info.barkleyFwVersion = l103->barkleyFwVersion;
    info.barkleyHwInfo = l103->barkleyHwInfo;

    info.abbyHWVersion = l103->abbyHWVersion;
    info.abbyFWVersion = l103->abbyFWVersion;
    info.abbyDFVersion = l103->abbyDFVersion;

    info.batteryVoltageCalib = l103->batteryVoltageCalib;
    info.batteryCurrentCalib = l103->batteryCurrentCalib;

    info.tpFrontVendorID = l103->tpFWVersion.frontVendorID;
    info.tpFrontFirmwareRev = l103->tpFWVersion.frontFirmwareRev;
    info.tpFrontCfgVersion = l103->tpConfigVersion.frontCfgVersion;
    info.tpRearVendorID = l103->tpFWVersion.rearVendorID;
    info.tpRearFirmwareRev = l103->tpFWVersion.rearFirmwareRev;
    info.tpRearCfgVersion = l103->tpConfigVersion.rearCfgVersion;

    memcpy(info.tpFrontLotInfo, l103->tpFrontLotInfo, 0x8);
    memcpy(info.tpRearLotInfo, l103->tpRearLotInfo, 0x8);

    info.wlanBtHWRevision = l103->wlanBtHWRevision;

    memcpy(info.wlanMacAddress, l103->wlanMacAddress, 6);
    memcpy(info.btMacAddress, l103->btMacAddress, 6);

    if (l103->batteryLotInfo[0] != 0xFFFFFFFF)
        strncat(info.batteryLotInfo, l103->batteryLotInfo, 0x20);
    else
        strncat(info.batteryLotInfo, "-", 0x20);

    if (l103->unkInfo[0] != 0xFFFFFFFF)
        strncat(info.unkInfo, l103->unkInfo, 0x64);
    else
        strncat(info.unkInfo, "-", 0x64);

    if (l103->oledLotInfo[0] != 0xFFFFFFFF)
        strncat(info.oledLotInfo, l103->oledLotInfo, 0x10);
    else
        strncat(info.oledLotInfo, "-", 0x10);

    if (l103->unkInfo2[0] != 0xFFFFFFFF)
        strncat(info.unkInfo2, l103->unkInfo2, 0x10);
    else
        strncat(info.unkInfo2, "-", 0x10);

    if (l103->lcdLotInfo[0] != 0xFFFFFFFF)
        strncat(info.lcdLotInfo, l103->lcdLotInfo, 0x20);
    else
        strncat(info.lcdLotInfo, "-", 0x20);
  }
  else
  {
    ksceDebugPrintf("leaf 103 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x104, buf);
  if (ret >= 0) info.diagnosticsRun = 1;
  else
  {
    info.diagnosticsRun = 0;
    ksceDebugPrintf("leaf 104 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x113, buf);
  if (ret >= 0)
  {
    ksceDebugPrintf("leaf 113 %d %x\n", buf[0] != 0xFF, buf[0]);
    if (buf[0] != 0xFF)
    {
        strncat(info.imei, buf, 32);
    }
    else
    {
        strncat(info.imei, "-", 32);
    }
  }
  else
  {
    strncat(info.imei, "-", 32);
    ksceDebugPrintf("leaf 113 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x115, buf);
  if (ret >= 0)
  {
    if (buf[0] != 0xFF)
    {
        strncat(info.productTypeInfo, buf, 0x10);
    }
    else
    {
      strncat(info.productTypeInfo, "-", 0x10);
    }
  }
  else
  {
    strncat(info.productTypeInfo, "-", 0x10);
    ksceDebugPrintf("leaf 115 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x117, buf);
  if (ret >= 0)
  {
    memcpy(info.temperatureThreshhold, buf, 4);
  }
  else
  {
    memset(info.temperatureThreshhold, 0, 4);
    ksceDebugPrintf("leaf 117 ret = 0x%08x\n", ret);
  }

  ret = ksceIdStorageReadLeaf(0x119, buf);
  if (ret >= 0)
  {
    memcpy(info.ethMacAddress, buf, 6);
  }
  else
  {
    memset(info.ethMacAddress, 0, 6);
    ksceDebugPrintf("leaf 119 ret = 0x%08x\n", ret);
  }

  ksceSysconNvsReadData(0x4E0, info.kibanId, 0x10);

  return 0;
}

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize args, void *argp)
{
  SceUID t = ksceKernelCreateThread("ColamboThread", init_thread, 0x3C, 0x1000, 0, 0x10000, 0);
  ksceKernelStartThread(t, 0,NULL);
  int status = 0;
  ksceKernelWaitThreadEnd(t, &status, 0);

  sceHprmSetConnectCallbackForDriver(connect_cb, &monitor);

  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp)
{
  return SCE_KERNEL_STOP_SUCCESS;
}
