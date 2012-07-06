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

typedef struct  {
	int number;
	std::vector<std::string> hosts;
	std::vector<std::string> ports;
} chunksLocations;

class Metadata{
	public:
		Metadata(configuration config);
		int create(std::string filepath);
		int insert();
		int remove();
		int get();
		chunksLocations * getLocations(int number, std::string filepath);

	private:
		//packets?
		std::vector<std::string> pkgList;
		configuration *config;
		ZHTClient *client;

};



