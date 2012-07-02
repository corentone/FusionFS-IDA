# Author:  Corentin Debains
# Email:   cdebains@iit.edu
#


CXX=g++
CFLAGS=-Xlinker -zmuldefs -Llib -L/usr/local/lib -Iinc
LFLAGS=-lstdc++ -lrt -lpthread -lm -lc -lprotobuf -lprotoc

OBJECTS=metadata.o data.o idaAPI.o

#tocheck
#.PHONY: clean ida


all:
	make ida


###ZHT Library Compilation and import
LFLAGS+=-lzht
zht: lib/ZHT/Makefile
	cd lib/ZHT && make
	cp lib/ZHT/lib/libzht.a lib/


###Erasure Code Wrapper Library Compilation and Library Import
LFLAGS+=-lecwrapper
CUDAINC=-I $(CUDA_INC_PATH)
CUDALIB=-L $(CUDA_LIB_PATH)
CFLAGS+=$(CUDAINC)
LFLAGS+=$(CUDALIB) 

ecwrapper: lib/ECwrapper/Makefile
	cd lib/ECwrapper && make
	cp lib/ECwrapper/lib/libecwrapper.a lib/
###





ida: ecwrapper src/ida.cpp $(OBJECTS)
	$(CXX) $(CFLAGS) src/ida.cpp -o bin/fu-fs $(LFLAGS)

PORT=5000
run: zht
	lib/ZHT/bin/server_zht $(PORT) lib/ZHT/neighbor lib/ZHT/zht.cfg



obj:
	mkdir -p obj

%.o: src/%.cpp obj
	$(CXX) $(CFLAGS) -c src/$*.cpp -o obj/$*.o $(LFLAGS)

# A special kind of rule:  These files don't need to be remade if they're
# out of date, just destroyed.
cache:  src/gib_cuda_checksum.cu
	rm -rf cache
	mkdir cache

clean:
	rm -rf obj cache
	
mrproper: clean
	rm -f lib/*.a
