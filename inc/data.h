/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Data Management Class for IDA API Header
 */

#include "config.h"
#include <ecwrapper.h>
//#include <TRANSFERPROTOCOL>


Class Data{
	public:
		Data(configuration config);
		int insert(string filepath, vector<string> locations);
		int remove(string filepath, vector<string> locations);
		int get(string filepath, vector<string> locations);

	private:
		int bufsize;
		int filesize;
		string cachePath;
		int fileEncode();
		int fileDecode();
		int chunksSend();
		int chunksDownload();
};

