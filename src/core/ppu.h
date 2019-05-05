#pragma once
#include "stdafx.h"

struct Sprite 
{
	Byte yOffset;
	Byte indexTable;
	Byte spriteAttribute;
};

class CPU;
class Memory;
class PPU 
{
public:
	PPU(Memory* mem);
	~PPU();

private:
	Memory* m_CpuRam;

	Sprite m_Sprites[64];
	Byte m_Memory[0x4000]
};