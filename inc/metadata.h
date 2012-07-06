/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Metadata Class Header
 */

#include "config.h"
#include <string>
#include <vector>
#include <client.h>

class Metadata{
	public:
		Metadata(configuration config);
		int create(std::string filepath);
		int insert(std::string filepath);
		int remove(std::string remoteFilepath);
		int get(std::string remoteFilepath);

	private:
		//packets?
		std::vector<std::string> pkgList;
		configuration *config;
		ZHTClient *client;

};

