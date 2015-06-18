#ifndef STOPCLIENTEFFECTOBJECTMESSAGE_H_
#define STOPCLIENTEFFECTOBJECTMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

class StopClientEffectObjectMessage : public BaseMessage {
public:
	StopClientEffectObjectMessage(SceneObject* obj, const String& label) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xAD6F6B26);
		insertLong(obj->getObjectID());
		insertAscii(label);
		insertByte(0x01);
	}

};

#endif /*STOPCLIENTEFFECTOBJECTMESSAGE_H_*/
