#include "FileWorker.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

FileWorker::FileWorker()
{
	_inName = "in.txt";
	_outName = "out.txt";
}

vector<string> FileWorker::getNameFromConsole()
{
	cout << "Enter the name of the input file with extension\n";
	getline(cin, _inName);

	cout << "Enter the name of the output file without extension\n";
	getline(cin, _outName);
	while(_inName == _outName+".bin") {
		cout << "The file names cannot be the same. Please enter another name";
		cin >> _outName;
	}
	_outName+=".bin";
	vector<string> result;
	result.emplace_back(_inName);
	result.emplace_back(_outName);
	return result;
}

void FileWorker::write(string text)
{
	ofstream outFile;
	outFile.open(_outName);
	if (outFile.is_open())
	{
		outFile << text;
	}
	outFile.close();
}

void FileWorker::write(string text, string name)
{
	ofstream outFile;
	outFile.open(name);
	if (outFile.is_open())
	{
		outFile << text;
	}
	outFile.close();
}
void FileWorker::writeBin(string text) {
	ofstream outFile;
	outFile.open(_outName);
	if (outFile.is_open())
	{
		outFile << text;
	}
	outFile.close();
}

string FileWorker::readAllIn() {
	string textFromFile = "";

	ifstream inFile(_inName, ios::binary);
	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			textFromFile += inFile.get();
		}
	}
	inFile.close();
	return textFromFile;
}

string FileWorker::readAllOut() {
	string textFromFile = "";

	ifstream inFile(_outName, ios::binary);
	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			textFromFile += inFile.get();
		}
	}

	inFile.close();
	return textFromFile;
	/*NameName*/
}

string FileWorker::readAll(string name) {
	string textFromFile = "";

	ifstream inFile(name, ios::binary);
	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			textFromFile += inFile.get();
		}
	}
	inFile.close();
	return textFromFile;
}



string FileWorker::getInName() {
	return _inName;
}

string FileWorker::getOutName() {
	return _outName;
}