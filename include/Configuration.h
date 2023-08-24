#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
uint16_t E2PROM_BEGIN=0x0,  ///< Початок енергонезалежної пам'яті
         E2PROM_SIZE=0xFFF, ///< Розмір енергонезалежної пам'яті
        FLASH_BEGIN=0x0,    ///< Початок пам'яті флеш
        FLASH_SIZE=0xFFF,   ///< Розмір флеш пам'яті
        REC_LEN=0x20;       ///< Довжина запису

QString
    help{" -help"},
    NoInstall{"Program not found, continuation is not possible"};
std::string
    avrdude{"avrdude"},
    programer{" -c "},
    CPUchip{" -p m2560"},
    ALLfuses{" -U efuse:w:0xFD:m  -U hfuse:w:0xD8:m  -U lfuse:w:0xFF:m"},
    Ext{"hex"},
    DiscoveryFile{"nanite_v3.1.ino."},
    NanitInfoFile{"NanitInfo.ino."},
    BootFile{"with_bootloader."+Ext},
    WipeFile{"./wipe."+Ext},
    ClearFile{"./clear."+Ext},
    NumberFile{"./number."+Ext};
QString ProgramerList[]{
    "2232hio",
    "4232h",
    "adafruit_gemma",
    "arduino",
    "arduino-ft232r",
    "arduino_gemma",
    "arduinoisp",
    "arduinoisporg",
    "atmelice",
    "atmelice_dw",
    "atmelice_isp",
    "atmelice_pdi",
    "atmelice_tpi",
    "atmelice_updi",
    "avr109",
    "avr910",
    "avr911",
    "avrftdi",
    "avrisp",
    "avrisp2",
    "avrispmkII",
    "avrispv2",
    "buspirate",
    "buspirate_bb",
    "butterfly",
    "butterfly_mk",
    "bwmega",
    "c232hm",
    "c2n232i",
    "dasa",
    "dasa3",
    "diecimila",
    "digilent-hs2",
    "dragon_dw",
    "dragon_hvsp",
    "dragon_isp",
    "dragon_jtag",
    "dragon_pdi",
    "dragon_pp",
    "ehajo-isp",
    "flip1",
    "flip2",
    "ft2232h",
    "ft232h",
    "ft232r",
    "ft245r",
    "ft4232h",
    "iseavrprog",
    "jtag1",
    "jtag1slow",
    "jtag2",
    "jtag2avr32",
    "jtag2dw",
    "jtag2fast",
    "jtag2isp",
    "jtag2pdi",
    "jtag2slow",
    "jtag2updi",
    "jtag3",
    "jtag3dw",
    "jtag3isp",
    "jtag3pdi",
    "jtag3updi",
    "jtagkey",
    "jtagmkI",
    "jtagmkII",
    "jtagmkII_avr32",
    "ktlink",
    "linuxspi",
    "lm3s811",
    "mib510",
    "micronucleus",
    "mkbutterfly",
    "nibobee",
    "o-link",
    "openmoko",
    "pavr",
    "pickit2",
    "pickit4",
    "pickit4_isp",
    "pickit4_pdi",
    "pickit4_tpi",
    "pickit4_updi",
    "pkobn_updi",
    "ponyser",
    "powerdebugger",
    "powerdebugger_dw",
    "powerdebugger_isp",
    "powerdebugger_pdi",
    "powerdebugger_tpi",
    "powerdebugger_upd",
    "serialupdi",
    "siprog",
    "snap",
    "snap_isp",
    "snap_pdi",
    "snap_tpi",
    "snap_updi",
    "stk500",
    "stk500hvsp",
    "stk500pp",
    "stk500v1",
    "stk500v2",
    "stk600",
    "stk600hvsp",
    "stk600pp",
    "tc2030",
    "teensy",
    "tigard",
    "ttl232r",
    "tumpa",
    "um232h",
    "uncompatino",
    "urclock",
    "usbasp",
    "usbasp-clone",
    "usbtiny",
    "wiring",
    "xbee",
    "xplainedmini",
    "xplainedmini_dw",
    "xplainedmini_tpi",
    "xplainedmini_updi",
    "xplainedpro",
    "xplainedpro_pdi",
    "xplainedpro_updi"};

#endif // CONFIGURATINO_H