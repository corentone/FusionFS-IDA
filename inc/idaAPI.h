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
		idaAPI(config configuration);
		int insert(string filepath);
		int remove(string filepath);
		int get(string filepath);
	private:
		Metadata *meta;
};
