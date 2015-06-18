/*
 * WeaponObjectMEssage6.h
 *
 *  Created on: 01/05/2012
 *      Author: victor
 */

#ifndef WEAPONOBJECTMESSAGE6_H_
#define WEAPONOBJECTMESSAGE6_H_

#include "engine/engine.h"
#include "TangibleObjectMessage6.h"

class WeaponObjectMessage6 : public TangibleObjectMessage6 {
public:
	WeaponObjectMessage6(TangibleObject* tano)
			: TangibleObjectMessage6(tano, 0x5745414F) {

		insertByte(0x06);
		insertInt(0);
		insertShort(0x04);

		insertByte(0);
		insertShort(0);
		insertFloat(0);

		setSize();
	}

};


#endif /* WEAPONOBJECTMESSAGE6_H_ */
