/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Metadata Class Header
 */

#include "config.h"
#include <client.h>

typedef struct {
	int number;
	std::vector<string> hosts;
	std::vector<std::string> ports;
} chunksLocations;

class Metadata{
	public:
		Metadata(configuration config);
		int create(std::string filepath);
		int insert(std::string filepath);
		int remove(std::string remoteFilepath);
		int get(std::string remoteFilepath);
		chunksLocations * getLocations(int number, std::string filepath);
		std::string getHash(std::string filepath);

	private:
		//packets?
		std::vector<std::string> pkgList;
		configuration *config;
		ZHTClient *client;

};



