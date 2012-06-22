/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Metadata Class Header
 */

#include "config.h"


Class Metadata{
	public:
		Metadata(configuration config);
		int create(string filepath);
		int insert();
		int remove();
		int get();

	private:
		//packets?
		vector<string> pkgList;
		configuration *config;
		ZHTClient *client;

};

