/*
 * DataArchive.h
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#ifndef DATAARCHIVESTORE_H_
#define DATAARCHIVESTORE_H_

#include "engine/util/Singleton.h"
#include "engine/log/Logger.h"
#include "system/thread/ReadWriteLock.h"
#include "system/thread/ReadLocker.h"
#include "system/thread/Locker.h"
#include "engine/util/iffstream/IffStream.h"

class TreeArchive;
class TOCArchive;

class DataArchiveStore : public Singleton<DataArchiveStore>, public Logger, public ReadWriteLock, public Object {
public:
	TreeArchive* treeDirectory;
	TOCArchive* tocDirectory;

	DataArchiveStore();

	~DataArchiveStore();

	byte* getData(const String& path, int& size);

	int loadTres(String& path, Vector<String>& treFilesToLoad);
	int loadTOCs(String& path, Vector<String>& tocFilesToLoad);

	IffStream* openIffFile(const String& fileName);

	TreeArchive* getTreeArchive() {
		return treeDirectory;
	}

	TOCArchive* getTocArchive() {
		return tocDirectory;
	}


};


#endif /* DATAARCHIVE_H_ */
