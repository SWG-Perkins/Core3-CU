/*
 * BuffObject.h
 *
 *  Created on: Nov 2, 2014
 *      Author: valkyra
 */

#ifndef BUFFOBJECT_H_
#define BUFFOBJECT_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"

class BuffObject : public Object {
protected:

	String emptyString;

	String buffName;
	String group1;
	String group2;
	int priority;
	float duration;

	String effect1Name;
	float effect1Value;
	String effect2Name;
	float effect2Value;
	String effect3Name;
	float effect3Value;
	String effect4Name;
	float effect4Value;
	String effect5Name;
	float effect5Value;

	String callBack;
	String particleEffect;

	bool debuff;

public:
	BuffObject() {
		buffName = "";
		group1 = "";
		group2 = "";
		priority = 0;
		duration = 0;
		effect1Name = "";
		effect2Name = "";
		effect3Name = "";
		effect4Name = "";
		effect5Name = "";

		effect1Value = 0;
		effect2Value = 0;
		effect3Value = 0;
		effect4Value = 0;
		effect5Value = 0;

		debuff = false;

		emptyString = "";
	}

	~BuffObject() {
	}

	void parseDataTableRow(DataTableRow* row) {
		row->getValue(0, buffName);
		row->getValue(1, group1);
		row->getValue(2, group2);
		row->getValue(4, priority);
		row->getValue(6, duration);
		row->getValue(7, effect1Name);
		row->getValue(8, effect1Value);
		row->getValue(9, effect2Name);
		row->getValue(10, effect2Value);
		row->getValue(11, effect3Name);
		row->getValue(12, effect3Value);
		row->getValue(13, effect4Name);
		row->getValue(14, effect4Value);
		row->getValue(15, effect5Name);
		row->getValue(16, effect5Value);
		row->getValue(18, callBack);
		row->getValue(19, particleEffect);
		row->getValue(21, debuff);
	}


	inline String& getBuffName() {
		return buffName;
	}

	inline String& getGroup1() {
		return group1;
	}

	inline String& getGroup2() {
		return group2;
	}

	inline int getPriority() {
		return priority;
	}

	inline float getDuration() {
		return duration;
	}

	inline String& getEffectName(int effectNumber) {

		switch (effectNumber) {
		case 1:
			return effect1Name;
			break;
		case 2:
			return effect2Name;
			break;
		case 3:
			return effect3Name;
			break;
		case 4:
			return effect4Name;
			break;
		case 5:
			return effect5Name;
			break;
		default:
			return emptyString;
			break;
		}
	}

	inline float getEffectValue(int effectNumber) {
		switch (effectNumber) {
		case 1:
			return effect1Value;
			break;
		case 2:
			return effect2Value;
			break;
		case 3:
			return effect3Value;
			break;
		case 4:
			return effect4Value;
			break;
		case 5:
			return effect5Value;
			break;
		default:
			return 0;
			break;
		}
	}

	inline String& getCallback() {
		return callBack;
	}

	inline String& getParticleEffect() {
		return particleEffect;
	}

	inline bool isDebuff() {
		return debuff;
	}
};

#endif /* BUFFOBJECT_H_ */
