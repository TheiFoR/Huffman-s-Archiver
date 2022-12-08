#include "HuffmansAlgorithm.h"
#include "Node.h"
#include <time.h> 
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <bitset>

#define BUFFER_BLOCK_SIZE 256

#define dch(to) cout << to << " is Good\n";
#define tmr0 startTimer=clock();
#define tmr1(v) endTimer=clock();secondsTimer=(double)(endTimer-startTimer)/CLOCKS_PER_SEC;cout<<v<<" The time: "<<secondsTimer<<" seconds\n";startTimer=clock();
#define tmr2(v) endTimer=clock();secondsTimer=(double)(endTimer-startTimer)/CLOCKS_PER_SEC;cout<<v<<" The time: "<<secondsTimer<<" seconds\n";
#define tmri clock_t endTimer;clock_t startTimer;double secondsTimer;
#define bar(i, maxI, max) if (i % (maxI / max) == 0) {int progress = 0;system("cls");cout << "/" << string((progress / (100 / max)), '#') << string((100 / (100 / max)) - (progress / (100 / max)), '.') << "/ " << progress << " % " << endl;++progress;}
#define prl(t) cout<<t<<endl;
#define pr(t) cout<<t<<" ";

typedef unordered_map<char, int>::iterator iteratorCI;
typedef unordered_map<char, vector<bool>>::iterator iteratorCV;

using namespace std;

