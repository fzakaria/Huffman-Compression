#include <vector>
#include <string>


class BitStream
{
public:
    enum TYPE
    {
        READING,
        WRITING,
    };
    BitStream(TYPE type);
    virtual void InsertBits(std::string bits);
    virtual void InsertBit(char bit); //only will recognize '0' or '1'
    virtual void InsertBit(unsigned int bit); //only recognizes if it is 0 or one
    virtual void Flush();
    virtual bool isGood();

    virtual std::vector<unsigned char> GetBuffer() const { return this->m_buffer; }
    virtual unsigned int GetPaddingLength() const { return (7 - this->m_currentBitNum); }
    virtual void SetPaddingLength(unsigned int padd){ this->m_paddingLength = padd; }
    virtual std::string GetNextBit();
    virtual void SetInputStream(std::istream & ss) { this->m_stringstream = &ss; }

private:
    void UpdateState();

    TYPE m_type;
    std::istream * m_stringstream;
    unsigned int m_paddingLength;
    unsigned int m_currentBitNum;
    unsigned char m_currentByte;
    std::vector<unsigned char> m_buffer;
};