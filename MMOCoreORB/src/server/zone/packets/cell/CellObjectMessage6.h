/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CELLOBJECTMESSAGE6_H_
#define CELLOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

class CellObjectMessage6 : public BaseLineMessage {
public:
	CellObjectMessage6(uint64 coId)
			: BaseLineMessage(coId, 0x53434C54, 6, 0x02) {

		//insertShort(1); //operand count
		//insertInt(0x42); // some const value it appears
		//insertInt(0x4A); //*shrug*
		insertInt(0x6E);
		insertInt(0);
		insertInt(0);

		setSize();

	}
};
#endif /*CELLOBJECTMESSAGE6_H_*/
