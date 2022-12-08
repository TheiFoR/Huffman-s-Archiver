#pragma once
#include <string>
#include <vector>

using namespace std;

class FileWorker
{
private:
	string _inName;
	string _outName;
public:
	FileWorker();

	vector<string> getNameFromConsole();
	void write(string text);
	void writeBin(string text);
	void write(string text, string name);

	string readAllIn();
	string readAllOut();
	string readAll(string name);

	string getInName();
	string getOutName();
};