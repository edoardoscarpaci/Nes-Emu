#pragma once
#include "../stdafx.h"
#include "Memory.h"
struct Sprite

{
	Byte yOffset;
	Byte indexTable;
	Byte spriteAttribute;
};

class CPU;
class PPU
{
public:
	PPU(Memory* mem);
	~PPU();
	void step();


	inline bool getNameTableAddress(){return m_CpuRam->getPPUNameTable(); };
	inline bool getIncreaseAmount(){return m_CpuRam->getPPUIncreaseAmount();};
	inline bool getPatternTableSprite() {return m_CpuRam->getPPUPatternTableSprite();};
	inline bool getPatternTableBackground() {return m_CpuRam->getPPUPatternTableBackground();};
	inline bool getSpriteSize(){return m_CpuRam->getPPUSpriteSize();};
	inline bool getMasterSlave(){return m_CpuRam->getMasterSlave();};
	inline bool getNMIDisable(){return m_CpuRam->getPPUNMIDisable();};




private:
	Memory* m_CpuRam;

	Byte m_RightPattern[0xfff];
	Byte m_LeftPattern[0xfff];

	Byte m_NameTable[4][0x400];

	Byte m_ColorPalette[0x2f];

	Byte m_Memory[0x4000];
	Sprite m_Sprites[64];


	HalfWord m_Scanline;
	HalfWord m_CyclesDone;
};
