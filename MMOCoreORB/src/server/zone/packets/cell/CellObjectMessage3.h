/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CELLOBJECTMESSAGE3_H_
#define CELLOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

class CellObjectMessage3 : public BaseLineMessage {
public:
	CellObjectMessage3(uint64 coId, int cellNumber)
			: BaseLineMessage(coId, 0x53434C54, 3, 0x05) {
		//BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt) {
		insertInt(0);
		insertShort(0); // STFName
		insertInt(0);
		insertShort(0); // STF
		insertInt(0); // custom name
		insertInt(0);
		insertByte(0x01);
		insertInt(cellNumber); //Cell Number, like 1,2,3,4 etc. NOT Object id.

		setSize();
	}
};
#endif /*CELLOBJECTMESSAGE3_H_*/
