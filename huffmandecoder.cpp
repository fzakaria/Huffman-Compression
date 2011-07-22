#include "huffmandecoder.h"
#include "huffmantree.h"
#include "bitstream.h"
#include <stddef.h>
#include <sstream>
#include <iostream>

HuffmanDecoder::HuffmanDecoder(const std::string & inputFile, const std::string & outputFile):HuffmanCodec(inputFile, outputFile)
{
}

HuffmanDecoder::~HuffmanDecoder()
{
}

void HuffmanDecoder::PerformAction()
{
    this->Decode();
}

void HuffmanDecoder::Decode()
{
    this->BuildASCIICount();
    this->BuildHuffmanCodes();
    this->BuildDecodedFile();
}



void HuffmanDecoder::BuildDecodedFile()
{
    std::istream & buffer = this->GetInputStream(false); //don't reset where we left off
    InputBitStream inBitStream(buffer);
    unsigned int padding;
    buffer.read((char*)&padding, sizeof(padding));
    inBitStream.SetPaddingLength(padding);
    std::map<std::string, std::string>::iterator it;
    std::string currentCode = "";

    while (inBitStream.isGood())
    {
        currentCode += inBitStream.GetNextBit();
        if (inBitStream.isEOF())
            break;

        it = this->m_huffmanCodes.find(currentCode);
        if ( it != this->m_huffmanCodes.end())
        {//code exists!
            std::string decodedChar = it->second;
            currentCode = "";
            this->m_outputFileStream << decodedChar;
        }
    }
    this->m_outputFileStream.flush();

}

void HuffmanDecoder::BuildHuffmanCodes()
{
    HuffmanCodec::BuildHuffmanCodes();
    //we now want to swap the key and data values;
    std::map<std::string, std::string> swap_map;
    std::map<std::string,std::string>::iterator it;
    for (it = this->m_huffmanCodes.begin(); it != this->m_huffmanCodes.end(); it++)
    {
        std::string character = it->first;
        std::string huffmanCode = it->second;
        swap_map.insert(std::pair<std::string, std::string>(huffmanCode, character));
    }
    this->m_huffmanCodes = swap_map;
}


void HuffmanDecoder::BuildASCIICount()
{
    std::istream & buffer = this->GetInputStream();
    buffer.read((char*)this->m_asciiCount, sizeof(unsigned long)* ASCII_LENGTH);
}
