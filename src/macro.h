#pragma once

#define BIT(x) 1<<x
#define HighNibble(x) (x & 0xF0) >> 4
#define LowNibble(x) x & 0x0F
#define SignOverflow(a,b) short((short)a + b) > 0x80
#define CheckNegative(a) a & 0x80
