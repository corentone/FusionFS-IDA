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
		int insert(string filepath);
		int insert();
		int remove();
		int get();

	private:
		unsigned char * buffers;
		int bufsize;
		int filesize;
};

