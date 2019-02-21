/*
* tools.h
*
* Created: 16.02.2019 00:21:36
*  Author: Markus Bröker<broeker.markus@googlemail.com>
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#define Set_Bit(var, bit) ((var) |= (1<<bit))
#define Clear_Bit(var, bit) ((var) &= ~(1<<bit))
#define Toggle_Bit(var, bit) ((var) ^= (1<<bit))
#define Check_Bit(var, bit) ((var>>bit) & 1)

#define BINARY_PATTERN "%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c"
#define toBinary(word) \
	(word & 0x8000) ? '1' : '0', \
	(word & 0x4000) ? '1' : '0', \
	(word & 0x2000) ? '1' : '0', \
	(word & 0x1000) ? '1' : '0', \
	(word & 0x800) ? '1' : '0', \
	(word & 0x400) ? '1' : '0', \
	(word & 0x200) ? '1' : '0', \
	(word & 0x100) ? '1' : '0', \
	(word & 0x80) ? '1' : '0', \
	(word & 0x40) ? '1' : '0', \
	(word & 0x20) ? '1' : '0', \
	(word & 0x10) ? '1' : '0', \
	(word & 0x8) ? '1' : '0', \
	(word & 0x4) ? '1' : '0', \
	(word & 0x2) ? '1' : '0', \
	(word & 0x1) ? '1' : '0'

#endif /* TOOLS_H_ */
