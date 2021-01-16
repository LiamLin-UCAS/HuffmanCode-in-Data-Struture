#include<iostream>
using namespace std;

struct chainNode
{
	treeNode* element;
	chainNode* next;
	chainNode() {
		this->element = NULL;
		this->next = NULL;
	};
	chainNode(treeNode* theElement) {
		this->element = theElement;
		this->next = NULL;
	}
	chainNode(treeNode* theElement, chainNode* theNext) {
		this->element = theElement;
		this->next = theNext;
	}
};
struct charAndWeight
{
	char character;
	int weigh;
	charAndWeight() {
		this->character = '\0';
		this->weigh = 0;
	}
	charAndWeight(char theCharacter) {
		this->character = theCharacter;
		this->weigh = 0;
	}
	charAndWeight(char theCharacter, int theWeigh) {
		this->character = theCharacter;
		this->weigh = theWeigh;
	}
};
struct treeNode {
	charAndWeight element;
	treeNode* leftChild;
	treeNode* rightChild;
	treeNode() {
		this->element = NULL;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}
	treeNode(const charAndWeight& theElement) {
		this->element = theElement;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}
	treeNode(const charAndWeight& theElement, treeNode* theLeftChild, treeNode* theRightChild) {
		this->element = theElement;
		this->leftChild = theLeftChild;
		this->rightChild = theRightChild;
	}
};

class chain
{
public:
	chain();
	chain(const chain& theList);
	~chain();
	void insert(treeNode* theElement, const int& theIndex);
	int size() { return listSize; };
	treeNode* getElement(const int& theIndex);
	int getIndex(const treeNode& theElement);
	void printList();
	void inputSortedChain();
	void inputSortedChain(const int& theElement);
	void chainIterator(chain theList);
private:
	chainNode* firstNode;
	int listSize;
};
chain::chain() {
	firstNode = NULL;
	listSize = 0;
}
chain::chain(const chain& theList) {
	listSize = theList.listSize;
	if (listSize == 0) {
		firstNode = NULL;
		return;
	}
	chainNode* sourceNode = theList.firstNode;
	firstNode = new chainNode(sourceNode->element);
	sourceNode = sourceNode->next;
	chainNode* lastNode = firstNode;
	while (sourceNode != NULL) {
		lastNode->next = new chainNode(sourceNode->element);
		lastNode = lastNode->next;
		sourceNode = sourceNode->next;
	}
	lastNode = NULL;
}
chain::~chain() {
	while (firstNode != NULL) {
		chainNode* tempNode = firstNode->next;
		delete firstNode;
		firstNode = tempNode;
	}
}
treeNode* chain::getElement(const int& theIndex) {
	chainNode* temp = firstNode;
	for (int i = 0; i < theIndex; i++)
	{
		temp = temp->next;
	}
	return temp->element;
}
int chain::getIndex(const treeNode& theElement) {
	chainNode* tempNode = firstNode;
	for (int i = 0; i < listSize; i++) {
		if (theElement.element.character == tempNode->element->element.character && theElement.element.weigh == tempNode->element->element.weigh)
			return i;
		else {
			tempNode = tempNode->next;
		}
		if (i == listSize - 1)
			return -1;
	}
}
void chain::insert(treeNode* theElement, const int& theIndex) {
	//在theIndex前一位插入新节点
	if (theIndex == 0) {
		firstNode = new chainNode(theElement, firstNode);
	}
	else {
		chainNode* temp = firstNode;
		for (int i = 0; i < theIndex - 1; i++) {
			temp = temp->next;
		}//循环结束后temp指向序号为theIndex的节点的前一个结点
		temp->next = new chainNode(theElement, temp->next);
	}
	listSize++;
}
void chain::printList() {
	chainNode* temp = firstNode;
	for (int i = 0; i < listSize - 1; i++) {
		cout << temp->element << ",";
		temp = temp->next;
	}
	cout << temp->element;
}
void chain::inputSortedChain() {
	int temp;
	cin >> temp;
	insert(temp, 0);
	cin >> temp;
	while (temp != 0) {
		for (int i = 0; i < listSize; i++) {
			if (temp < getElement(i)) {
				insert(temp, i);
				break;
			}
			if (i == listSize - 1) {//在链表尾部插入新元素
				insert(temp, listSize);
				break;
			}
		}
		cin >> temp;
	}
}
void chain::inputSortedChain(const int& theElement) {
	for (int i = 0; i < listSize; i++) {
		if (theElement < getElement(i)) {
			insert(theElement, i);
			break;
		}
		if (i == listSize - 1) {//在链表尾部插入新元素
			insert(theElement, listSize);
			break;
		}
	}
}
void chain::chainIterator(chain theList) {
	for (int j = 0; j < theList.size(); j++) {
		for (int i = 0; i <= listSize; i++) {
			if (i == 0) {
				if (theList.getElement(j) < this->getElement(0)) {
					this->insert(theList.getElement(j), 0);
					break;
				}
			}
			else {
				if (i == listSize) {
					if (theList.getElement(j) > this->getElement(listSize - 1)) {
						this->insert(theList.getElement(j), listSize);
						break;
					}
				}
				else {
					if (theList.getElement(j) > this->getElement(i - 1) && theList.getElement(j) < this->getElement(i)) {
						this->insert(theList.getElement(j), i);
						break;
					}
				}
			}
		}
	}
}

class binaryTree {
public:
	binaryTree();
	~binaryTree() { erase(root); };
	int setHeight() { return height(root); };
	int countELement() { return count(root); };
	void rootErase();
	void inputTree();
	treeNode* root;
private:

	int countTemp = 0;
	int treeSize, treeHeight;
	int height(const treeNode* root);
	void erase(const treeNode* root);
	int count(const treeNode* root);
	void input(const string& data, treeNode* root, const int& length, const int& index);
};
binaryTree::binaryTree() {
	root = NULL;
	treeSize = 0;
	treeHeight = 0;
}
int binaryTree::height(const treeNode* root) {
	if (root == NULL)
		return 0;
	else {
		int leftHeight = height(root->leftChild);
		int rightHeight = height(root->rightChild);
		return (leftHeight > rightHeight) ? (++leftHeight) : (++rightHeight);
	}
}
void binaryTree::erase(const treeNode* root) {
	if (root != NULL) {
		erase(root->leftChild);
		erase(root->rightChild);
		delete root;
	}
}
void binaryTree::rootErase() {
	erase(root);
	treeSize = 0;
	treeHeight = 0;
}
int binaryTree::count(const treeNode* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		return count(root->leftChild) + count(root->rightChild) + 1;
	}
}

class HuffmanCodeOperator
{
public:
	HuffmanCodeOperator();
	void createHuffmanTree();
	void inputFrequencyArray();
private:
	int lengthOfFrequencyArray;
	binaryTree* charSet;
	void createFrequencyArray(int length);
};
HuffmanCodeOperator::HuffmanCodeOperator()
{
	lengthOfFrequencyArray = 0;
	charSet = NULL;
}
void HuffmanCodeOperator::createFrequencyArray(int length) {
	this->lengthOfFrequencyArray = length;
	this->charSet = new binaryTree[length];
}
void HuffmanCodeOperator::inputFrequencyArray() {
	cin >> lengthOfFrequencyArray;
	createFrequencyArray(lengthOfFrequencyArray);
	for (int i = 0; i < lengthOfFrequencyArray; i++) {
		charAndWeight temp;
		cin >> temp.character >> temp.weigh;
		charSet[i].root = new treeNode(temp);
	}
}
void HuffmanCodeOperator::createHuffmanTree() {

}