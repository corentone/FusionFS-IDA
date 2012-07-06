/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Data Management Class for IDA API Header
 */

#include "metadata.h"
#include "config.h"
#include <ecwrapper.h>
//#include <TRANSFERPROTOCOL>


class Data{
	public:
		Data(configuration * config);
		int insert(std::string filepath);
		int remove(std::string filepath);
		int get(std::string filepath, std::vector<std::string> locations);

	private:
		configuration * config;
		Metadata * meta;
		std::string cachePath;
		int fileEncode(std::string filepath);
		int fileDecode(std::string filepath);
		int chunksSend(std::string hashFile, chunksLocations * locations);
		//int chunksDownload();
		int ECLibraryInit(ecFunctions * ec);
		
};

//Threads Funcs
void *threadSendFunc(void * args);




//TODO Define the way to share with Metadata a structure containing the locations and ports
struct threadArgs{
		std::string chunkPath;
		std::string remoteHost;
		std::string remotePort;
};
