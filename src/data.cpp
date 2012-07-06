/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Data Management Class for IDA API
 */

#include "../inc/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


Data::Data(configuration * config/*TODO, Metadata * meta*/){

	this->config = config;
	//TODO this.meta = meta;

}

int Data::insert(std::string filepath){
	this->fileEncode(filepath);
	
	chunksLocations * locations = this->meta->getLocations(this->config->k+this->config->m,filepath);
	
	this->chunksSend(this->meta->getHash(filepath), locations);
	return 0;
}

int Data::remove(std::string filepath){
	//TODO	
	//Order to remote node to delete FILES!
	return 0;
}

int Data::get(std::string filepath, std::vector<std::string> locations){
	//this->chunksDownload();
	this->fileDecode(filepath);
}

int Data::fileEncode(std::string filepath){

	//INPUTS: Filename to Encode, # data blocks (n), # parity blocks (m), size of buffer (in B)
	std::string filename = filepath;
	std::string filenameDest = this->config->cacheDirectory + "FileHashHere"; //TODO+ this.meta.getHash();
	int n = this->config->k;
	int m = this->config->m;
	int bufsize = this->config->bufsize;

	FILE *source;
	FILE *destination[n+m];
	FILE *destinationMeta;

	/* Initialize Ec Functions and Context */
	ecFunctions ec;
    ecContext context;

	this->ECLibraryInit(&ec);
	
	int rc = ec->init(n, m, &context);
	if (rc) {
		printf("Error:  %i\n", rc);
		exit(EXIT_FAILURE);
	}

	/* Allocate/define the appropriate number of buffers */
	void *buffers;
	ec->alloc(&buffers, bufsize, &bufsize, context);

	/* Open source file and destination files */
	source = fopen(filename.c_str(), "rb");
	if(!source){
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	int j;
	char strJ[30];
	std::string filenameDestJ;
	
	for (j = 0; j < n + m; j++) {
		sprintf(strJ, "%d", j);//convert J to std::string
		filenameDestJ = filenameDest + "." + strJ;
    	destination[j] = fopen(filenameDestJ.c_str(), "wb");
		if(!destination[j]){
			printf("ERROR: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
			}
	}

	/* Encode N*BUFSIZE bytes at a time then repeat until EOF */
	int bytesRead;
	while(!feof(source)){
		//1-read		
		bytesRead = fread(buffers,sizeof(unsigned char), bufsize*n, source);

		if(bytesRead < bufsize * n){//Padding(with 0s) if necessary
			memset((unsigned char *) buffers + bytesRead, 0, bufsize*n - bytesRead);
		}
		
		//2-encode
    		ec->generate(buffers, bufsize, context);

		//3-Write
		for (j = 0; j < n + m; j++) {
    			fwrite((unsigned char *)buffers + j*bufsize, sizeof(unsigned char), bufsize, destination[j]);
    		}
	}

	/* Close files */
	fclose(source);
	for (j = 0; j < n + m; j++) {
		fclose(destination[j]);
	}

	/* Free allocated memory and destroy Context */
	ec->free(buffers, context);
    	ec->destroy(context);

	return 0;
}

void * threadSendFunc(void * args){
		struct target * target = (struct target *)args;
		//TODO ffs_sendfile("udt", target->remoteHost.c_str(), target->remotePort.c_str(), target->localpath.c_str(), target->remotepath.c_str());
	
	};

int Data::chunksSend(std::string fileHash, chunksLocations * locations){
	//TODO

	int n = this->config->k;
	int m = this->config->m;

	pthread_t threads[n+m];
	struct threadArgs[n+m];//argument structure
	
	char strJ[30];
	int j;
	for(j=0; j < n+m; j++){
	
		//1 fill the argument structure
		sprintf(strJ, "%d", j);//convert J to std::string
		threadArgs[j].chunkPath = this->config->cacheDirectory + filenameDest + "." + strJ;
		threadArgs[j].remoteHost = locations->hosts[j];
		threadArgs[j].remoteHost = locations->ports[j];
	
		//2 Start the thread
		pthread_create(&threads[j], NULL, &threadSendFunc, (void *)&args[j]);
	}

	for(j=0; j < n+m; j++){
		pthread_join(threads[j], NULL);
	}

	return 0;
}

int Data::fileDecode(std::string filepath){

	std::string filecacheSource = this->config->cacheDirectory + "FileHashHere"; //TODO+ this.meta.getHash();
	int n = this->config->k;
	int m = this->config->m;
	int bufsize = this->config->bufsize;
	int filesize = 101;//this->meta->getFilesize();TODO
	std::string filenameDest;

	/* Initialize Ec Functions and Context */
	ecFunctions ec;
    ecContext context;

	this->ECLibraryInit(&ec);
	
	int rc = ec->init(n, m, &context);
	if (rc) {
		printf("Error:  %i\n", rc);
		exit(EXIT_FAILURE);
	}

	/* Allocate/define the appropriate number of buffers */
	void *buffers;
	ec->alloc(&buffers, bufsize, &bufsize, context);


	/* Identify missing files and open files */
	//TODO Check files checksum + length to garantee correctness
	FILE *source[n+m];
	FILE *destination;

	int goodBufIds[m+n];
	int badBufIds[m+n];
	int ngood,nbad,i,j,tmp,unfinished,nBytes,towrite;
	ngood=0;
	nbad=0;

	destination = fopen(filepath.c_str(), "wb");
	if(!destination){
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	char strJ[30];//TODO not safe!
	std::string fileSourceJ;

	for (j = 0; j < n + m; j++) {
		sprintf(strJ, "%d", j);
		fileSourceJ = filecacheSource + strJ;
    	source[j] = fopen(fileSourceJ.c_str(), "rb");
    	
		if(!source[j]){
			if(errno != ENOENT && errno != EACCES){
			//Its normal not to find some files TODO Note: In a real application, the system should be aware of the failures, and should try in priority the known good parts.
				printf("ERROR: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			if(j < n) badBufIds[nbad++] = j;
		}
		else{
			goodBufIds[ngood] = j;

			ngood++;
		}
	}

	/* Shuffling */
	for(j=0; j < ngood; j++){
		if(goodBufIds[j] != j && goodBufIds[j] < n){
			i = j+1;
			while(goodBufIds[i] < n) i++;
			tmp = goodBufIds[i];
			memmove(goodBufIds+j+1, goodBufIds+j, sizeof(int)*(i-j));
			goodBufIds[j] = tmp;
		}
	}
	
	unfinished = 1;
	nBytes = 0;
	
	while (unfinished) {
		for (j = 0; j < ngood; j++) {
			fread((unsigned char*)buffers + j*bufsize,sizeof(unsigned char), bufsize, source[goodBufIds[j]]);
		}
	
		int buf_ids[256];
		memcpy(buf_ids, goodBufIds, n*sizeof(int));
		memcpy(buf_ids + n, badBufIds, nbad*sizeof(int));
		ec->recover(buffers, bufsize, buf_ids, nbad, context);
	
		/* Replace buffers */
		for (i = 0; i < n; i++) {
			if (buf_ids[i] != i) {
				j = i+1;
				while (buf_ids[j] != i) j++;
				memcpy((unsigned char*)buffers + bufsize*i, (unsigned char*)buffers + bufsize*j, bufsize);
				buf_ids[i] = i;
			}
		}
		
		if (nBytes + n*bufsize >= filesize) {
			towrite = filesize - nBytes;
			unfinished = 0;
		} else {
			towrite = n * bufsize;
		}
 		
		nBytes += towrite;
	
		/* Write buffers to file */
		fwrite((unsigned char*)buffers, sizeof(unsigned char), towrite, destination);
	}
	
	/* Close files */
	fclose(destination);
	for (j = 0; j < ngood; j++) {
		fclose(source[goodBufIds[j]]);
	}
	
	/* Free allocated memory and destroy Context */
	ec->free(buffers, context);
	ec->destroy(context);
    	
	return 0;
}

int Data::ECLibraryInit(ecFunctions * ec){

	switch(this->config->codingId){
	
		case 0: //should be replaced by a defined variable like GIBRALTAR
			ec_init_Gibraltar(ec);
			break;
	
		case 1: //should be replaced by a defined variable like JERASURERS
			ec_init_JerasureRS(ec);
			break;
			
		default:
			return 1;
	}
	return 0;
}
