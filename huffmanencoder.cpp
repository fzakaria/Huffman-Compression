#include "huffmanencoder.h"
#include "huffmantree.h"
#include <stddef.h>
#include <sstream>
#include <iostream>

HuffmanEncoder::HuffmanEncoder(const std::string & inputFile, const std::string & outputFile):HuffmanCodec(inputFile, outputFile)
{
}

HuffmanEncoder::~HuffmanEncoder()
{
}

void HuffmanEncoder::PerformAction()
{
    this->Encode();
}

void HuffmanEncoder::Encode()
{
    this->BuildASCIICount();
    this->BuildHuffmanCodes();
    this->BuildEncodedFile();
}



void HuffmanEncoder::BuildEncodedFile()
{
    std::istream & inputStream = this->GetInputStream();
    std::stringstream tempStream; //we need to write it to a temporary stream so that we can write header first
    char current_char;
    OutputBitStream outBitStream(tempStream);

    while (inputStream.good())
    {
         inputStream.get(current_char);
         if (inputStream.eof())
             break;
         std::string binaryCode = this->GetHuffmanCode(current_char);
         outBitStream.InsertBits(binaryCode);
    }
    outBitStream.Flush();
    this->WriteBufferToFile(outBitStream);
}

void HuffmanEncoder::WriteBufferToFile(const OutputBitStream & bs)
{
    this->WriteHeaderToFile(bs);
    HuffmanCodec::WriteBufferToFile(bs);
}

void HuffmanEncoder::WriteHeaderToFile(const OutputBitStream & bs)
{
    this->m_outputFileStream.write( (char*)(this->m_asciiCount), sizeof(unsigned long)*ASCII_LENGTH);
    
    unsigned int padding = bs.GetPaddingLength();
    this->m_outputFileStream.write((char*)&padding, sizeof(padding) );

    this->m_outputFileStream.flush();
}

void HuffmanEncoder::BuildASCIICount()
{
    std::istream & buffer = this->GetInputStream();
    char current_char;
    while (buffer.good())
    {
        buffer.get(current_char);
        if (buffer.eof())
            break;
        this->m_asciiCount[(int)current_char] += 1;
    }
}
