#include "../inc/metadata.h"

using namespace std;

Metadata::Metadata(configuration config) {
	config(config);
}

int Metadata::createMetadata(string filepath) {
	// TODO: I think that we don't need this method! Or what are we trying to do?

	//1- Read Config to fill the package
	Package package;
	//2- Stat the file to get file specific informations

}

int Metadata::insert(string filepath) {
	vector<string> pkgList;
	//Send Metadata to ZHT
	client.insertMetadata(config.path, config.member_path, pkgList, filepath, config.codingId, config.k, config.m, config.bufsize);
}

int Metadata::remove(string filepath) {

	//TODO

	//remove metadata from ZHT

}

int Metadata::get() {

	//TODO

	//retrieve metadata from ZHT



}
