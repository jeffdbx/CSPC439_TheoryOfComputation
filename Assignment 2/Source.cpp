// Jeff Bohlin
// CPSC 439 - Project 2
// October 27th, 2014
//
// This program derives strings randomly from a context free grammar(CFG) supplied as input.
//
// The general algorithm for accomplishing this is as follows:
// 1. Initialize the current string to be START.
// 2. While the current string contains upper case letters:
//	    (a) Identify the variable names in the current string(there must be at least
//		one).
//
//		(b) Choose one name to expand randomly, where each variable name instance
//		is equally likely to be chosen.
//
//		(c) Find the variable’s rules in the grammar. Choose one of the rules to expand
//		randomly, where again each of the variable’s rules are equally likely to be
//		chosen.
//
// 3. Return the current string, which contains no upper case letters.
//

#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<list>
#include<memory>
#include<vector>
#include<time.h>

#include"RandomStringDerivation.h"


//  GetData
//
//  Reads the grammar from the input file and stores the content in a string.
//  @param file_name: the name of the input file.
//  @param file_content: the content of the input file.
//
void GetData(const std::string &file_name, std::string &file_content);

int main(int argc, char** argv)
{
	using namespace std;

	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return EXIT_FAILURE;
	}

	string file_name(argv[1]);
	string file_content;

	GetData(file_name, file_content);

	Grammar grammar(file_content);
	grammar.ParseVariablesAndRules();
	
	cout << "FINAL STRING:\n" << grammar.RandomizedDerivation() << endl;


	return EXIT_SUCCESS;
}

// Reads the grammar from the input file and stores the content in a string.
void GetData(const std::string &file_name, std::string &file_content)
{
	using namespace std;

	ifstream fin;
	fin.open(file_name.c_str());

	if (!fin.is_open())
	{
		cout << "file not found!" << endl;
		exit(EXIT_FAILURE);
	}

	string temp;
	while (fin)
	{
		getline(fin, temp);
		file_content += temp;
		file_content += "\n";
	}

	fin.close();

	// A very weak way to check if the grammar file is valid.  This just checks if "START=" is found or not.
	// A much more complete function could be written to handle every instance of invalid content.  But for the
	// sake of time, I'll leave this as it is.
	if (file_content.find("START=") == string::npos)
	{
		cerr << "Invalid grammar file. Exiting..." << endl;
		exit(EXIT_FAILURE);
	}
}
