#include <queue>
#include <string>
#include <vector>
#include <map>

class Node
{
public:
    Node();
    Node(Node * left, Node * right);
    virtual ~Node();

    virtual bool IsLeafNode() const { return (m_rightChild == NULL && m_leftChild == NULL); }

    virtual Node * GetRightChild() const { return m_rightChild; }
    virtual void SetRightChild( Node * right )  { m_rightChild = right; }

    virtual Node * GetLeftChild() const { return m_leftChild; }
    virtual void SetLeftChild( Node * left )  { m_leftChild = left; }

    virtual Node * GetParent() const { return m_parent; }
    virtual void SetParent( Node * parent )  { m_parent = parent; }

protected:
    Node * m_parent;
    Node * m_leftChild;
    Node * m_rightChild;
};

class HuffmanNode : public Node
{
public:
    HuffmanNode(unsigned int count, std::string data);
    HuffmanNode(unsigned int count, char data);
    HuffmanNode(HuffmanNode * left, HuffmanNode * right);
    HuffmanNode();

    virtual ~HuffmanNode();

    unsigned int GetCount() const { return m_count; }
    std::string GetString() const { return m_string; }

    std::string GetBitCount() const { return m_bitCount; }
    void SetBitCount(std::string count) { this->m_bitCount = count; }
    void IncreaseBitCount(std::string count) { this->m_bitCount += count; }

    void IncreaseBitCountByOne();
    void IncreaseBitCountByZero();

private:
    unsigned int m_count;
    std::string m_string;
    std::string m_bitCount;
};


struct compare 
{
    bool operator()(const HuffmanNode *  l, const HuffmanNode *  r) 
    {
        return l->GetCount() > r->GetCount();
    }
};

class HuffmanTree
{
public:
    HuffmanTree();
    virtual ~HuffmanTree();
    
    void BuildTree(unsigned long ascii_count[]);
    std::map<std::string, std::string> GetHuffmanCodes() const;

protected:

private:
    void AssignBinaryCodes(HuffmanNode * node, std::string bitCount);


    std::priority_queue<HuffmanNode * , std::vector<HuffmanNode * >, compare> m_pqueue;

    std::map<std::string, std::string> m_codeMap;
    HuffmanNode * m_root;
};


