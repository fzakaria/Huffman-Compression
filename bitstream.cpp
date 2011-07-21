#include "bitstream.h"
#include <iostream>
#include <sstream>

BitStream::BitStream(TYPE type): m_type(type), m_paddingLength(0)
{
    switch (m_type)
    {
    case READING:
        {
            this->m_currentBitNum = 8;
            this->m_currentByte = 0;
            break;
        }
    case WRITING:
        {
            this->m_currentBitNum = 0;
            this->m_currentByte = 0;
            break;
        }
    default:
        break;
    }

}

void BitStream::InsertBits(std::string bits)
{
    for (unsigned int i = 0 ; i < bits.length(); i++)
    {
        char bitToAdd = bits[i];
        this->InsertBit(bitToAdd);
    }
}

void BitStream::InsertBit(char bit)
{
    if (bit != '0' && bit != '1')
    {
        std::cerr << "Invalid Bit character given" << std::endl;
        return;
    }

    if (bit == '0')
    {
        this->InsertBit((unsigned int)0);
    }
    else
    {
        this->InsertBit((unsigned int)1);
    }

}

void BitStream::InsertBit(unsigned int bit)
{
    bit &= 1; //sanity check to make sure it is only 0 or 1
    bit = bit << (7 - this->m_currentBitNum); //lets move the bit to the current position (if it's a one it matters onl)
    this->m_currentBitNum += 1;
    this->m_currentByte |= bit;

    if (this->m_currentBitNum > 7)
    {
        this->UpdateState();
    }
}

void BitStream::Flush()
{
    this->m_buffer.push_back(this->m_currentByte);
    this->m_currentByte = 0;
}

void BitStream::UpdateState()
{
    switch (this->m_type)
    {
    case READING:
        {
            char curr_char;
            this->m_stringstream->get(curr_char);
            this->m_currentByte = curr_char;
            this->m_currentBitNum = 0;
            break;
        }
    case WRITING:
        {
            this->m_currentBitNum = 0;
            this->Flush();
            break;
        }
    default:
        break;
    }
}

bool BitStream::isGood()
{
    if (this->m_type == WRITING)
        return true;

    if (this->m_currentBitNum > 7)
    {
        this->UpdateState();
    }

    this->m_stringstream->peek();
    bool streamState = this->m_stringstream->good();
    if (!streamState)
    {
        int a = 1;
    }
    bool paddingReached = this->m_paddingLength >= (7 - this->m_currentBitNum);
    return streamState || !paddingReached;

}

std::string BitStream::GetNextBit()
{
    if (this->m_currentBitNum > 7)
    {
        this->UpdateState();
    }

    this->m_stringstream->peek();
    if (this->m_stringstream->eof() && (this->m_paddingLength < (7 - this->m_currentBitNum)) )
    {
        this->m_stringstream->clear();
    }

    int bit = this->m_currentByte >> (7 - this->m_currentBitNum);
    bit = bit & 1; //apply mask to get rid of everything but first bit
    this->m_currentBitNum += 1;

    if (bit)
    {
        return "1";
    }
    else
    {
        return "0";
    }
}