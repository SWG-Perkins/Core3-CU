/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTPERMISSIONSMESSAGE_H_
#define CLIENTPERMISSIONSMESSAGE_H_

#include "engine/engine.h"

class ClientPermissionsMessage : public BaseMessage {
public:
	ClientPermissionsMessage() : BaseMessage(7) {
		insertShort(0x04);
		insertInt(0xE00730E5);
		insertByte(1); // can Login
		insertByte(1); // can create Normal character
		insertByte(1); // can create Jedi character
		insertByte(1); // can skip tutorial
		
	}

};

#endif /*CLIENTPERMISSIONSMESSAGE_H_*/
