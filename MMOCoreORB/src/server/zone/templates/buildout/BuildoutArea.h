#ifndef BUILDOUTAREA_H_
#define BUILDOUTAREA_H_

#include "engine/engine.h"

class BuildoutArea : public Object {
	String	name;
	float	x1;
	float	z1;
	float	x2;
	float	z2;
	bool useClipRect;
	float	clipRectX1;
	float	clipRectZ1;
	float	clipRectX2;
	float	clipRectZ2;
	int		envFlags;
	int		envFlagsExclude;
	bool	useOrigin;
	float	originX;
	float	originZ;
	float	compositeX1;
	float	compositeZ1;
	float	compositeX2;
	float	compositeZ2;
	String	compositeName;
	bool	isolated;
	bool	allowMap;
	bool	internal;

	//internal use
public:
	uint64 buildingObjectId;

public:
	BuildoutArea() : Object(), name(""), allowMap(false), internal(false) {

	}

	BuildoutArea(const BuildoutArea& boa) : Object() {
		name = boa.name;
		buildingObjectId = boa.buildingObjectId;
	}

	BuildoutArea& operator= (const BuildoutArea& boa) {
		if (this == &boa)
			return *this;

		name = boa.name;
		buildingObjectId = boa.buildingObjectId;

		return *this;
	}

	void parse(DataTableRow* data) {
		data->getValue(0, name);
		data->getValue(1, x1);
		data->getValue(2, z1);
		data->getValue(3, x2);
		data->getValue(4, z2);
		data->getValue(5, useClipRect);
		data->getValue(6, clipRectX1);
		data->getValue(7, clipRectZ1);
		data->getValue(8, clipRectX2);
		data->getValue(9, clipRectZ2);
		data->getValue(10, envFlags);
		data->getValue(11, envFlagsExclude);
		data->getValue(12, useOrigin);
		data->getValue(13, originX);
		data->getValue(14, originZ);
		data->getValue(15, compositeX1);
		data->getValue(16, compositeZ1);
		data->getValue(17, compositeX2);
		data->getValue(18, compositeZ2);
		data->getValue(19, compositeName);
		data->getValue(20, isolated);
		data->getValue(21, allowMap);
		data->getValue(22, internal);

	}

	String getName() {
		return name;
	}

	float getX1() {
		return x1;
	}

	float getX2() {
		return x2;
	}

	float getZ1() {
		return z1;
	}

	float getZ2() {
		return z2;
	}

	String getCompositeName() {
		return compositeName;
	}

	float getCompositeX1() {
		return compositeX1;
	}

	float getCompositeX2() {
		return compositeX2;
	}

	float getCompositeZ1() {
		return compositeZ1;
	}

	float getCompositeZ2() {
		return compositeZ2;
	}

};


#endif
