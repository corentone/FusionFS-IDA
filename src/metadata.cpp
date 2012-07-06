/* 
 * Metadata Class for IDA API
 *
 * Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 * Author:  Pedro Alvarez-Tabio
 * Email:   palvare3@iit.edu
 */

#include "../inc/metadata.h"

using namespace std;

Metadata::Metadata(configuration config) {
	this->config = &config;
	client->initialize(config.path, config.member_path);
}

/*int Metadata::createMetadata(string filepath) {
	// TODO: I think that we don't need this method! Or what are we trying to do?

	//1- Read Config to fill the package
	Package package;
}*/

int Metadata::insert(string filepath) {

	// Stat the file to get file specific informations TODO: Error checking
	//struct stat st;
	//stat(filepath, &st);
	// Which ones do we get?
	
	vector<string> pkgList;
	// Send Metadata to ZHT
	client->insertMetadata(config->path, config->member_path, pkgList, filepath, config->codingId, config->k, config->m, config->bufsize);
}

int Metadata::remove(string remoteFilepath) {

	// TODO
	// Remove metadata from ZHT
	client->removeMetadata(remoteFilepath);
}

int Metadata::get(string remoteFilepath) {

	// Retrieve metadata from ZHT
	string metadata = client->getMetadata(remoteFilepath);

}
