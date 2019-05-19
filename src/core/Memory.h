#pragma once
#include "../stdafx.h"
#define CheckPageBoundary(a) a > 0xff

struct NesFileHeader {
  Byte NesString[3];
  Byte FileFormat;
  Byte NPrg_Rom;
  Byte NChr_Rom;
  Byte ControlByte1;
  Byte ControlByte2;
  Byte NRamBanks;
};

class Memory {
public:
  Memory();
  ~Memory();

  void write(uint16_t index, Byte data);
  Byte read(uint16_t index);

  uint16_t readHalfWord(uint16_t index);
  void writeHalfWord(uint16_t address, uint16_t data);
  Byte updateValue(uint16_t address, Byte data);

  void loadRom1Slot(Byte *Bank);
  void loadRom2Slot(Byte *Bank);

  void switchSlot(Byte slot, Byte *Bank);

  Byte readZero(uint16_t address);
  Byte readZeroIndexed(uint16_t address, uint8_t offset);
  Byte readAbsolute(uint16_t address);
  Byte readAbsoluteIndexed(uint16_t address, uint8_t offset);
  Byte readPreIndexed(uint16_t address, uint16_t offset);
  Byte readPostIndexed(uint16_t address, uint16_t offset);

  // Return the address to jump when a interrupt occur
  inline uint16_t NMIInterrupt() {
    return m_Memory[0xFFFB] << 8 | m_Memory[0xFFFA];
  };
  inline uint16_t IRQInterrupt() {
    return m_Memory[0xFFFF] << 8 | m_Memory[0xFFFE];
  };
  inline uint16_t ResetInterrupt() {
    return m_Memory[0xFFFD] << 8 | m_Memory[0xFFFC];
  };

  // void PPUsetNameTableAddress(Byte slot);

  inline void setPPUIncreaseAmount(bool set) {
    set ? m_Memory[m_PPUControlRegister] | 0x04
        : m_Memory[m_PPUControlRegister] & ~0x04;
  };
  inline void setPPUPatternTableSprite(bool set) {
    set ? m_Memory[m_PPUControlRegister] | 0x08
        : m_Memory[m_PPUControlRegister] & ~0x08;
  };
  inline void setPPUPatternTableBackground(bool set) {
    set ? m_Memory[m_PPUControlRegister] | 0x10
        : m_Memory[m_PPUControlRegister] & ~0x10;
  };
  inline void setPPUSpriteSize(bool set) {
    set ? m_Memory[m_PPUControlRegister] | 0x20
        : m_Memory[m_PPUControlRegister] & ~0x20;
  };
  inline void setPPUMasterSlave(bool set) {
    set ? m_Memory[m_PPUControlRegister] | 0x40
        : m_Memory[m_PPUControlRegister] & ~0x40;
  };

  inline Byte getPPUNameTable() {
    return m_Memory[m_PPUControlRegister] & 0x3;
  };
  inline Byte getPPUIncreaseAmount() {
    return m_Memory[m_PPUControlRegister] & 0x4;
  };
  inline Byte getPPUPatternTableSprite() {
    return m_Memory[m_PPUControlRegister] & 0x8;
  };
  inline Byte getPPUPatternTableBackground() {
    return m_Memory[m_PPUControlRegister] & 0x10;
  };
  inline Byte getPPUSpriteSize() {
    return m_Memory[m_PPUControlRegister] & 0x20;
  };
  inline Byte getMasterSlave() {
    return m_Memory[m_PPUControlRegister] & 0x40;
  };
  inline Byte getPPUNMIDisable() {
    return m_Memory[m_PPUControlRegister] & 0x80;
  };

  inline Byte getPPUColor() {
    return m_Memory[m_PPUControlRegister + 1] & 0x1;
  };
  inline Byte getPPUClipBackground() {
    return m_Memory[m_PPUControlRegister + 1] & 0x2;
  };
  inline Byte getPPUClipSprite() {
    return m_Memory[m_PPUControlRegister + 1] & 0x4;
  };
  inline Byte getPPUHideBackground() {
    return m_Memory[m_PPUControlRegister + 1] & 0x8;
  };
  inline Byte getPPUHideSprite() {
    return m_Memory[m_PPUControlRegister + 1] & 0x10;
  };
  inline Byte getPPUColorMode() {
    return m_Memory[m_PPUControlRegister + 1] & 0xE0;
  }

  inline bool isPageBoundarySet() { return m_PageBoundary; };

  void DMA(void *OAMPointer, Address address);

  bool loadRom(const std::string &path);

private:
  Byte m_Memory[0x10000];

  bool m_PageBoundary;
  const uint16_t m_PPUControlRegister = 0x2000;
  const uint16_t m_PPUStatusRegister = 0x2002;
  const uint16_t m_SPRRAMAddrRegister = 0x2003;
  const uint16_t SpriteDMARegister = 0x4014;
};
