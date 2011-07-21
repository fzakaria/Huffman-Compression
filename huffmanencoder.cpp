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
    std::istream & buffer = this->GetInputStream();
    char current_char;
    BitStream bstream(BitStream::WRITING);

    while (buffer.good())
    {
         buffer.get(current_char);
         if (buffer.eof())
             break;
         std::string binaryCode = this->GetHuffmanCode(current_char);
         bstream.InsertBits(binaryCode);
    }
    bstream.Flush();
    this->WriteBufferToFile(bstream);
}

void HuffmanEncoder::WriteBufferToFile(const BitStream & bs)
{
    this->WriteHeaderToFile(bs);
    HuffmanCodec::WriteBufferToFile(bs.GetBuffer());
}

void HuffmanEncoder::WriteHeaderToFile(const BitStream & bs)
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