void HuffmansAlgorithm::encode(Node* _root, string str, unordered_map<char, string>& _huffmanCode, ofstream* codeBookFileName)
{
	if (_root == nullptr) {
		*codeBookFileName << '-';
		_codeBook += '-';
		return;
	}

	if (!_root->leftNode && !_root->rightNode) {
		_huffmanCode[_root->letter] = str;
	}

	*codeBookFileName << (_root->letter);
	_codeBook += (_root->letter);
	encode(_root->leftNode, str + "0", _huffmanCode, codeBookFileName);
	encode(_root->rightNode, str + "1", _huffmanCode, codeBookFileName);
}
void HuffmansAlgorithm::decode(Node* _root, int& index, string str, string& result)
{
	if (_root == nullptr) {
		return;
	}

	if (!_root->leftNode && !_root->rightNode)
	{
		result += _root->letter;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(_root->leftNode, index, str, result);
	else
		decode(_root->rightNode, index, str, result);
}
void HuffmansAlgorithm::restoringTree(Node*& _root, string codeBook)
{
	static int index = 0;
	if (codeBook.size() - 1 == index)
		return;

	static int specialPosition = -1;

	char value = codeBook[index++];
	if (specialPosition == -1) {
		int indexSpecialPosition = codeBook.find("---", index);
		int indexSpecialPosition1 = codeBook.find("-----", index);
		if (indexSpecialPosition == indexSpecialPosition1) {
			specialPosition = indexSpecialPosition + 2;
		}
		else if (indexSpecialPosition != -1) {
			specialPosition = indexSpecialPosition;
		}
	}

	if (value == '-' && specialPosition != index - 1)
		return;

	_root = _root->getNode(value);
	restoringTree(_root->leftNode, codeBook);
	restoringTree(_root->rightNode, codeBook);
}

string HuffmansAlgorithm::readFileBlockwise(string fileName) {
	string textFromFile;

	char* buffer = new char[BUFFER_BLOCK_SIZE+1];
	buffer[BUFFER_BLOCK_SIZE] = 0;

	ifstream inFile(fileName, ios::binary);

	if (inFile.is_open())
	{
		inFile.seekg(0, ios::end);
		size_t fileSize = inFile.tellg();
		inFile.seekg(0);

		int numberOfCompleteBlocks = fileSize / BUFFER_BLOCK_SIZE;

		for (int i = 0; i < numberOfCompleteBlocks; ++i) {
			inFile.read(buffer, BUFFER_BLOCK_SIZE);
			textFromFile.append(buffer, BUFFER_BLOCK_SIZE);
		}

		numberOfCompleteBlocks = fileSize % BUFFER_BLOCK_SIZE;

		inFile.read(buffer, numberOfCompleteBlocks);
		buffer[numberOfCompleteBlocks] = 0;

		textFromFile.append(buffer, numberOfCompleteBlocks);
	}
	inFile.close();

	delete[] buffer;

	if (!textFromFile.empty() && textFromFile[textFromFile.size() - 1] == -1)
		textFromFile.erase(prev(textFromFile.end()));

	return textFromFile;
}

void HuffmansAlgorithm::fillingInProbability() {
	for (char ch : _inputText) {
		++_letterProbability[ch];
	}
}
void HuffmansAlgorithm::initializingTree() {
	for (auto pair : _letterProbability) {
		_initialTree.emplace(_root->getNode(pair.first, pair.second));
	}
}
void HuffmansAlgorithm::creatingTree() {
	int letterFrequencyAmount;
	while (_initialTree.size() > 1)
	{
		Node* left = _initialTree.top();
		_initialTree.pop();

		Node* right = _initialTree.top();
		_initialTree.pop();

		letterFrequencyAmount = left->letterFrequency + right->letterFrequency;
		_initialTree.emplace(_root->getNode('\0', letterFrequencyAmount, left, right));
	}
}
void HuffmansAlgorithm::creatingCodeBook() {
	_root = _initialTree.top();
	ofstream* codeBookFile = new ofstream();
	codeBookFile->open("CodeBook.txt", ios::binary);
	if (codeBookFile->is_open()) {
		encode(_root, "", _huffmanCode, codeBookFile);
	}
	codeBookFile->close();
}
void HuffmansAlgorithm::encodingIntoBinaryCode() {
	size_t i = 0;
	char byteBuffer = 0;
	string tempResult;

	tempResult.reserve(_inputText.size());
	for (char ch : _inputText) {
		tempResult += _huffmanCode[ch];
		while(tempResult.size() - (8*i) > 7) {
			byteBuffer = 0;
			for (int j = 0; j < 8; ++j) {
				byteBuffer += ((tempResult[(i * 8 + j)] - '0') << (7 - j));
			}
			++i;
			_outputText += byteBuffer;
		}
	}
	tempResult += "1";
	byteBuffer = 0;
	for (int j = 0; j < tempResult.size() - (8 * i); ++j) {
		byteBuffer += ((tempResult[i * 8 + j] - '0') << (7 - j));
	}
	_outputText += byteBuffer;
}
void HuffmansAlgorithm::writeToFile(string fileName) {
	ofstream resultFile;
	resultFile.open(fileName, ios::binary);
	resultFile << _outputText;
	resultFile.close();
}


string HuffmansAlgorithm::getBinaryCode(string text) {
	string binaryRow;
	bitset<8> byte;
	for (char ch : text) {
		byte = ch;
		binaryRow += byte.to_string();
	}
	return binaryRow;
}
void HuffmansAlgorithm::decodeText(string text) {
	unsigned int index = 0;
	unsigned int tempCount = 0;
	unsigned int count = 0;
	unsigned int end = 0;

	string result;
	Node* tempRoot = _root;

	size_t textSize = text.size();
	result.reserve(textSize);

	while ((text[textSize - 1] & 0b00000001 << (end)) >> (end) != 0b00000001) {
		++end;
	}
	while (index < textSize) {
		tempCount = 7 - count;
		if (index == textSize - 0b00000001) {
			if (count == 0b00001000 - end) {
				break;
			}
		}
		if ((text[index] & (0b00000001 << tempCount)) >> tempCount) {
			if (!tempRoot->rightNode) {
				result += tempRoot->letter;
				tempRoot = _root;
			}
			else
			{
				tempRoot = tempRoot->rightNode;
				++count;
			}
		}
		else {
			if (!tempRoot->leftNode) {
				result += tempRoot->letter;
				tempRoot = _root;
			}
			else
			{
				tempRoot = tempRoot->leftNode;
				++count;
			}
		}

		if (count == 0b00001000) {
			++index;
			count = 0b0;
		}
	}
	_outputText = result;
}

void HuffmansAlgorithm::codingAlgorithm(string inputFileName, string outputFileName)
{
	//tmri;
	//tmr0;
	_inputText = readFileBlockwise(inputFileName);
	prl(_inputText.size());
	fillingInProbability();//
	initializingTree();
	creatingTree();
	creatingCodeBook();
	encodingIntoBinaryCode();//
	writeToFile(outputFileName);
	_outputText = "";
	_inputText = "";
	_root->deleteNode(_root);
}
void HuffmansAlgorithm::decodingAlgorithm(string inputFileName, string outputFileName) {
	_inputText = readFileBlockwise(inputFileName);//
	_codeBook = readFileBlockwise("CodeBook.txt");
	restoringTree(_root, _codeBook);
	decodeText(_inputText);//
	writeToFile(outputFileName);
	prl(_outputText.size());
}