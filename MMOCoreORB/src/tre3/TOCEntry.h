#ifndef TOCENTRY_H_
#define TOCENTRY_H_

#include "engine/engine.h"

class TOCEntry : public Object, public Logger {
	// Entry
public:

	static const int ENTRYSIZE = 24;

	byte compressor;
	byte unused;
	uint16 treeFileIndex;
	uint32 crc;
	uint32 fileNameOffset;
	uint32 offset;
	uint32 length;
	uint32 compressedLength;

public:
	TOCEntry() : Object(), Logger() {
		setLoggingName("TOCEntry");
		setLogging(true);
	}

};


#endif /* TREEFILERECORD_H_ */
