#pragma once

#include "Variable.h"
#include<string>
#include<list>
#include<memory>

class Grammar
{
public:
    // Default ctor.
    Grammar() {}

    //  LoadGrammar
    //
    //  Reads the grammar from the input file and stores the content in a string.
    //  @param file_name: the name of the input file.
    //
    void LoadGrammar(const std::string &file_name);

    //  RandomizedDerivation
    //
    //  Derives a final string using the grammar rules associated with each variable found within.
    //  @return: the final derived string as a result of implementing the grammar
    //  rules for each variable within the string.
    //
    std::string RandomizedDerivation();

    //  PrintGrammar
    //
    //  Prints all of the variables and their associated rules. This was used primarily
    //  for debugging purposes.
    //
    void PrintGrammar();

    // Default dtor.
    ~Grammar()
    {
        // No need to delete objects pointed to by unique_ptrs.  They will take care of themselves.
    }

private:
    //  ParseVariablesAndRules
    //
    //  Parses all of the variables and grammar rules from the input file.
    //  @param m_file_name: the content of the input file. Explicitly passing a
    //  private member in order to enforce const.
    //
    void ParseVariablesAndRules(const std::string &m_file_content);

    //  AnyCapitalLettersLeft
    //
    //  Determines if any capital letters are left in the string.
    //  @param s: the current string of the derivation.
    //  @return: true if a capital letter exists, false otherwise.
    //
    bool AnyCapitalLettersLeft(const std::string &s);

    //  replace
    //
    //  Replaces a substring, within a given string, with a different substring.
    //  @param str: the string to be modified.
    //  @param from: the substring in 'str' to be replaced.
    //  @param to: the substring to be inserted into 'str'.
    //  @return: true if replacement occurred, false otherwise.
    //
    //  Reference:
    //  http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
    //
    bool replace(std::string &str, const std::string &from, const std::string &to);

    //  GetRule
    //
    //  This function calls the variable's GetRule() member function, which in turn, 
    //  returns (randomly) one of its associated rules.
    //  @param variable: the name of the variable we are looking up.
    //  @return: a rule associated with that variable.
    //
    std::string GetRule(const std::string &variable); 

    // Stores all of the variables found within the input file.
    std::list<std::unique_ptr<Variable>> m_variables;

    // Stores all of my "variable references".  This was going to store objects as outlined in the assignment
    // requirements.  However, I was having issues understanding fundamentally how to implement that.  So I
    // resorted to storing them as string objects to reduce complication (for me).
    std::vector<std::string> m_variable_references;

    // The input file content.
    std::string m_file_content;

    // The current string that we are deriving.
    std::string m_current_string;
};