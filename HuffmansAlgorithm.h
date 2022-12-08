#pragma once

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

using namespace std;

class HuffmansAlgorithm
{
private:
	struct NodeCompare
	{
		bool operator()(Node* leftNode, Node* rightNode)
		{
			return leftNode->letterFrequency > rightNode->letterFrequency;
		}
	};
	unordered_map<char, unsigned int> _letterProbability;
	priority_queue<Node*, vector<Node*>,NodeCompare> _initialTree;
	unordered_map<char, string> _huffmanCode;

	string _inputText;
	string _codeBook;
	string _outputText;
	Node* _root;
	
	void encode(Node* root, string str, unordered_map<char, string>& huffmanCode, ofstream* codeBookFileName);
	void decode(Node* root, int& index, string str, string& result);

	void restoringTree(Node*& root, string codeBook);
	string readFileBlockwise(string fileName);
	string readFileBytes(string fileName);
	void fillingInProbability();
	void initializingTree();
	void creatingTree();
	void creatingCodeBook();
	void encodingIntoBinaryCode();
	void writeToFile(string fileName);

	string getBinaryCode(string text);
	void decodeText(string binaryText);
public:
	void codingAlgorithm(string inputFileName, string outputFileName);
	void decodingAlgorithm(string inputFileName, string outputFileName);
};