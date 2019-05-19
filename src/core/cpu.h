#pragma once

#include "../stdafx.h"
#define Frequency 1.79 * 10E+6 //10e+6 is to let 1.79 in Mhz so million of heartz
#define FrameRate 60
#define Multiplier 1.0



class Memory;
class CPU
{
public:
	CPU();
	~CPU();

	//Just mask the bit of the flag
	inline bool getCarryFlag() { return m_Ps & 0x1;};
	inline bool getZeroFlag() { return m_Ps & 0x2;};
	inline bool getDecimalModeFlag() { return m_Ps & 0x8;};
	inline bool getDisableInterruptFlag() { return m_Ps & 0x4;};
	inline bool getBreakFlag() {return m_Ps & 0x10;};
	inline bool getOverflowFlag() { return m_Ps & 0x40; };
	inline bool getNegativeFlag() { return m_Ps & 0x80; };

	//Set the value of Flag if on is True  and will do an OR with the bit set in the position of the flag
	//If we need to unset the flag will do a AND with all the bit set and only the bit in the position of the flag unset;

	inline void setCarryFlag(bool on) { on ? m_Ps |= 0x1 : m_Ps &= 0xFE; };
	inline void setZeroFlag(bool on) { on ? m_Ps |= 0x2 : m_Ps &= 0xFD; };
	inline void setDisableInterruptFlag(bool on) { on ? m_Ps |= 0x4 : m_Ps &= 0xFB; };
	inline void setDecimalModeFlag(bool on) { on ? m_Ps |= 0x8 : m_Ps &= 0xF7;};
	inline void setBreakFlag(bool on) { on ? m_Ps |= 0x10 : m_Ps &= 0xEF; };
	inline void setOverflowFlag(bool on) { on ? m_Ps |= 0x40 : m_Ps &= 0xBF; };
	inline void setNegativeFlag(bool on) { on ? m_Ps |= 0x80 : m_Ps &= 0x7F;};

	static void NMI_callback();


private:
	SixteenBitRegister m_PC;
	EightBitRegister m_SP, m_Acc, m_X, m_Y, m_Ps;

