#include <stdint.h>

//#pragma pack(push, 1)

typedef struct {
  uint8_t magic[4]; //'SMI\0'
  uint32_t version; //1
  uint32_t min_fwv; //Minimal firmware version
  uint8_t unused[0x80 - 0xC];
    //Encrypted with per-console keys.
    //This is used to verify the leaf has not been modified.
  uint8_t encrypted_data[0x200 - 0x80];
} Leaf0x80;


typedef struct {
  char str1[0x100];
  char str2[0x100];
} Leaf0x100;

typedef struct {
  uint32_t server_ip;
  uint16_t server_port;
  uint8_t netmask; //Number of '1' bits in netmask
  uint8_t unused;
  uint32_t client_ip;
  uint32_t defaultGW;
} conn_param;

typedef struct {
    uint32_t unk0;
    uint32_t unk4;
    struct {
        uint8_t id;
        uint8_t state;
    } ProcessId[0x20];
    char gcpId[0x20];
    char productId[0x20];
    //The following fields indicate the number of X present in unit
    struct {
        uint8_t ComNum;     //Com (3G module)
        uint8_t WlanNum;    //Ethernet is also counted in here, despite field name
        uint8_t BtNum;      //Bluetooth
        uint8_t BatteryNum;
        uint8_t HdmiNum;
        uint8_t CpNum;      //Communication Processor
        struct { //Guessed field names
            uint8_t Front;
            uint8_t Back;
        } CameraNum;
        struct { //Guessed field names
            uint8_t Front;
            uint8_t Back;
        } TouchNum;
        uint8_t SixSenseNum;  //Gyro
        uint8_t EMagNum;      //Magnetometer / Compass
        uint8_t GpsNum;
        uint8_t AnaDevNum;    //a.k.a. Analog Pad (AP) or Joystick
        uint8_t DisplayNum;
        uint8_t SimNum;       //SIM slot
    } DeviceNum;
    uint8_t simPackNum;   //Prepaid SIM card
    uint8_t comType;
    uint8_t unused_9A[14];
    uint32_t contentsVer;  //spkgInfo.version from sceSblUsGetSpkgInfo(0x18)
    uint8_t unk_AC[4];
    uint8_t unk_B0;
    uint8_t unused_B1[0x7];

    uint8_t unk_B8;
    uint8_t unused_B9[0x7];

    conn_param conn_param_0; //For WLAN test?
    conn_param conn_param_1; //For Ethernet test?

    char ssid[0x20];    //SSID of AP used for WLAN test
    uint8_t test_bt_addr[6]; //Bluetooth MAC address for BT test
    uint8_t unused_106[2];

    char imeiBarcode[32];
    char partsNoBarcode[16];
    char imsi[16];
    char iccId[20];

    uint8_t unused_15C[4];

    //Version of the software executed on the unit
    //during manufacturing. Each element of the array
    //corresponds to a different program.
    uint32_t softVer[3];
    uint8_t unused_16C[4];
    struct {
        char essid[12];
        uint8_t channel;
    } WlanTestApInfo;
    uint8_t unused_17D[3];
    uint16_t WlanRssi;
    uint8_t unused_182[6];

    //Obtained from sceSblUsGetSpkgInfo(0x1C), which
    //corresponds to preinstall data patch Spkg.
    //First 4 bytes = spkgInfo.version
    //Fifth byte    = spkgInfo.status[1]
    uint8_t CustomThemeVersion[5];
    uint8_t unused_18D[3];

    //If set, clears itself at some point during
    //factTest and skips something
    uint8_t ConfigProcessJumpFlag;
    uint8_t unused_191[111];
} Leaf0x102;

typedef struct {
    uint32_t ernieHwInfo;
    uint32_t ernieFwVersion;
    uint32_t ernieDlVersion;
    uint16_t ernieCfgVersion;

    uint8_t _padding0x00C[0x12];

    uint8_t emmcFwVersion[0x8];
    uint8_t _padding0x028[0x8];

    uint8_t emmcFwVersion2[0x8];
    uint8_t _padding0x038[0x8];

    uint16_t elmoFWVer;
    uint8_t _padding0x042[0x1E];

    uint16_t cookieFWVer;
    uint8_t _padding0x062[0x1E];

    uint16_t barkleyFwVersion;
    uint16_t barkleyHwInfo;

    uint8_t _padding0x084[0x1C];

    uint16_t abbyHWVersion;
    uint16_t abbyFWVersion;
    uint16_t abbyDFVersion;
    uint8_t _padding0x0A6[0x2];

    uint16_t batteryVoltageCalib;
    uint16_t batteryCurrentCalib;

    uint8_t _padding0x0AC[0x14];

    struct {
      uint16_t frontVendorID;
      uint16_t frontFirmwareRev;
      uint16_t rearVendorID;
      uint16_t rearFirmwareRev;
    } tpFWVersion;

    struct {
      uint16_t frontCfgVersion;
      uint16_t rearCfgVersion;
    } tpConfigVersion;

    uint8_t _padding0x0CC[0x4];

    uint8_t tpFrontLotInfo[0x8];
    uint8_t tpRearLotInfo[0x8];

    uint32_t wlanBtHWRevision;

    uint8_t _padding0x0E4[0x4];

    uint8_t wlanMacAddress[6];
    uint8_t _padding0x0EE[0x2];

    uint8_t btMacAddress[6];
    uint8_t _padding0x0F6[0xA];

    char batteryLotInfo[0x20];
    char unkInfo[0x64];
    char oledLotInfo[0x10];
    char unkInfo2[0x10];

    uint8_t _padding0x1A4[0x4];
    char lcdLotInfo[0x20];
    uint8_t _padding0x1C8[0x38];
} Leaf0x103;

typedef struct {
  uint8_t wlanRegion[3];
  uint8_t unused[0x200-3];
} Leaf0x110;

typedef struct {
  uint8_t wlanMac[6];
  uint8_t unused[0x200 - 6];
} Leaf0x111;

typedef struct {
  char comImei[16];
  // todo; other info
  uint8_t unused[0x200 - 16];
} Leaf0x113;

typedef struct {
  char productInfo[16];
  uint8_t unused[0x200 - 16];
} Leaf0x115;

typedef struct {
  uint8_t colorVariation[4];
  uint8_t unused[0x200 - 4];
} Leaf0x116;

typedef struct {
  uint8_t temperatureThreshhold[4];
  uint8_t unused[0x200 - 4];
} Leaf0x117;

typedef struct {
  uint8_t ethMac[6];
  uint8_t unused[0x200 - 6];
} Leaf0x119;


//#pragma pack(pop)