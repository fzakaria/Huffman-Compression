#ifndef HUFFMANCODEC_H
#define HUFFMANCODEC_H

#include <string>
#include <fstream>
#include <string>
#include <map>
#include <vector>


#define ASCII_LENGTH 256
class HuffmanCodec
{
public:
    HuffmanCodec(const std::string & inputFile, const std::string & outputFile);
    virtual ~HuffmanCodec();
    virtual void PerformAction() = 0;

protected:
    virtual void Init(const std::string & inputFile, const std::string & outputFile);
    virtual void Encode();
    virtual void Decode();

    virtual void BuildASCIICount() = 0;

    virtual void BuildHuffmanCodes();
    virtual std::string GetHuffmanCode(char data);
    virtual std::istream & GetInputStream(bool reset = true);

    virtual void WriteBufferToFile(const std::vector<unsigned char> & buffer);

    std::ifstream m_inputFileStream;
    std::ofstream m_outputFileStream;

    unsigned long m_asciiCount[ASCII_LENGTH];
    std::map<std::string, std::string> m_huffmanCodes;
};
#endif