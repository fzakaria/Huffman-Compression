#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <vector>
#include <string>

class BitStream
{
public:
    virtual ~BitStream();
    virtual bool isGood() const =0;
    virtual bool isEOF() const =0;

    virtual std::ios & GetStream() const { return m_stream; }

    virtual unsigned int GetPaddingLength() const { return m_paddingBitLength; }
    virtual void SetPaddingLength(unsigned int padd){ m_paddingBitLength = padd; }
protected:
    BitStream(std::ios & stream);
    
    unsigned int m_paddingBitLength;
    unsigned int m_currentBitNum;
    std::ios & m_stream;
    unsigned char m_currentByte;
private:
    BitStream();
    BitStream(const BitStream& copy);

};

class OutputBitStream: public BitStream
{
public:
    OutputBitStream(std::ostream & stream);
    virtual ~OutputBitStream();

    virtual void InsertBits(std::string bits);
    virtual void InsertBit(char bit); //only will recognize '0' or '1'
    virtual void InsertBit(unsigned int bit);//only recognizes 0 or non 0
    virtual void Flush();

    virtual bool isGood() const { return m_stream.good(); }
    virtual bool isEOF() const { return m_stream.eof(); }

    virtual std::ostream & GetStream() const { return dynamic_cast<std::ostream&>(m_stream); }

    friend std::ostream & operator<< (std::ostream &, const OutputBitStream &);
private:
    OutputBitStream();
    OutputBitStream(const OutputBitStream& copy);

};

class InputBitStream: public BitStream
{
public:
    InputBitStream(std::istream & stream);
    virtual ~InputBitStream();

    virtual std::string GetNextBit();

    virtual bool isGood() const;
    virtual bool isEOF() const;

    virtual std::istream & GetStream() const { return dynamic_cast<std::istream&>(m_stream); }
private:
    virtual void Consume();
    InputBitStream();
    InputBitStream(const InputBitStream& copy);
};

#endif