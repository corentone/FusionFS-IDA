/* Author:  Corentin Debains
 * Email:   cdebains@iit.edu
 *
 *
 * Data Management Class for IDA API
 */


Data::Data(configuration config){

	//TODO Load config

}

int Data::insert(string filepath, vector<string> locations){
	this.fileEncode(filepath);
	this.chunksSend(locations);
	return 0;
}

int Data::remove(string filepath, vector<string> locations){
	//TODO	
	//Order to remote node to delete FILES!
	return 0;
}

int Data::get(string filepath, vector<string> locations){
	this.chunksDownload();
	this.fileDecode();
}

int Data::fileEncode(){

	//INPUTS: Filename to Encode, # data blocks (n), # parity blocks (m), size of buffer (in B)
	char * filename = argv[1];
	char filenameDest[260];	
	int n = this.n;
	int m = this.m;
	int bufsize = this.bufsize;

	FILE *source;
	FILE *destination[n+m];
	FILE *destinationMeta;

	/* Initialize Ec Functions and Context */
	ecFunctions ec;
    ecContext context;

	ec_init_Gibraltar(&ec); //If Gibraltar
	//ec_init_JerasureRS(&ec); //if Jerasure Reed Solomon
	
	int rc = ec->init(n, m, &context);
	if (rc) {
		printf("Error:  %i\n", rc);
		exit(EXIT_FAILURE);
	}

	/* Allocate/define the appropriate number of buffers */
	void *buffers;
	ec->alloc(&buffers, bufsize, &bufsize, context);

	/* Open source file and destination files */
	source = fopen(filename, "rb");
	if(!source){
		printf("ERROR: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	int j;
	
	for (j = 0; j < n + m; j++) {
		sprintf(filenameDest, "./%s.%d", filename, j);
	    	destination[j] = fopen(filenameDest, "wb");
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

int Data::chunksSend(){
	//TODO

	//threadSTART HERE
	//int ffs_sendfile(const char *proto, const char *remote_ip, const char *server_port, const char *local_filename, const char *remote_filename);
	
	//thread JOIN HERE

	return 0;
}
