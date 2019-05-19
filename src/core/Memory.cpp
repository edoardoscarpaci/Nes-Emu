#include "Memory.h"
#include "../stdafx.h"

Memory::Memory() : m_PageBoundary(false) { memset(m_Memory, 0, 0x10000); }

Memory::~Memory() {}

void Memory::write(uint16_t index, Byte data) {
  if (index >= 0x800 && index <= 0x2000) {
    m_Memory[index % 0x800] = data;
  } else if (index > 0x2000 && index <= 4000) {
    m_Memory[index % 8 + 0x2000] = data;
  } else {
    m_Memory[index] = data;
  }
}

Byte Memory::read(uint16_t index) {
  if (index >= 0x800 && index <= 0x2000) {

    return m_Memory[index % 0x800];
  } else if (index > 0x2000 && index <= 4000) {
    return m_Memory[index % 8 + 0x2000];
  } else {
    return m_Memory[index];
  }
}

uint16_t Memory::readHalfWord(uint16_t index) {

  if (index >= 0x800 && index <= 0x2000) {
    return m_Memory[(index + 1) % 0x800] << 8 | m_Memory[index % 0x800];
  }

  else if (index > 0x2000 && index <= 4000) {
    return m_Memory[((index + 1) % 8) + 0x2000] << 8 |
           m_Memory[index % 8 + 0x2000];
  } else {
    return m_Memory[index + 1] << 8 | m_Memory[index];
  }
}

void Memory::writeHalfWord(uint16_t address, uint16_t data) {
  if (address >= 0x800 && address <= 0x2000) {
    m_Memory[address % 0x800] = data & 0xff;
    m_Memory[address + 1 % 0x800] = data >> 8;

  } else if (address > 0x2000 && address <= 4000) {
    m_Memory[address % 8 + 0x2000] = data & 0xff;
    m_Memory[address + 1 % 8 + 0x2000] = data >> 8;

  } else {
    m_Memory[address] = data & 0xff;
    m_Memory[address + 1] = data >> 8;
  }
}

Byte Memory::updateValue(uint16_t address, Byte data) {
  if (address >= 0x800 && address <= 0x2000) {
    m_Memory[address % 0x800] += data;
  } else if (address > 0x2000 && address <= 4000) {
    m_Memory[address % 8 + 0x2000] += data;
  } else {
    m_Memory[address] += data;
  }

  return m_Memory[address];
}

void Memory::loadRom1Slot(Byte *Bank) {
  memcpy(&m_Memory[0x8000], Bank, 0x4000);
}

void Memory::loadRom2Slot(Byte *Bank) {
  memcpy(&m_Memory[0xC000], Bank, 0x4000);
}

void Memory::switchSlot(Byte slot, Byte *Bank) {
  if (slot == 1) {
    memcpy(&m_Memory[0x8000], Bank, 0x4000);

  } else {
    memcpy(&m_Memory[0xC000], Bank, 0x4000);
  }
}

Byte Memory::readZero(uint16_t address) { return read(read(address)); }

Byte Memory::readZeroIndexed(uint16_t address, uint8_t offset) {
  return read(read(address) + offset);
}

Byte Memory::readAbsolute(uint16_t address) {

  return read(readHalfWord(address));
}

Byte Memory::readAbsoluteIndexed(uint16_t address, uint8_t offset) {
  HalfWord realAddress = readHalfWord(address) + offset;
  m_PageBoundary = CheckPageBoundary(realAddress);

  return read(realAddress);
}

Byte Memory::readPreIndexed(uint16_t address, uint16_t offset) {
  return read(readHalfWord(read(address) + offset));
}

Byte Memory::readPostIndexed(uint16_t address, uint16_t offset) {
  uint16_t realAddress = readHalfWord(read(address)) + offset;
  m_PageBoundary = CheckPageBoundary(realAddress);

  return read(realAddress);
}

void Memory::DMA(void *OAMPointer, Address address) {
  memcpy(OAMPointer, &m_Memory[address], 256);
}

bool Memory::loadRom(const std::string &path) {

  int size;
  if (path.find(".nes") == std::string::npos)
    return false;

  NesFileHeader header;
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  size = file.tellg();
  file.seekg(0, file.beg);

  file.read((char *)&header, 9);
  file.read((char *)&m_Memory[0x8000], header.NPrg_Rom * 0x4000);

  return true;
}
