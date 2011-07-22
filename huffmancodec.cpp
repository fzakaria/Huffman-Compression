#include "huffmancodec.h"
#include "huffmantree.h"
#include <iostream>
#include <sstream>

HuffmanCodec::HuffmanCodec(const std::string & inputFile, const std::string & outputFile)
{
    this->Init(inputFile, outputFile);
}

HuffmanCodec::~HuffmanCodec()
{
    this->m_inputFileStream.close();
    this->m_outputFileStream.close();
}

void HuffmanCodec::Init(const std::string & inputFile, const std::string & outputFile)
{
    //initialize it to 0
    for (int i = 0 ; i < ASCII_LENGTH; ++i)
    {
        this->m_asciiCount[i] = 0;
    }

    this->m_inputFileStream = std::ifstream(inputFile, std::ofstream::binary);
    if (!this->m_inputFileStream.is_open())
    {
        throw std::ifstream::failure("Could not open the input file");
    }

    this->m_outputFileStream = std::ofstream(outputFile, std::ofstream::binary);
    if (!this->m_outputFileStream .is_open())
    {
        throw std::ifstream::failure("Could not open the output file");
    }
}


void HuffmanCodec::Encode()
{
    std::cerr << "Unsupported function" << std::endl;
}

void HuffmanCodec::Decode()
{
    std::cerr << "Unsupported function" << std::endl;
}

std::string HuffmanCodec::GetHuffmanCode(char data)
{
    std::map<std::string,std::string>::iterator it;
    std::string key(&data,1);
    it = this->m_huffmanCodes.find(key);
    if (it == this->m_huffmanCodes.end())
    {
        std::cerr << "Invalid character not mapped in the map: " << data << std::endl;
        return "";
    }
    return (it)->second;
}

std::istream & HuffmanCodec::GetInputStream(bool reset)
{
    if (reset)
    {
        this->m_inputFileStream.clear();
        this->m_inputFileStream.seekg(0, std::ios::beg);
    }
    return this->m_inputFileStream;
}

void HuffmanCodec::WriteBufferToFile(const OutputBitStream & bs)
{
    this->m_outputFileStream << bs;
    this->m_outputFileStream.flush();
    this->m_outputFileStream.close();
}

void HuffmanCodec::BuildHuffmanCodes()
{
    HuffmanTree * treeP = new HuffmanTree();
    treeP->BuildTree(this->m_asciiCount);
    this->m_huffmanCodes = treeP->GetHuffmanCodes();
    delete treeP;
}