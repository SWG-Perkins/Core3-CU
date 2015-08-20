#ifndef BUILDOUTROW_H_
#define BUILDOUTROW_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"

class DataTableRow;

class BuildoutRow : public Object {
public:
	BuildoutRow() : Object() {

	}


	uint32 sharedTemplateCrc;
	int cellIndex;
	float setX;
	float setY;
	float setZ;
	float setOrientationW;
	float setOrientationX;
	float setOrientationY;
	float setOrientationZ;
	float radius;
	int portalLayoutCrc;

public:
	void parse(DataTableRow* row, int offset) {
		row->getValue(offset + 0, sharedTemplateCrc);
		row->getValue(offset + 1, cellIndex);
		row->getValue(offset + 2, setX);
		row->getValue(offset + 3, setY);
		row->getValue(offset + 4, setZ);
		row->getValue(offset + 5, setOrientationW);
		row->getValue(offset + 6, setOrientationX);
		row->getValue(offset + 7, setOrientationY);
		row->getValue(offset + 8, setOrientationZ);
		row->getValue(offset + 9, radius);
		row->getValue(offset + 10, portalLayoutCrc);
	}
};


#endif
