#ifndef TOCFILE_H_
#define TOCFILE_H_

#include "engine/engine.h"
#include "TOCFileHeader.h"
#include "TOCEntry.h"

class TOCArchive;

class TOCFile : public Logger {
	TOCArchive* tocArchive;

	void readHeader(FileInputStream* fileStream, const String& path);
	void readFilePaths(FileInputStream* fileStream);
	void readNullTermString(byte* buffer, TOCFileHeader* tocHeader);
	void readEntries(FileInputStream* fileStream, TOCFileHeader* tocHeader);
	void readTOCEntriesUncomp(byte* buffer, TOCFileHeader* tocHeader);

	public:
	TOCFile(TOCArchive* archive);
	~TOCFile();

	void read(const String& path);
};

#endif /* TREEFILE_H_ */