	Byte(CPU::*OpCodePointer[256])(void) =
	{
		OpCodeBRK,
		OpCodeORAIndX,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeORAZero,
		OpCodeASLZero,

		OpcodeNull,

		OpCodePHP,
		OpCodeORAImm,
		OpCodeASLAcc,

		OpcodeNull,
		OpcodeNull,

		OpCodeORAAbs,
		OpCodeASLAbs,

		OpcodeNull,

		OpCodeBPL,
		OpCodeORAIndY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeORAZeroX,
		OpCodeASLZeroX,

		OpcodeNull,

		OpCodeCLC,
		OpCodeORAAbsY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeORAAbsX,
		OpCodeASLAbsX,

		OpcodeNull,

		OpCodeJSR,
		OpCodeANDIndX,

		OpcodeNull,
		OpcodeNull,

		OpCodeBITZero,
		OpCodeANDZero,
		OpCodeROLZero,

		OpcodeNull,

		OpCodePLP,
		OpCodeANDImm,
		OpCodeROLAcc,

		OpcodeNull,

		OpCodeBITAbs,
		OpCodeANDAbs,
		OpCodeROLAbs,

		OpcodeNull,

		OpCodeBMI,
		OpCodeANDIndY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeANDZeroX,
		OpCodeROLZeroX,

		OpcodeNull,

		OpCodeSEC,
		OpCodeANDAbsY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeANDAbsX,
		OpCodeROLAbsX,

		OpcodeNull,

		OpCodeRTI,
		OpCodeEORIndX,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeEORZero,
		OpCodeLSRZero,

		OpcodeNull,

		OpCodePHA,
		OpCodeEORImm,
		OpCodeLSRAcc,

		OpcodeNull,

		OpCodeJMPAbs,
		OpCodeEORAbs,
		OpCodeLSRAbs,

		OpcodeNull,

		OpCodeBVC,
		OpCodeEORIndY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeEORZeroX, //0x55,
		OpCodeLSRZeroX,

		OpcodeNull,

		OpCodeCLI,
		OpCodeEORAbsY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeEORAbsX,
		OpCodeLSRAbsX,

		OpcodeNull,

		OpCodeRTS,
		OpCodeADCIndX,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeADCZero,
		OpCodeRORZero,

		OpcodeNull,

		OpCodePLA,
		OpCodeADCImm,
		OpCodeRORAcc,

		OpcodeNull,

		OpCodeJMPInd,
		OpCodeADCAbs,
		OpCodeRORAbs,

		OpcodeNull,

		OpCodeBVS,
		OpCodeADCIndY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeADCZeroX,
		OpCodeRORZeroX,

		OpcodeNull,

		OpCodeSEI,
		OpCodeADCAbsY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeADCAbsX,
		OpCodeRORAbsX,

		OpcodeNull,
		OpcodeNull,

		OpCodeSTAIndX,

		OpcodeNull,
		OpcodeNull,

		OpCodeSTYZero,
		OpCodeSTAZero,
		OpCodeSTXZero,

		OpcodeNull,

		OpCodeDEY,

		OpcodeNull,

		OpCodeTXA,

		OpcodeNull,

		OpCodeSTYAbs,
		OpCodeSTAAbs,
		OpCodeSTXAbs,

		OpcodeNull,

		OpCodeBCC,
		OpCodeSTAIndY,

		OpcodeNull,
		OpcodeNull,

		OpCodeSTYZeroX,
		OpCodeSTAZeroX,
		OpCodeSTXZeroY,

		OpcodeNull,

		OpCodeTYA,
		OpCodeSTAAbsY,
		OpCodeTXS,

		OpcodeNull,
		OpcodeNull,

		OpCodeSTAIndX,

		OpcodeNull,
		OpcodeNull,

		OpCodeLDYImm,
		OpCodeLDAIndX,
		OpCodeLDXImm,

		OpcodeNull,

		OpCodeLDYZero,
		OpCodeLDAZero,
		OpCodeLDXZero,

		OpcodeNull,

		OpCodeTAY,
		OpCodeLDAImm,
		OpCodeTAX,
		OpcodeNull,

		OpCodeLDYAbs,
		OpCodeLDAAbs,
		OpCodeLDXAbs,

		OpcodeNull,

		OpCodeBCS,
		OpCodeLDAIndY,

		OpcodeNull,
		OpcodeNull,

		OpCodeLDYZeroX,
		OpCodeLDAZeroX,
		OpCodeLDXZeroY,

		OpcodeNull,

		OpCodeCLV,
		OpCodeLDAAbsY,
		OpCodeTSX,

		OpcodeNull,

		OpCodeLDYAbsX,
		OpCodeLDAAbsX,
		OpCodeLDXAbsY,

		OpcodeNull,

		OpCodeCPYImm,
		OpCodeCMPIndX,

		OpcodeNull,
		OpcodeNull,

		OpCodeCPYZero,
		OpCodeCMPZero,
		OpCodeDECZero,

		OpcodeNull,

		OpCodeINY,
		OpCodeCMPImm,
		OpCodeDEX,

		OpcodeNull,

		OpCodeCPYAbs,
		OpCodeCMPAbs,
		OpCodeDECAbs,

		OpcodeNull,

		OpCodeBNE,
		OpCodeCMPIndY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeCMPZeroX,
		OpCodeDECZeroX,

		OpcodeNull,

		OpCodeCLD,
		OpCodeCMPAbsY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeCMPAbsX,
		OpCodeDECAbsX,

		OpcodeNull,

		OpCodeCPXImm,
		OpCodeSBCIndX,

		OpcodeNull,
		OpcodeNull,

		OpCodeCPXZero,
		OpCodeSBCZero,
		OpCodeINCZero,

		OpcodeNull,

		OpCodeINX,
		OpCodeSBCImm,
		OpCodeNOP,

		OpcodeNull,

		OpCodeCPXAbs,
		OpCodeSBCAbs,
		OpCodeINCAbs,

		OpcodeNull,

		OpCodeBEQ,
		OpCodeSBCIndY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeSBCZeroX,
		OpCodeINCZeroX,

		OpcodeNull,

		OpCodeSED,
		OpCodeSBCAbsY,

		OpcodeNull,
		OpcodeNull,
		OpcodeNull,

		OpCodeSBCAbsX,
		OpCodeINCAbsX,

		OpcodeNull

	};

	Memory* m_Ram;


	double m_Multiplier;
	double m_CyclesPerFrame;


#pragma region OpCodeFunction
	Byte OpcodeNull();

	Byte OpCodeADCZero();
	Byte OpCodeADCZeroX();
	Byte OpCodeADCImm();
	Byte OpCodeADCAbs();
	Byte OpCodeADCAbsX();
	Byte OpCodeADCAbsY();
	Byte OpCodeADCIndY();
	Byte OpCodeADCIndX();

	Byte OpCodeANDImm();
	Byte OpCodeANDAbs();
	Byte OpCodeANDAbsX();
	Byte OpCodeANDAbsY();
	Byte OpCodeANDZero();
	Byte OpCodeANDZeroX();
	Byte OpCodeANDIndX();
	Byte OpCodeANDIndY();

	Byte OpCodeASLAcc();
	Byte OpCodeASLZero();
	Byte OpCodeASLZeroX();
	Byte OpCodeASLAbs();
	Byte OpCodeASLAbsX();

	Byte OpCodeBCC();
	Byte OpCodeBCS();

	Byte OpCodeBEQ();

	Byte OpCodeBITZero();
	Byte OpCodeBITAbs();

	Byte OpCodeBMI();
	Byte OpCodeBNE();
	Byte OpCodeBPL();
	Byte OpCodeBRK();

