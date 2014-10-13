all: compressor
	g++ bitstream.o compressor.o huffmancodec.o huffmandecoder.o huffmanencoder.o huffmantree.o -o compressor

compressor: bitstream.o compressor.o huffmancodec.o huffmandecoder.o huffmanencoder.o huffmantree.o compressor.cpp
	g++ -c compressor.cpp

huffmandecoder.o: huffmancodec.o huffmantree.o bitstream.o huffmandecoder.cpp
	g++ -c huffmancodec.o huffmantree.o bitstream.o huffmandecoder.cpp

huffmanencoder.o: huffmancodec.o bitstream.o huffmantree.o huffmanencoder.cpp
	g++ -c huffmancodec.o huffmantree.o bitstream.o huffmanencoder.cpp

huffmancodec.o: bitstream.o huffmantree.o huffmancodec.cpp
	g++ -c huffmantree.o bitstream.o huffmancodec.cpp

huffmantree.o: huffmantree.cpp
	g++ -c huffmantree.cpp

bitstream.o: bitstream.cpp
	g++ -c bitstream.cpp

clean:
	rm -rf *o compressor
