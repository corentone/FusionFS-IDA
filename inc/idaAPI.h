#include "../inc/metadata.h"
#include "../inc/data.h"

class idaAPI {
	public:
		idaAPI();
		idaAPI(config configuration);
		int insert(string filepath);
		int remove(string filepath);
		int get(string filepath);
};
