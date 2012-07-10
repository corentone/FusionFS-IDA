/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Information Dispersal Algorithm based FusionFS API Header
 */

#include "metadata.h"
#include "data.h"
#include "config.h"

class idaAPI {
	public:
		idaAPI();
		idaAPI(string configPath);
		int insert(string filepath);
		int remove(string filepath);
		int get(string filepath);
	private:
		Metadata *meta;
		std::vector<std::string> split(const std::string &s, char delim);
		std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};
