#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include "huffmancodec.h"

class HuffmanDecoder : public HuffmanCodec
{
public:
    HuffmanDecoder(const std::string & inputFile, const std::string & outputFile);
    virtual ~HuffmanDecoder();

    virtual void PerformAction();

protected:
    virtual void Decode();
    virtual void BuildASCIICount();
    virtual void BuildHuffmanCodes();
private:
    void BuildDecodedFile();
};

#endif