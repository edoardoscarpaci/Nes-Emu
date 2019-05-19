#include "ppu.h"
#include "../stdafx.h"
#include "Palette.h"

void PPU::step() {

  int x = m_CyclesDone - 1;
  int xfineScroll = (m_XFineScroll + x) % 8;
  if (m_Scanline == 0 || m_Scanline == 262) {

  }

  else if (m_Scanline >= 1 && m_Scanline <= 239 && x >= 8) {
    Byte backgroundColor = 0;
    Byte spriteColor = 0;
    Byte priority = 0;

    Byte Color;

    if (mask.showbackground) {
      Byte TileNumber = read(0x2000 | (m_VramAddress.reg & 0xfff));
      Byte attributeTable = read(0x23C0 | (m_VramAddress.reg & 0x0C00) |
                                 ((m_VramAddress.reg >> 4) & 0x38) |
                                 ((m_VramAddress.reg >> 2) & 0x07));

      // Read Tile Number and multiply by 16 to get tileAddress in palette table
      HalfWord addrPattern = TileNumber * 16 | getPatternTableBackground()
                                                   << 12;

      backgroundColor = ((read(addrPattern) >> xfineScroll) & 0x1) |
                        (read(addrPattern + 8) >> (xfineScroll - 1)) & 0x2;

      Byte shift = ((TileNumber / 16) % 2 << 2 | TileNumber % 2 << 1) & 0x6;
      backgroundColor |= ((read(attributeTable) << shift) & 0x3) << 2;

      if ((m_VramAddress.reg & 0x001F) == 31) // if coarse X == 31
      {
        m_VramAddress.reg &= ~0x001F; // coarse X = 0
        m_VramAddress.reg ^= 0x0400;  // switch horizontal nametable
      } else
        m_VramAddress.reg += 1;
    }
    if (mask.showprite && (mask.lfsprite || xfineScroll < 8))
      for (int i = 0; i < secOAM.size(); i++) {
        int height = getSpriteSize() ? 16 : 8;
        int xPixel = (m_CyclesDone - secOAM[i].xOffset) % 8;
        int yLine = (m_Scanline - secOAM[i].yOffset) % height;

        if (!(secOAM[i].attribute & 0x40))
          xPixel ^= 7;
        if (!(secOAM[i].attribute & 0x80))
          yLine ^= height;

        int addr;

        if (height == 8)
          addr = (secOAM[i].tileNumber & ~1) * 16 + ctrl.spat ? 0x1000 : 0x0;
        else
          addr = (secOAM[i].tileNumber & ~1) * 16 + secOAM[i].tileNumber & 0x1
                     ? 0x1000
                     : 0x0;

        addr += yLine + (yLine % 8);

        spriteColor = read(addr) >> xPixel & 0x1;
        spriteColor |= ((read(addr + 8) >> xPixel) & 0x1) << 1;

        spriteColor |= (secOAM[i].attribute & 0x3) << 2;
        priority = (secOAM[i].attribute & 0x20);

        if (!status.sprite0hit && i == 0 && backgroundColor &&
            mask.showbackground && spriteColor) {
          status.sprite0hit = true;
          break;
        }
      }

    if ((!backgroundColor && spriteColor) ||
        (backgroundColor && spriteColor && !priority)) {
      Color = spriteColor;
    } else if (!backgroundColor && !spriteColor) {
      Color = 0;
    } else {
      Color = backgroundColor;
    }

  } else if (m_Scanline == 240) {
    if ((m_VramAddress.reg & 0x7000) != 0x7000) // if fine Y < 7
      m_VramAddress.reg += 0x1000;              // increment fine Y
    else {
      m_VramAddress.reg &= ~0x7000;              // fine Y = 0
      int y = (m_VramAddress.reg & 0x03E0) >> 5; // let y = coarse Y
      if (y == 29) {
        y = 0;                       // coarse Y = 0
        m_VramAddress.reg ^= 0x0800; // switch vertical nametable
      } else if (y == 31)
        y = 0; // coarse Y = 0, nametable not switched
      else
        y += 1; // increment coarse Y
      m_VramAddress.reg = (m_VramAddress.reg & ~0x03E0) | (y << 5);
      // put coarse Y back into m_VramAddress.reg
    }
  }

  else if (m_Scanline >= 241 && m_Scanline <= 260) {
    if (ctrl.nmi) {
      status.vblank = true;
      // call nmi
    }
  }
}

Byte PPU::evaluateSprite() {}

void PPU::loadSprite() {
  int range;
  int n = 0;
  for (Sprite s : m_Sprites) {
    if (getSpriteSize())
      range = 16; // if sprite 8x16 set the height as 16 to control later
    else
      range = 8;

    int line = m_Scanline - s.yOffset;
    if (line < range && line >= 0) {
      secOAM[n] = s;
      if (++n > 8) {
        status.spriteov = true;
        break;
      }
    }
  }
}

void PPU::clearSprite() {
  for (Sprite i : secOAM) {
    i.sprite[0] = 0xff;
    i.sprite[1] = 0xff;
    i.sprite[2] = 0xff;
    i.sprite[3] = 0xff;
  }
}

void PPU::setData(HalfWord index, Byte value) {
  switch (index) {
  case 0:
    ctrl.reg = value;
    m_TempVramAddress.nt = ctrl.nt;
    break;
  case 1:
    mask.reg = value;
    break;
  case 3:
    m_OAMAddress = value;
    break;
  case 4:
    m_Sprites[m_OAMAddress / 4].sprite[m_OAMAddress % 4] = value;
    m_OAMAddress++;
    break;

  case 5:
    if (firstWrite) {
      m_XFineScroll = value & 0x7;
      m_TempVramAddress.coarseX = value >> 3;
    } else {
      m_TempVramAddress.fyscroll = value & 0x7;
      m_TempVramAddress.coarseY = value >> 3;
    }
    break;

  case 6:
    if (firstWrite)
      m_TempVramAddress.reg = (value % 0x4000) << 8;
    else {
      m_TempVramAddress.reg |= value % 0x4000;
      m_VramAddress.reg = m_TempVramAddress.reg;
    }
    break;

  case 7:
    write(m_VramAddress.reg, value);
    getIncreaseAmount() ? m_VramAddress.reg += 32 : m_VramAddress.reg += 1;
    break;
  }
}

Byte PPU::getData(HalfWord index, Byte value) {
  switch (index) {
  case 2:
    firstWrite = 0;
    status.vblank = 0;
    return status.reg;
  case 4:
    if (inizializeSecOAM)
      return 0xff;

    return m_Sprites[m_OAMAddress / 4].sprite[m_OAMAddress % 4];
  case 7:
    Byte temp = read(m_VramAddress.reg);
    ctrl.inc ? m_VramAddress.reg += 32 : m_VramAddress.reg += 1;
    return temp;
  }
}

void PPU::write(HalfWord address, Byte value) {
  if (address < 0x2000) {
    m_PatternTable[address % 0x1000][address % 2] = value;
  } else if (address < 0x3000) {
    m_NameTable[address % 0x3C0][address % 4] = value;
  } else if (address < 0x4000) {
    m_ColorPalette[(address % 0x20) % 4] = value;
  } else {
    write(address % 0x4000, value);
  }
}

Byte PPU::read(HalfWord address) {
  if (address < 0x2000) {
    return m_PatternTable[address / 0x1000][address % 2];
  } else if (address < 0x3000) {
    return m_NameTable[address / 0x3C0][address % 4];
  } else if (address < 0x4000) {
    return m_ColorPalette[(address % 0x20) % 4];
  } else {
    return read(address % 0x4000);
  }
}
