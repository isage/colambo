#include <stdint.h>

typedef struct {
  uint16_t version;
  uint16_t size;
  uint32_t fwVer;
  uint32_t minFwVer;
  uint32_t unk00C;
  uint32_t unk010; // Used for Kit Activation. If lower than 0x20, the Kit is fake activated (License Status = 0, Issue No = 0, Expire Date = 0xffffffff). If lower than 0x30, default bus error handler is not registered in SceKernelBusError.
  uint8_t unk014[0xC];
  uint8_t qaFlags[0x10];
  uint8_t bootFlags[0x10];
  uint8_t dipSwitches[0x20];
  uint32_t dramBase;
  uint32_t dramSize;
  uint32_t unk068;
  uint32_t bootType;
  uint8_t openPSID[0x10];
  uint32_t secureKernelEnpBase;
  uint32_t secureKernelEnpSize;
  uint32_t contextAuthSmBase;
  uint32_t contextAuthSmSize;
  uint32_t kprxAuthSmBase;
  uint32_t kprxAuthSmSize;
  uint32_t progRvkBase;
  uint32_t progRvkSize;
  uint8_t pscode[0x8];
  uint32_t stackChkGuard;
  uint32_t unk0AC;
  uint8_t sessionId[0x10];
  uint32_t sleepFactor;
  uint32_t wakeupFactor;
  uint32_t udcdStatus;
  uint32_t bootControls;
  uint32_t suspendinfoBase;
  uint32_t hwInfo;
  uint32_t powerInfo;
  uint32_t unk0DC;
  uint32_t unk0E0; // If resume, always 0 (second_loader).
  uint32_t unk0E4;
  uint8_t hwInfo2[0x10];
  uint32_t bootloaderRev;
  uint32_t magic;
  uint8_t coredumpKey[0x20];
  uint8_t unused[0xE0];
} kblParam_t;

