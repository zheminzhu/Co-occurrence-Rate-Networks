CC = g++ -std=c++11
CFLAGS = -Wall -c
LFLAGS = -Wall
DEBUG = -g
LIBS = liblinear/liblinear.so.1
OBJS = Corpus.o CPT.o CR.o DecodeModel.o IndexedCorpus.o Indices.o Result.o SVRLinearModel.o Template.o \
TrainModel.o Utils.o ViterbiDecoder.o

all: lib train decode
	
train: $(OBJS) $(LIBS)
	$(CC) $(LFLAGS) $(OBJS) -o train train.cpp -lrt $(LIBS)
	
decode: $(OBJS) $(LIBS)
	$(CC) $(LFLAGS) $(OBJS) -o decode decode.cpp -lrt $(LIBS)

lib:
	make -C liblinear lib
	sudo cp liblinear/liblinear.so.1 /usr/lib/
		
Corpus.o: Corpus.cpp Corpus.h
	$(CC) $(CFLAGS) -o Corpus.o Corpus.cpp 
	
CPT.o: CPT.cpp CPT.h
	$(CC) $(CFLAGS) -o CPT.o CPT.cpp
	
CR.o: CR.cpp CR.h
	$(CC) $(CFLAGS) -o CR.o CR.cpp	
	
DecodeModel.o: DecodeModel.cpp DecodeModel.h
	$(CC) $(CFLAGS) -o DecodeModel.o DecodeModel.cpp
	
IndexedCorpus.o: IndexedCorpus.cpp IndexedCorpus.h
	$(CC) $(CFLAGS) -o IndexedCorpus.o IndexedCorpus.cpp	
	
Indices.o: Indices.cpp Indices.h
	$(CC) $(CFLAGS) -o Indices.o Indices.cpp
	
Result.o: Result.cpp Result.h
	$(CC) $(CFLAGS) -o Result.o Result.cpp	
	
SVRLinearModel.o: SVRLinearModel.cpp SVRLinearModel.h
	$(CC) $(CFLAGS) -o SVRLinearModel.o SVRLinearModel.cpp
	
Template.o: Template.cpp Template.h
	$(CC) $(CFLAGS) -o Template.o Template.cpp
	
TrainModel.o: TrainModel.cpp TrainModel.h Utils.h
	$(CC) $(CFLAGS) -o TrainModel.o TrainModel.cpp	
	
Utils.o: Utils.cpp Utils.h
	$(CC) $(CFLAGS) -o Utils.o Utils.cpp
	
ViterbiDecoder.o: ViterbiDecoder.cpp ViterbiDecoder.h
	$(CC) $(CFLAGS) -o ViterbiDecoder.o ViterbiDecoder.cpp	
	
clean:
	rm -f *~ *.o train decode
	make -C liblinear clean