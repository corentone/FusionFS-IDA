/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Data Management Class for IDA API Header
 */

//#include "metadata.h"
#include "config.h"
#include <string>
#include <vector>
#include <ecwrapper.h>
//#include <TRANSFERPROTOCOL>


class Data{
	public:
		Data(configuration * config);
		int insert(std::string filepath, std::vector<std::string> locations);
		int remove(std::string filepath, std::vector<std::string> locations);
		int get(std::string filepath, std::vector<std::string> locations);

	private:
		configuration * config;
		//Metadata * meta;
		std::string cachePath;
		int fileEncode(std::string filepath);
		int fileDecode(std::string filepath);
		int chunksSend(std::vector<std::string> locations);
		//int chunksDownload();
		int ECLibraryInit(ecFunctions * ec);
		
};

//Threads Funcs
void *threadSendFunc(void * args);




//TODO Define the way to share with Metadata a structure containing the locations and ports
struct target{
		std::string localpath;
		std::string remotepath;
		std::string remoteHost;
		std::string remotePort;
};
