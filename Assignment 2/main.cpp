// Jeff Bohlin
// CPSC 439 - Assignment 2
// October 27th, 2014
//
// This program derives strings randomly from a context free grammar(CFG) supplied as input.
//
// The general algorithm for accomplishing this is as follows:
// 1. Initialize the current string to be START.
// 2. While the current string contains upper case letters:
//      (a) Identify the variable names in the current string(there must be at least
//      one).
//
//      (b) Choose one name to expand randomly, where each variable name instance
//      is equally likely to be chosen.
//
//      (c) Find the variable’s rules in the grammar. Choose one of the rules to expand
//      randomly, where again each of the variable’s rules are equally likely to be
//      chosen.
//
// 3. Return the current string, which contains no upper case letters.
//

#include "Grammar.h"
#include "Variable.h"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string file_name(argv[1]);
    
    Grammar grammar;
    grammar.LoadGrammar(file_name);

    std::cout << "FINAL STRING:\n" << grammar.RandomizedDerivation() << std::endl;

    return EXIT_SUCCESS;
}

