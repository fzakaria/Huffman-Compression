#include "huffmantree.h"
#include <iostream>

HuffmanTree::HuffmanTree():m_root(NULL)
{

}

HuffmanTree::~HuffmanTree()
{
    if (this->m_root) delete this->m_root;
}

void HuffmanTree::BuildTree(unsigned long ascii_count[])
{
    //we know the length is 256 since it's ASCII. Let's create the min-queue
    for (int i = 0 ; i < 256; ++i)
    {
        char current_char = (char)i;
        unsigned int current_count = ascii_count[i];
        if (current_count == 0)
        {
            continue;
        }
        HuffmanNode *newNode = new HuffmanNode(current_count, current_char);
        this->m_pqueue.push(newNode);
    }

    if (this->m_pqueue.empty())
    {
        std::cerr << "[HuffmanTree] Priority queue is empty. Trying to encode Empty file perhaps?" <<std::endl;
        return;
    }
    else if (this->m_pqueue.size() == 1)
    {
        this->m_root = this->m_pqueue.top();
        this->m_pqueue.pop();
        this->AssignBinaryCodes(this->m_root, "0");
        return;
    }
    else
    {
        while (this->m_pqueue.size() > 1)
        {
            HuffmanNode * left_child = this->m_pqueue.top();
            left_child->IncreaseBitCountByZero();
            this->m_pqueue.pop();//calls destructor but it's a pointer so no biggie


            HuffmanNode * right_child = this->m_pqueue.top();
            right_child->IncreaseBitCountByOne();
            this->m_pqueue.pop();

            HuffmanNode * parent_node = new HuffmanNode(left_child, right_child);
            this->m_pqueue.push(parent_node);
        }

        if (this->m_root)
        {
            delete this->m_root;
        }

        this->m_root = this->m_pqueue.top();
        this->m_pqueue.pop();
        this->AssignBinaryCodes(this->m_root, "");
        return;
    }

}

std::map<std::string, std::string> HuffmanTree::GetHuffmanCodes() const
{
    return this->m_codeMap;
}


void HuffmanTree::AssignBinaryCodes(HuffmanNode * node, std::string bitCount)
{
    node->IncreaseBitCount(bitCount);
    HuffmanNode * left = (HuffmanNode * )node->GetLeftChild();
    HuffmanNode * right = (HuffmanNode * )node->GetRightChild();

    if (left != NULL)
    {
        left->SetBitCount(node->GetBitCount());
        this->AssignBinaryCodes(left, "0");
    }
    if (right != NULL)
    {
        right->SetBitCount(node->GetBitCount());
        this->AssignBinaryCodes(right, "1");
    }
    //lets add it to the map now as a saving
    if (node->IsLeafNode())
    {
        this->m_codeMap.insert( std::pair<std::string, std::string>(node->GetString(), node->GetBitCount()) );
    }

}

Node::Node()
{
    this->m_rightChild = NULL;
    this->m_leftChild = NULL;
    this->m_parent = NULL;
}

Node::Node(Node * left, Node * right)
{
    this->m_leftChild = left;
    this->m_rightChild = right;
    left->SetParent(this);
    right->SetParent(this);
}

Node::~Node()
{
    if (this->m_leftChild) delete this->m_leftChild;
    if (this->m_rightChild) delete this->m_rightChild;
}


HuffmanNode::HuffmanNode(): Node(), m_count(0), m_string('\0'), m_bitCount("")
{

}

HuffmanNode::HuffmanNode(unsigned int count, char data): Node(), m_count(count), m_string(1, data), m_bitCount("")
{
}

HuffmanNode::HuffmanNode(unsigned int count, std::string value): Node(), m_count(count), m_string(value), m_bitCount("")
{
}

HuffmanNode::HuffmanNode(HuffmanNode * left, HuffmanNode * right): Node(left, right)
{
    this->m_count = left->GetCount() + right->GetCount();
    this->m_string = left->GetString() + right->GetString();
}

HuffmanNode::~HuffmanNode()
{
}

void HuffmanNode::IncreaseBitCountByOne()
{
    this->m_bitCount = this->m_bitCount + "1";
}

void HuffmanNode::IncreaseBitCountByZero()
{
    this->m_bitCount = this->m_bitCount + "0";
}
