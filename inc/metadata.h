/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Metadata Class Header
 */

#include "config.h"
#include <string>
#include <vector>
#include <zht>



class Metadata{
	public:
		Metadata(configuration config);
		int create(std::string filepath);
		int insert();
		int remove();
		int get();

	private:
		//packets?
		std::vector<std::string> pkgList;
		configuration *config;
		ZHTClient *client;

};

