#ifndef TOCFILEHEADER_H_
#define TOCFILEHEADER_H_

#include "engine/engine.h"
#include "TOCEntry.h"

class TOCArchive;

namespace zlib {
#include <zlib.h>
}

class TOCFileHeader : public Object, public Logger {
public:
	Vector<String> treFileNames;
	Vector<TOCEntry*> tocEntry;

	static const int HEADERSIZE = 36;

	// Header
	int token;
	int version;
	byte tocCompressor;
	byte fileNameBlockCompressor;
	byte unusedOne;
	byte unusedTwo;
	int numberOfFiles;
	int sizeOfTOC;
	int sizeOfNameBlock;
	int uncompSizeOfNameBlock;
	int numberOfTreeFiles;
	int sizeOfTreeFileNameBlock;

	String fileName;

public:
	TOCFileHeader(const String& name) : Object(), Logger() {
		setLoggingName("TOCEntry");
		setLogging(true);
		fileName = name;
	}
};

#endif /* TREEFILE_H_ */
