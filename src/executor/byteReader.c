#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/commonType.h"

#include "byteReader.h"

static byte readByte(ByteReader *this);

static short readShort(ByteReader *this);

static int readInteger(ByteReader *this);

ByteReader *createByteReader(byte* code, u32 length, u32 pc) {
	if (code!=NULL && length>0) {
		ByteReader *byteReader = (ByteReader *)calloc(1, sizeof(ByteReader));
		if (byteReader!=NULL) {
			byteReader->code = code;
			byteReader->length = length;
			byteReader->pc = pc;

			byteReader->readByte = readByte;
			byteReader->readShort = readShort;
			byteReader->readInteger = readInteger;
		}
		return byteReader;
	}
	return NULL;
}

static byte readByte(ByteReader *this) {
	byte data = this->code[this->pc];
	this->pc++;
	return data;
}

static short readShort(ByteReader *this) {
	byte data1 = readByte(this);
	byte data2 = readByte(this);
	return (data1 << 8) | data2;
}

static int readInteger(ByteReader *this) {
	byte data1 = readByte(this);
	byte data2 = readByte(this);
	byte data3 = readByte(this);
	byte data4 = readByte(this);
	return (data1 << 24) | (data2 << 16) | (data2 << 8) | data1;
}
