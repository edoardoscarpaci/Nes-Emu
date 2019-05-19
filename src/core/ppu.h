#pragma once
#include "../stdafx.h"
#include "Memory.h"

union PPUCTRL {
  struct {
    unsigned nt : 2;
    unsigned inc : 1;
    unsigned spat : 1;
    unsigned bpat : 1;
    unsigned spsize : 1;
    unsigned ms : 1;
    unsigned nmi : 1;
  };
  Byte reg;
};
union PPUMASK {
  struct {
    unsigned grey : 1;
    unsigned lfbackground : 1;
    unsigned lfsprite : 1;
    unsigned showbackground : 1;
    unsigned showprite : 1;
    unsigned red : 1;
    unsigned green : 1;
    unsigned blue : 1;
  };
  Byte reg;
};
union PPUSTATUS {
  struct {
    unsigned useless : 5;
    unsigned spriteov : 1;
    unsigned sprite0hit : 1;
    unsigned vblank : 1;
  };
  Byte reg;
};
union PPUADDR {
  struct {
    unsigned coarseX : 5;
    unsigned coarseY : 5;
    unsigned nt : 2;
    unsigned fyscroll : 3;
  };
  HalfWord reg : 15;
};

union Sprite {
  struct {
    Byte yOffset;
    Byte tileNumber;
    Byte attribute;
    Byte xOffset;
  };
  Byte sprite[4];

  Sprite &operator=(Sprite s) {
    sprite[0] = s.sprite[0];
    sprite[1] = s.sprite[1];
    sprite[2] = s.sprite[2];
    sprite[3] = s.sprite[3];
    return *this;
  }
};

class CPU;
class PPU {
public:
  PPU(Memory *mem);
  ~PPU();

  void step();

  inline bool getNameTableAddress() { return ctrl.nt; };
  inline bool getIncreaseAmount() { return ctrl.inc; };
  inline bool getPatternTableSprite() { return ctrl.spat; };
  inline bool getPatternTableBackground() { return ctrl.bpat; };
  inline bool getSpriteSize() { return ctrl.spsize; };
  inline bool getMasterSlave() { return ctrl.ms; };
  inline bool getNMIDisable() { return ctrl.nmi; };

  inline bool getColor() { return mask.grey; };
  inline bool getClipBackground() { return mask.lfbackground; };
  inline bool getClipSprite() { return mask.lfsprite; };
  inline bool getHideBackground() { return mask.showbackground; };
  inline bool getHideSprite() { return mask.showprite; };

  inline bool getPPUVBlankFlag() { return status.vblank; };
  inline bool getPPU0HitFlag() { return status.sprite0hit; };
  inline bool getPPUSpriteOverflowFlag() { return status.spriteov; };

  void DirectMemoryAccessCopy(Address address);
  Byte getData(HalfWord index, Byte value);
  void setData(HalfWord index, Byte value);

private:
  Memory *m_CpuRam;

  Byte m_PatternTable[2][0x1000];
  Byte m_NameTable[4][0x400];
  Byte m_ColorPalette[0x20];

  std::array<Sprite, 64> m_Sprites;

  HalfWord m_Scanline;
  HalfWord m_CyclesDone;

  Byte m_OAMAddress;
  Byte m_XFineScroll : 3;

  bool firstWrite;
  PPUADDR m_VramAddress, m_TempVramAddress;

  PPUSTATUS status;
  PPUCTRL ctrl;
  PPUMASK mask;

  std::array<Sprite, 8> secOAM;

  bool inizializeSecOAM;

  void write(HalfWord Address, Byte value);
  Byte read(HalfWord Address);
  Byte evaluateSprite();
  void loadSprite();
  void clearSprite();
};
