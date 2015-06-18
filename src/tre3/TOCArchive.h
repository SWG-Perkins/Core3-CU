/*
 * TreeArchive.h
 *
 *  Created on: Apr 7, 2011
 *      Author: crush
 */

#ifndef TOCARCHIVE_H_
#define TOCARCHIVE_H_

#include "engine/engine.h"
#include "TreeFile.h"
#include "TOCFile.h"
#include "TreeArchive.h"
#include "TOCEntry.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/templates/DataArchiveStore.h"
#include "TOCFileHeader.h"

namespace zlib {
#include <zlib.h>
}

class TOCArchive : public Logger {

public:

	Vector<TOCFileHeader*> tocHeader;

	TOCArchive() {
		setLoggingName("TOCArchive");
		setLogging(true);
	}

	void unpackFile(const String& file) {
		TOCFile* tocFile = new TOCFile(this);
		tocFile->read(file);
		delete tocFile;
	}

	int indexOf(const String& filePath, TOCFileHeader* pHeader) {
		return searchTableOfContents(filePath.hashCode(), 0, pHeader->tocEntry.size() - 1, pHeader);
	}

	int searchTableOfContents(int crc, int left, int right, TOCFileHeader* pHeader) {
		if (left > right)
			return -1;

		int middle = (left + right) / 2;

		if (pHeader->tocEntry.get(middle)->crc == crc)
			return middle;

		if (pHeader->tocEntry.get(middle)->crc > crc)
			return searchTableOfContents(crc, left, middle - 1, pHeader);

		return searchTableOfContents(crc, middle + 1, right, pHeader);
	}

	byte* getBytes(const String& recordPath, int& size) {


		TOCFileHeader* pHeader = NULL;
		TOCEntry* pToc = NULL;

		for (int i=0; i < tocHeader.size(); ++i) {
			TOCFileHeader* pHeaderPossible = tocHeader.get(i);

			if (indexOf(recordPath, pHeaderPossible) != -1) {
				pHeader = pHeaderPossible;
				pToc = pHeader->tocEntry.get(indexOf(recordPath, pHeaderPossible));
				break;
			} else {
				continue;
			}
		}


		if (pToc == NULL || pHeader == NULL) {
			error("Error loading TOCEntry for " + recordPath);
			return NULL;
		}

		uint16 tocNameIdx = pToc->treeFileIndex;
		String treFile = pHeader->treFileNames.get(tocNameIdx);

		String path = ConfigManager::instance()->getTocPath();
		path += "/" + treFile;

		info("Opening TRE - " + path + " for " + recordPath, true);

		size = 0;

		File* file = new File(path);

		if (file == NULL) {
			error("Error loading file for " + recordPath);
			delete file;
			return NULL;
		}

		FileInputStream fileStream(file);

		int offset = pToc->offset;
		unsigned long uncompSize = pToc->length;
		unsigned long compSize = pToc->compressedLength;

		fileStream.skip(offset);

		byte* uncompressed = uncompress(&fileStream, pToc->compressor, uncompSize, compSize);

		size = uncompSize;

		fileStream.close();
		delete file;

		return uncompressed;
	}

	/**
	 * Uncompresses a block of data and returns it in a byte buffer.
	 * @param fileStream FileInputStream that has been advanced to the position of the compressedData and will be read for the compressedSize
	 */
	byte* uncompress(FileInputStream* fileStream, byte compressor, unsigned long uncompSize, unsigned long compSize) {
		byte* uncompressedData = new byte[uncompSize];

		switch (compressor) {
		case 2: //Data is compressed
		{
			byte* compressedData = new byte[compSize];

			fileStream->read(compressedData, compSize);

			int result = zlib::uncompress(uncompressedData, &uncompSize, compressedData, compSize);

			delete [] compressedData;
		}
		break;
		case 0: //Data is uncompressed
		default:
			fileStream->read(uncompressedData, uncompSize);
			break;
		}

		return uncompressedData;
	}

};


#endif /* TREEARCHIVE_H_ */