	Byte OpCodeBVC();
	Byte OpCodeBVS();

	Byte OpCodeCLC();
	Byte OpCodeCLD();
	Byte OpCodeCLI();
	Byte OpCodeCLV();

	Byte OpCodeCMPImm();
	Byte OpCodeCMPZero();
	Byte OpCodeCMPZeroX();
	Byte OpCodeCMPAbs();
	Byte OpCodeCMPAbsX();
	Byte OpCodeCMPAbsY();
	Byte OpCodeCMPIndX();
	Byte OpCodeCMPIndY();


	Byte OpCodeCPXImm();
	Byte OpCodeCPXZero();
	Byte OpCodeCPXAbs();

	Byte OpCodeCPYImm();
	Byte OpCodeCPYZero();
	Byte OpCodeCPYAbs();



	Byte OpCodeDECZero();
	Byte OpCodeDECZeroX();
	Byte OpCodeDECAbs();
	Byte OpCodeDECAbsX();


	Byte OpCodeDEX();
	Byte OpCodeDEY();

	Byte OpCodeEORImm();
	Byte OpCodeEORZero();
	Byte OpCodeEORZeroX();
	Byte OpCodeEORAbs();
	Byte OpCodeEORAbsX();
	Byte OpCodeEORAbsY();
	Byte OpCodeEORIndX();
	Byte OpCodeEORIndY();


	Byte OpCodeINCZero();
	Byte OpCodeINCZeroX();
	Byte OpCodeINCAbs();
	Byte OpCodeINCAbsX();

	Byte OpCodeINX();
	Byte OpCodeINY();

	Byte OpCodeJMPAbs();
	Byte OpCodeJMPInd();

	Byte OpCodeJSR();

	Byte OpCodeLDAImm();
	Byte OpCodeLDAZero();
	Byte OpCodeLDAZeroX();
	Byte OpCodeLDAAbs();
	Byte OpCodeLDAAbsX();
	Byte OpCodeLDAAbsY();
	Byte OpCodeLDAIndX();
	Byte OpCodeLDAIndY();

	Byte OpCodeLDXImm();
	Byte OpCodeLDXZero();
	Byte OpCodeLDXZeroY();
	Byte OpCodeLDXAbs();
	Byte OpCodeLDXAbsY();

	Byte OpCodeLDYImm();
	Byte OpCodeLDYZero();
	Byte OpCodeLDYZeroX();
	Byte OpCodeLDYAbs();
	Byte OpCodeLDYAbsX();


	Byte OpCodeLSRAcc();
	Byte OpCodeLSRZero();
	Byte OpCodeLSRZeroX();
	Byte OpCodeLSRAbs();
	Byte OpCodeLSRAbsX();

	Byte OpCodeNOP();

	Byte OpCodeORAImm();
	Byte OpCodeORAZero();
	Byte OpCodeORAZeroX();
	Byte OpCodeORAAbs();
	Byte OpCodeORAAbsX();
	Byte OpCodeORAAbsY();
	Byte OpCodeORAIndX();
	Byte OpCodeORAIndY();

	Byte OpCodePHA();
	Byte OpCodePHP();

	Byte OpCodePLA();
	Byte OpCodePLP();

	Byte OpCodeROLAcc();
	Byte OpCodeROLZero();
	Byte OpCodeROLZeroX();
	Byte OpCodeROLAbs();
	Byte OpCodeROLAbsX();

	Byte OpCodeRORAcc();
	Byte OpCodeRORZero();
	Byte OpCodeRORZeroX();
	Byte OpCodeRORAbs();
	Byte OpCodeRORAbsX();

	Byte OpCodeRTI();
	Byte OpCodeRTS();

	Byte OpCodeSBCImm();
	Byte OpCodeSBCZero();
	Byte OpCodeSBCZeroX();
	Byte OpCodeSBCAbs();
	Byte OpCodeSBCAbsX();
	Byte OpCodeSBCAbsY();
	Byte OpCodeSBCIndX();
	Byte OpCodeSBCIndY();

	Byte OpCodeSEC();
	Byte OpCodeSED();
	Byte OpCodeSEI();

	Byte OpCodeSTAZero();
	Byte OpCodeSTAZeroX();
	Byte OpCodeSTAAbs();
	Byte OpCodeSTAAbsX();
	Byte OpCodeSTAAbsY();
	Byte OpCodeSTAIndX();
	Byte OpCodeSTAIndY();

	Byte OpCodeSTXZero();
	Byte OpCodeSTXZeroY();
	Byte OpCodeSTXAbs();

	Byte OpCodeSTYZero();
	Byte OpCodeSTYZeroX();
	Byte OpCodeSTYAbs();

	Byte OpCodeTAX();
	Byte OpCodeTAY();

	Byte OpCodeTSX();

	Byte OpCodeTXA();
	Byte OpCodeTXS();

	Byte OpCodeTYA();



#pragma endregion





};
