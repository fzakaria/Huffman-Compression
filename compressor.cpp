// compressor.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "huffmandecoder.h"
#include "huffmanencoder.h"

int main(int argc, char * argv[])
{
    std::string inputFileName = "test.txt";
    std::string encodedFileName = "encoded.txt";
    std::string decodedFileName = "decoded.txt";
    std::cout << "Encoding file: " << inputFileName << " --> " << encodedFileName << std::endl;
    HuffmanEncoder * encoder = new HuffmanEncoder(inputFileName, encodedFileName);
    encoder->PerformAction();
    delete encoder;

    std::cout << "Decoding file: " << encodedFileName << " --> " << decodedFileName << std::endl;
    HuffmanDecoder * decoder = new HuffmanDecoder(encodedFileName, decodedFileName);
    decoder->PerformAction();
    delete decoder;

    std::cout << "Press any key to quit!" << std::endl;
    char t;
    std::cin >> t;
	return 0;
}

