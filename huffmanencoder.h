#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include "bitstream.h"
#include "huffmancodec.h"


class HuffmanEncoder : public HuffmanCodec
{
public:
    HuffmanEncoder(const std::string & inputFile, const std::string & outputFile);
    virtual ~HuffmanEncoder();

    virtual void PerformAction();

protected:
    virtual void Encode();
    virtual void WriteBufferToFile(const BitStream & bs);
    virtual void BuildASCIICount();
private:
    void BuildEncodedFile();
    void WriteHeaderToFile(const BitStream & bs);
};

#endif