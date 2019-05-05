#include "./stdafx.h"
#include "cpu.h"
#include "Memory.h"

#define OperandAddress m_PC + 1

CPU::CPU():m_Multiplier(1.0),m_CyclesPerFrame(Frequency/FrameRate * Multiplier),
m_PC(0),m_SP(0),m_Acc(0),m_X(0),m_Y(0),m_Ps(0)
{
	m_Ram = new Memory();
}

CPU::~CPU()
{
	delete m_Ram;
}

Byte CPU::OpcodeNull()
{
	printf("OpCode not implemented");
	return 0;
}

Byte CPU::OpCodeADCZero()
{

	Byte operand = m_Ram->readZero(OperandAddress);

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeADCZeroX()
{
	int8_t operand = m_Ram->readZeroIndexed(OperandAddress, m_X);
	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;
	m_PC += 2;

	return 4;

}

Byte CPU::OpCodeADCImm()
{
	int8_t operand = m_Ram->read(OperandAddress);
	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeADCAbs()
{
	int8_t operand = m_Ram->readAbsolute(OperandAddress);
	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;

	m_PC += 3;
	return 4;
}

Byte CPU::OpCodeADCAbsX()
{

	int8_t operand = m_Ram->readAbsoluteIndexed(OperandAddress, m_X);

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
	{
		return 5;
	}

	return 4;
}

Byte CPU::OpCodeADCAbsY()
{
	Byte operand = m_Ram->readAbsoluteIndexed(OperandAddress,m_Y);
	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeADCIndY()
{

	int8_t operand = m_Ram->readPostIndexed(OperandAddress,m_Y);

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;

	m_PC += 2;

	if (m_Ram->isPageBoundarySet())
	{
		return 6;
	}

	return 5;
}

Byte CPU::OpCodeADCIndX()
{
	uint8_t operand = m_Ram->readPreIndexed(OperandAddress, m_X);

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);
	m_Acc = sum;

	m_PC += 2;


	return 6;
}

Byte CPU::OpCodeANDImm()
{
	Byte operand = m_Ram->read(OperandAddress);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeANDAbs()
{
	Byte operand = m_Ram->readAbsolute(OperandAddress);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeANDAbsX()
{
	Byte operand = m_Ram->readAbsoluteIndexed(OperandAddress,m_X);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeANDAbsY()
{

	Byte operand = m_Ram->readAbsoluteIndexed(OperandAddress, m_Y);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeANDZero()
{
	Byte operand = m_Ram->readZero(OperandAddress);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 2;

	return 3;
}


Byte CPU::OpCodeANDZeroX()
{
	Byte operand = m_Ram->readZeroIndexed(OperandAddress,m_X);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeANDIndX()
{
	Byte operand = m_Ram->readPreIndexed(OperandAddress, m_X);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeANDIndY()
{
	Byte operand = m_Ram->readPreIndexed(OperandAddress, m_X);

	m_Acc &= operand;

	if (m_Acc == 0)
		setZeroFlag(true);
	else if (m_Acc & 0x80)
		setOverflowFlag(true);

	m_PC += 2;

	if (m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodeASLAcc()
{

	setCarryFlag(m_Acc & 0x80);
	m_Acc <<= 1;
	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeASLZero()
{
	Byte zeroAddress = m_Ram->read(OperandAddress);

	Byte operand = m_Ram->read(zeroAddress);
	setCarryFlag(operand & 0x80);

	operand <<= 1;

	m_Ram->write(zeroAddress, operand);

	setZeroFlag(operand == 0);
	setNegativeFlag(operand & 0x80);


	m_PC += 2;

	return 5;
}

Byte CPU::OpCodeASLZeroX()
{
	Byte zeroAddress = m_Ram->read(OperandAddress) + m_X;

	Byte operand = m_Ram->read(zeroAddress);
	setCarryFlag(operand & 0x80);

	operand <<= 1;

	m_Ram->write(zeroAddress, operand);

	setZeroFlag(operand == 0);
	setNegativeFlag(operand & 0x80);


	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeASLAbs()
{
	Address address = m_Ram->readHalfWord(OperandAddress);

	Byte operand = m_Ram->read(address);
	setCarryFlag(operand & 0x80);

	operand <<= 1;

	m_Ram->write(address, operand);

	setZeroFlag(operand == 0);
	setNegativeFlag(operand & 0x80);


	m_PC += 3;

	return 6;
}

Byte CPU::OpCodeASLAbsX()
{
	Address address = m_Ram->readHalfWord(OperandAddress) + m_X;

	Byte operand = m_Ram->read(address);
	setCarryFlag(operand & 0x80);

	operand <<= 1;

	m_Ram->write(address, operand);

	setZeroFlag(operand == 0);
	setNegativeFlag(operand & 0x80);


	m_PC += 3;

	return 7;
}

Byte CPU::OpCodeBCC()
{


	if (!getCarryFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if(m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;

}

Byte CPU::OpCodeBCS()
{
	if (getCarryFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeBEQ()
{
	if (getZeroFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeBITZero()
{

	Byte operand = m_Ram->readZero(OperandAddress);

	setZeroFlag(!(operand & m_Acc));
	setOverflowFlag(operand & 0x40);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeBITAbs()
{
	Byte operand = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(!(operand & m_Acc));
	setOverflowFlag(operand & 0x40);
	setNegativeFlag(operand & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeBMI()
{
	if (getNegativeFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeBNE()
{
	if (!getZeroFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeBPL()
{
	if (!getNegativeFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeBRK()
{
	setBreakFlag(1);
	return 7;
}

Byte CPU::OpCodeBVC()
{
	if (!getOverflowFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeBVS()
{
	if (getOverflowFlag())
	{

		Byte operand = m_Ram->read(OperandAddress);
		m_PC += 2;

		if (m_PC % 0xff + operand > 255)
		{
			m_PC += operand;
			return 4;
		}


		m_PC += operand;
		return  3;
	}

	return 2;
}

Byte CPU::OpCodeCLC()
{
	setCarryFlag(0);
	return 2;
}

Byte CPU::OpCodeCLD()
{
	setDecimalModeFlag(0);
	return 2;
}

Byte CPU::OpCodeCLI()
{
	setDisableInterruptFlag(0);
	return 2;
}

Byte CPU::OpCodeCLV()
{
	setOverflowFlag(0);
	return 2;
}

Byte CPU::OpCodeCMPImm()
{
	Byte operand = m_Ram->read(OperandAddress);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeCMPZero()
{
	Byte operand = m_Ram->readZero(OperandAddress);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeCMPZeroX()
{
	Byte operand = m_Ram->readZeroIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeCMPAbs()
{
	Byte operand = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeCMPAbsX()
{
	Byte operand = m_Ram->readAbsoluteIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeCMPAbsY()
{
	Byte operand = m_Ram->readAbsoluteIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeCMPIndX()
{
	Byte operand = m_Ram->readPreIndexed(OperandAddress, m_X);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeCMPIndY()
{
	Byte operand = m_Ram->readPostIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == operand);
	setCarryFlag(m_Acc >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	if (m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodeCPXImm()
{
	Byte operand = m_Ram->read(OperandAddress);

	setZeroFlag(m_X == operand);
	setCarryFlag(m_X >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeCPXZero()
{
	Byte operand = m_Ram->readZero(OperandAddress);

	setZeroFlag(m_X == operand);
	setCarryFlag(m_X >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeCPXAbs()
{
	Byte operand = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_X == operand);
	setCarryFlag(m_X >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeCPYImm()
{
	Byte operand = m_Ram->read(OperandAddress);

	setZeroFlag(m_Y == operand);
	setCarryFlag(m_Y >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeCPYZero()
{
	Byte operand = m_Ram->readZero(OperandAddress);

	setZeroFlag(m_Y == operand);
	setCarryFlag(m_Y >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeCPYAbs()
{
	Byte operand = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_Y == operand);
	setCarryFlag(m_Y >= operand);
	setNegativeFlag(operand & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeDECZero()
{
	Byte address = m_Ram->read(OperandAddress);

	m_Ram->write(address, m_Ram->read(address) - 1);

	m_PC += 2;

	return 5;
}

Byte CPU::OpCodeDECZeroX()
{
	Byte address = m_Ram->read(OperandAddress) + m_X;

	m_Ram->write(address, m_Ram->read(address) - 1);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeDECAbs()
{
	Address address = m_Ram->readHalfWord(OperandAddress);

	m_Ram->write(address, m_Ram->read(address) - 1);

	m_PC += 3;

	return 6;
}

Byte CPU::OpCodeDECAbsX()
{
	Byte address = m_Ram->readHalfWord(OperandAddress) + m_X;

	m_Ram->write(address, m_Ram->read(address) - 1);

	m_PC += 3;

	return 7;
}

Byte CPU::OpCodeDEX()
{
	m_X-= 1;

	m_PC += 1;

	return 2;

}

Byte CPU::OpCodeDEY()
{
	m_Y -= 1;

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeEORImm()
{
	m_Acc ^= m_Ram->read(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;
	return 2;
}

Byte CPU::OpCodeEORZero()
{
	m_Acc ^= m_Ram->readZero(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;
	return 3;
}

Byte CPU::OpCodeEORZeroX()
{
	m_Acc ^= m_Ram->readZeroIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;
	return 4;
}

Byte CPU::OpCodeEORAbs()
{
	m_Acc ^= m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;
	return 4;
}

Byte CPU::OpCodeEORAbsX()
{
	m_Acc ^= m_Ram->readAbsoluteIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;
	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeEORAbsY()
{
	m_Acc ^= m_Ram->readAbsoluteIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;
	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeEORIndX()
{
	m_Acc ^= m_Ram->readPreIndexed(OperandAddress, m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;


	return 6;
}

Byte CPU::OpCodeEORIndY()
{
	m_Acc ^= m_Ram->readPostIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	if(m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodeINCZero()
{

	Byte Address = m_Ram->read(OperandAddress);
	Byte value = m_Ram->updateValue(Address,1);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_PC += 2;

	return 5;
}

Byte CPU::OpCodeINCZeroX()
{
	Byte address = m_Ram->read(OperandAddress) + m_X;
	Byte value = m_Ram->updateValue(address, 1);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeINCAbs()
{
	Address address = m_Ram->readHalfWord (OperandAddress);
	Byte value = m_Ram->updateValue(address, 1);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_PC += 3;

	return 6;
}

Byte CPU::OpCodeINCAbsX()
{
	Address address = m_Ram->readHalfWord(OperandAddress) + m_X;
	Byte value = m_Ram->updateValue(address, 1);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_PC += 3;

	return 7;
}

Byte CPU::OpCodeINX()
{
	m_X += 1;

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeINY()
{
	m_Y += 1;

	setZeroFlag(m_Y == 0);
	setNegativeFlag(m_Y & 0x80);

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeJMPAbs()
{
	m_PC = m_Ram->readAbsolute(OperandAddress);

	return 1;
}

Byte CPU::OpCodeJMPInd()
{

	m_PC = m_Ram->readHalfWord(m_Ram->readHalfWord(OperandAddress));
	return 1;
}

Byte CPU::OpCodeJSR()
{

	m_Ram->write(m_SP, m_PC - 1);
	m_SP -= 2;

	m_PC = m_Ram->readAbsolute(OperandAddress);

	return 6;
}

Byte CPU::OpCodeLDAImm()
{
	m_Acc = m_Ram->read(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeLDAZero()
{
	m_Acc = m_Ram->readZero(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeLDAZeroX()
{
	m_Acc = m_Ram->readZeroIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeLDAAbs()
{
	m_Acc = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeLDAAbsX()
{
	m_Acc = m_Ram->readAbsoluteIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeLDAAbsY()
{
	m_Acc = m_Ram->readAbsoluteIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeLDAIndX()
{
	m_Acc = m_Ram->readPreIndexed(OperandAddress, m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;


	return 6;
}

Byte CPU::OpCodeLDAIndY()
{
	m_Acc = m_Ram->readPostIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	if (m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodeLDXImm()
{
	m_X = m_Ram->read(OperandAddress);

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeLDXZero()
{
	m_X = m_Ram->readZero(OperandAddress);

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeLDXZeroY()
{
	m_X = m_Ram->readZeroIndexed(OperandAddress,m_Y);

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeLDXAbs()
{
	m_X = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeLDXAbsY()
{
	m_X = m_Ram->readAbsoluteIndexed(OperandAddress,m_Y);

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeLDYImm()
{
	m_Y = m_Ram->read(OperandAddress);

	setZeroFlag(m_Y == 0);
	setNegativeFlag(m_Y & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeLDYZero()
{
	m_Y = m_Ram->readZero(OperandAddress);

	setZeroFlag(m_Y == 0);
	setNegativeFlag(m_Y & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeLDYZeroX()
{
	m_Y = m_Ram->readZeroIndexed(OperandAddress,m_X);

	setZeroFlag(m_Y == 0);
	setNegativeFlag(m_Y & 0x80);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeLDYAbs()
{
	m_Y = m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_Y == 0);
	setNegativeFlag(m_Y & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeLDYAbsX()
{
	m_Y = m_Ram->readAbsoluteIndexed(OperandAddress,m_X);

	setZeroFlag(m_Y == 0);
	setNegativeFlag(m_Y & 0x80);

	m_PC += 3;


	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeLSRAcc()
{

	setCarryFlag(m_Acc & 0x1);

	m_Acc >>= 1;

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);


	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeLSRZero()
{
	Byte address = m_Ram->read(OperandAddress);

	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x01);

	value >>= 1;

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);

	m_PC += 2;

	return 5;
}

Byte CPU::OpCodeLSRZeroX()
{
	Byte address = m_Ram->read(OperandAddress) + m_X;

	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x01);

	value >>= 1;

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeLSRAbs()
{
	Address address = m_Ram->readHalfWord(OperandAddress);

	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x01);

	value >>= 1;

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);

	m_PC += 3;

	return 6;
}

Byte CPU::OpCodeLSRAbsX()
{
	Address address = m_Ram->readHalfWord(OperandAddress) + m_X;

	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x01);

	value >>= 1;

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);

	m_PC += 3;

	return 7;
}

Byte CPU::OpCodeNOP()
{

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeORAImm()
{
	m_Acc |= m_Ram->read(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 2;
}

Byte CPU::OpCodeORAZero()
{
	m_Acc |= m_Ram->readZero(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeORAZeroX()
{
	m_Acc |= m_Ram->readZeroIndexed(OperandAddress,m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeORAAbs()
{
	m_Acc |= m_Ram->readAbsolute(OperandAddress);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeORAAbsX()
{
	m_Acc |= m_Ram->readAbsoluteIndexed(OperandAddress , m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeORAAbsY()
{
	m_Acc |= m_Ram->readAbsoluteIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 3;

	if (m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeORAIndX()
{
	m_Acc |= m_Ram->readPreIndexed(OperandAddress, m_X);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeORAIndY()
{
	m_Acc |= m_Ram->readPostIndexed(OperandAddress, m_Y);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 2;

	if (m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodePHA()
{

	m_Ram->write(m_SP, m_Acc);
	m_SP--;

	m_PC += 1;

	return 3;
}

Byte CPU::OpCodePHP()
{

	m_Ram->write(m_SP, m_Ps);
	m_SP--;

	m_PC += 1;

	return 3;
}

Byte CPU::OpCodePLA()
{
	m_SP++;
	m_Acc = m_Ram->read(m_SP);

	m_PC += 1;

	return 4;
}

Byte CPU::OpCodePLP()
{
	m_SP++;
	m_Ps = m_Ram->read(m_SP);

	m_PC += 1;

	return 4;
}

Byte CPU::OpCodeROLAcc()
{
	Byte oldCarry = getCarryFlag();

	setCarryFlag(m_Acc &  0x80);

	m_Acc <<= 1;
	m_Acc &= (0xFE | oldCarry);

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeROLZero()
{
	Byte oldCarry = getCarryFlag();

	Byte address = m_Ram->read(OperandAddress);
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value <<= 1;
	value &= (0xFE | oldCarry);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 2;

	return 5;
}

Byte CPU::OpCodeROLZeroX()
{
	Byte oldCarry = getCarryFlag();

	Byte address = m_Ram->read(OperandAddress) + m_X;
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value <<= 1;
	value &= (0xFE | oldCarry);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeROLAbs()
{
	Byte oldCarry = getCarryFlag();

	Address address = m_Ram->readHalfWord(OperandAddress);
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value <<= 1;
	value &= (0xFE | oldCarry);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 3;

	return 6;
}

Byte CPU::OpCodeROLAbsX()
{
	Byte oldCarry = getCarryFlag();

	Address address = m_Ram->readHalfWord(OperandAddress) + m_X;
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value <<= 1;
	value &= (0xFE | oldCarry);

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);

	m_PC += 3;

	return 7;
}

Byte CPU::OpCodeRORAcc()
{
	Byte oldCarry = getCarryFlag();

	setCarryFlag(m_Acc & 0x01);

	m_Acc >>= 1;
	m_Acc &= (0x7F | (oldCarry << 7));

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 1;

	return 2;
}

Byte CPU::OpCodeRORZero()
{
	Byte oldCarry = getCarryFlag();

	Byte address = m_Ram->read(OperandAddress);
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value >>= 1;
	value &= (0x7F | (oldCarry << 7));

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 2;

	return 5;
}

Byte CPU::OpCodeRORZeroX()
{
	Byte oldCarry = getCarryFlag() + m_X;

	Byte address = m_Ram->read(OperandAddress);
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value >>= 1;
	value &= (0x7F | (oldCarry << 7));

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeRORAbs()
{
	Byte oldCarry = getCarryFlag();

	Address address = m_Ram->readHalfWord(OperandAddress);
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value >>= 1;
	value &= (0x7F | (oldCarry << 7));

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 3;

	return 6;
}

Byte CPU::OpCodeRORAbsX()
{
	Byte oldCarry = getCarryFlag();

	Address address = m_Ram->readHalfWord(OperandAddress) + m_X;
	Byte value = m_Ram->read(address);

	setCarryFlag(value & 0x80);

	value >>= 1;
	value &= (0x7F | (oldCarry << 7));

	setZeroFlag(value == 0);
	setNegativeFlag(value & 0x80);

	m_Ram->write(address, value);


	m_PC += 3;

	return 7;
}

Byte CPU::OpCodeRTI()
{

	m_Ps = m_Ram->read(m_SP--);
	m_PC = m_Ram->read(m_SP--);
	return 6;
}

Byte CPU::OpCodeRTS()
{
	m_PC = m_Ram->read(m_SP--);
	m_PC--;
	return 6;
}

Byte CPU::OpCodeSBCImm()
{
	Byte operand = m_Ram->read(OperandAddress);

	if(m_Acc < operand)
	{

	}

	return 1;
}

Byte CPU::OpCodeSBCZero()
{
	Byte operand = ~(m_Ram->readZero(OperandAddress));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeSBCZeroX()
{
	Byte operand = ~(m_Ram->readZeroIndexed(OperandAddress,m_X));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeSBCAbs()
{
	Byte operand = ~(m_Ram->readAbsolute(OperandAddress));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeSBCAbsX()
{
	Byte operand = ~(m_Ram->readAbsoluteIndexed(OperandAddress,m_X));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 3;

	if(m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeSBCAbsY()
{
	Byte operand = ~(m_Ram->readAbsoluteIndexed(OperandAddress,m_Y));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 3;

	if(m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeSBCIndX()
{
	Byte operand = ~(m_Ram->readPreIndexed(OperandAddress,m_X));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeSBCIndY()
{
	Byte operand = ~(m_Ram->readPostIndexed(OperandAddress,m_Y));

	HalfWord sum = m_Acc + operand + getCarryFlag();

	setOverflowFlag( ~(operand ^ m_Acc) & (sum ^m_Acc)  & 0x80 );
	setCarryFlag(sum > 0xff);
	setZeroFlag(sum == 0);
	setNegativeFlag(sum & 0x80);

	m_Acc = sum;
	m_PC += 3;

	if(m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodeSEC()
{
	setCarryFlag(1);
	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeSED()
{
	setDecimalModeFlag(1);
	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeSEI()
{
	setDisableInterruptFlag(1);
	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeSTAZero()
{
	 Byte address = m_Ram->readZero(OperandAddress);
	 m_Ram->write(address, m_Acc);

	 m_PC += 2;
	 return 3;
}

Byte CPU::OpCodeSTAZeroX()
{
	Byte address = m_Ram->readZeroIndexed(OperandAddress,m_X);
	m_Ram->write(address, m_Acc);

	m_PC += 2;
	return 4;
}

Byte CPU::OpCodeSTAAbs()
{
	Byte address = m_Ram->readAbsolute(OperandAddress);
	m_Ram->write(address, m_Acc);

	m_PC += 3;
	return 4;
}

Byte CPU::OpCodeSTAAbsX()
{
	Byte address = m_Ram->readZeroIndexed(OperandAddress,m_X);
	m_Ram->write(address, m_Acc);

	m_PC += 3;
	if(m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeSTAAbsY()
{
	Byte address = m_Ram->readZeroIndexed(OperandAddress,m_Y);
	m_Ram->write(address, m_Acc);

	m_PC += 3;
	if(m_Ram->isPageBoundarySet())
		return 5;

	return 4;
}

Byte CPU::OpCodeSTAIndX()
{
	Byte address = m_Ram->readPreIndexed(OperandAddress,m_X);
	m_Ram->write(address, m_Acc);

	m_PC += 2;

	return 6;
}

Byte CPU::OpCodeSTAIndY()
{
	Byte address = m_Ram->readPostIndexed(OperandAddress,m_Y);
	m_Ram->write(address, m_Acc);

	m_PC += 3;
	if(m_Ram->isPageBoundarySet())
		return 6;

	return 5;
}

Byte CPU::OpCodeSTXZero()
{
	Byte address = m_Ram->readZero(OperandAddress);
	m_Ram->write(address, m_X);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeSTXZeroY()
{
	Byte address = m_Ram->readZeroIndexed(OperandAddress,m_Y);
	m_Ram->write(address, m_X);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeSTXAbs()
{
	Byte address = m_Ram->readAbsolute(OperandAddress);
	m_Ram->write(address, m_X);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeSTYZero()
{
	Byte address = m_Ram->readZero(OperandAddress);
	m_Ram->write(address, m_Y);

	m_PC += 2;

	return 3;
}

Byte CPU::OpCodeSTYZeroX()
{
	Byte address = m_Ram->readZeroIndexed(OperandAddress,m_X);
	m_Ram->write(address, m_Y);

	m_PC += 2;

	return 4;
}

Byte CPU::OpCodeSTYAbs()
{
	Byte address = m_Ram->readAbsolute(OperandAddress);
	m_Ram->write(address, m_Y);

	m_PC += 3;

	return 4;
}

Byte CPU::OpCodeTAX()
{
	m_X  =  m_Acc;

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeTAY()
{
	m_Y  =  m_Acc;

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeTSX()
{
	m_X  =  m_SP;

	setZeroFlag(m_X == 0);
	setNegativeFlag(m_X & 0x80);

	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeTXA()
{
	m_Acc  =  m_X;

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeTXS()
{
	m_SP  =  m_X;

	setZeroFlag(m_SP == 0);
	setNegativeFlag(m_SP & 0x80);

	m_PC += 1;
	return 2;
}

Byte CPU::OpCodeTYA()
{
	m_Acc  =  m_Y;

	setZeroFlag(m_Acc == 0);
	setNegativeFlag(m_Acc & 0x80);

	m_PC += 1;
	return 2;
}
