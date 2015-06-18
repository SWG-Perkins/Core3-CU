#include "TOCFile.h"

#include "TOCArchive.h"
#include "engine/engine.h"

TOCFile::TOCFile(TOCArchive* archive) {
	tocArchive = archive;

}

TOCFile::~TOCFile() {
}

void TOCFile::read(const String& path) {
	setLoggingName("TOCFile " + path);
	setLogging(true);

	File* file = new File(path);

	FileInputStream fileStream(file);

	if (!file->exists()) {
		error("File does not exist.");
		delete file;
		return;
	}

	readHeader(&fileStream, path);

	fileStream.close();

	delete file;
}

void TOCFile::readHeader(FileInputStream* fileStream, const String& path) {

	TOCFileHeader* tocHeader = new TOCFileHeader(path);
	fileStream->read((byte*) &tocHeader->token, sizeof(tocHeader->token));
	fileStream->read((byte*) &tocHeader->version, sizeof(tocHeader->version));
	fileStream->read((byte*) &tocHeader->tocCompressor, sizeof(tocHeader->tocCompressor));
	fileStream->read((byte*) &tocHeader->fileNameBlockCompressor, sizeof(tocHeader->fileNameBlockCompressor));
	fileStream->read((byte*) &tocHeader->unusedOne, sizeof(tocHeader->unusedOne));
	fileStream->read((byte*) &tocHeader->unusedTwo, sizeof(tocHeader->unusedTwo));
	fileStream->read((byte*) &tocHeader->numberOfFiles, sizeof(tocHeader->numberOfFiles));
	fileStream->read((byte*) &tocHeader->sizeOfTOC, sizeof(tocHeader->sizeOfTOC));
	fileStream->read((byte*) &tocHeader->sizeOfNameBlock, sizeof(tocHeader->sizeOfNameBlock));
	fileStream->read((byte*) &tocHeader->uncompSizeOfNameBlock, sizeof(tocHeader->uncompSizeOfNameBlock));
	fileStream->read((byte*) &tocHeader->numberOfTreeFiles, sizeof(tocHeader->numberOfTreeFiles));
	fileStream->read((byte*) &tocHeader->sizeOfTreeFileNameBlock, sizeof(tocHeader->sizeOfTreeFileNameBlock));

	unsigned long blockSize = tocHeader->sizeOfTreeFileNameBlock;
	byte* theBytes = new byte[tocHeader->sizeOfTreeFileNameBlock];
	fileStream->read(theBytes, blockSize);

	tocArchive->tocHeader.add(tocHeader);

	// Read the file paths strings.
	readNullTermString(theBytes, tocHeader);

	readEntries(fileStream, tocHeader);
}

void TOCFile::readFilePaths(FileInputStream* fileStream) {
	// Unused.
}

void TOCFile::readNullTermString(byte* buffer, TOCFileHeader* tocHeader) {
	byte* curr = buffer;
	byte* prev = buffer;
	for (int i = 0; i < tocHeader->numberOfTreeFiles; ++i)
	{
		while (*curr != 0)
		{
			++curr;
		}

		String treFileName((char*) prev, curr - prev);


		tocHeader->treFileNames.add(treFileName);

		++curr;
		prev = curr;
	}

	delete [] buffer;
}

void TOCFile::readEntries(FileInputStream* fileStream, TOCFileHeader* tocHeader) {
	byte* theBytes = tocArchive->uncompress(fileStream, tocHeader->tocCompressor, tocHeader->sizeOfTOC, tocHeader->sizeOfTOC);
	readTOCEntriesUncomp(theBytes, tocHeader);

}

void TOCFile::readTOCEntriesUncomp(byte* buffer, TOCFileHeader* tocHeader) {
	ObjectInputStream* objInputStream = new ObjectInputStream((char*) buffer, tocHeader->sizeOfTOC);
	for (int i = 0; i < tocHeader->numberOfFiles; ++i)
	{
		TOCEntry* pToc = new TOCEntry();
		pToc->compressor = objInputStream->readByte();
		pToc->unused = objInputStream->readByte();
		pToc->treeFileIndex = objInputStream->readShort();
		pToc->crc = objInputStream->readInt();
		pToc->fileNameOffset = objInputStream->readInt();
		pToc->offset =  objInputStream->readInt();
		pToc->length =  objInputStream->readInt();
		pToc->compressedLength = objInputStream->readInt();

		tocHeader->tocEntry.add(pToc);
	}

	delete objInputStream;
}
