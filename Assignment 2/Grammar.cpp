#include "Grammar.h"
#include "Variable.h"
#include <fstream>
#include <iostream>
#include <time.h>

// Reads the grammar from the input file and stores the content in a string.
void Grammar::LoadGrammar(const std::string &file_name)
{
    std::ifstream fin;
    fin.open(file_name.c_str());

    if (!fin.is_open())
    {
        std::cout << "file not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string temp;
    while (fin)
    {
        std::getline(fin, temp);
        m_file_content += temp;
        m_file_content += "\n";
    }

    fin.close();

    // A very weak way to check if the grammar file is valid.  This just checks if "START=" is found or not.
    // A much more complete function could be written to handle every instance of invalid content.  But for the
    // sake of time, I'll leave this as it is.
    if (m_file_content.find("START=") == std::string::npos)
    {
        std::cerr << "Invalid grammar file. Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }
}
// Derives a final string using the grammar rules associated with each variable found within.
std::string Grammar::RandomizedDerivation()
{
    ParseVariablesAndRules(m_file_content);
    // Grab "START" from the variables vector.
    if (!m_variables.empty())
    {
        auto i = m_variables.begin();
        m_current_string = (*i)->m_name;
    }
    std::string temp = "";

    // Keep looping until all variables have been derived.  Every variable found within the current string are stored 
    // in the 'm_variable_references' vector.  Ideally this would store custom objects, but I store them as string
    // objects instead.
    while (AnyCapitalLettersLeft(m_current_string))
    {
        temp = "";
        for (unsigned i = 0; i < m_current_string.size(); i++)
        {
            if (isupper(m_current_string.at(i)))
            {
	            temp += m_current_string.at(i);
            }
            // This takes care of variables that are not at the end of the sentence (i.e. "CONTENTS on ...")
            if (!isupper(m_current_string.at(i)))
            {
	            if (temp != "")
	            {
		            m_variable_references.push_back(temp);
	            }
	            temp = "";
            }
        }
        // This takes care of variables at the end of a sentence (i.e. "... BREAD", or "START")
        if (temp != "")
        {
            m_variable_references.push_back(temp);
        }

        // This loop derives all of the variables that were found in the current string.
        while (!m_variable_references.empty())
        {
            srand((unsigned int)time(NULL));
            // Randomly choose which variable to derive.
            int rand_index = rand() % m_variable_references.size();
            auto iter = m_variable_references.at(rand_index);

            std::cout << "in \"" << iter << "\" replacing \"" << iter << "\" with \"" << GetRule(iter) << "\"";
            replace(m_current_string, iter, GetRule(iter));
            std::cout << " to obtain \"" << m_current_string << "\"" << std::endl;
            m_variable_references.erase(m_variable_references.begin() + rand_index);
        }
    }
    return m_current_string;
}

// Prints all of the variables and their associated rules. This was used primarily for debugging purposes.
void Grammar::PrintGrammar()
{
    if (m_variables.empty())
    {
        std::cout << "The grammar is empty." << std::endl;
    }
    for (auto variable_iter = m_variables.begin(); variable_iter != m_variables.end(); variable_iter++)
    {
        (*variable_iter)->PrintRules();
    }
}

// Parses all of the variables and grammar rules from the input file.
void Grammar::ParseVariablesAndRules(const std::string &m_file_content)
{
    std::unique_ptr<Variable> p;
    std::string file_content = m_file_content;
    std::string temp, var, rule;

    while (file_content.size() > 0)
    {
        if (isupper(file_content.at(0)))
        {
            // Grab each full line, one at a time.
            temp = file_content.substr(0, file_content.find("\n"));

            // Separate the variable...
            var = temp.substr(0, temp.find("="));
            p = std::make_unique<Variable>(var);

            // Separate the rule...
            rule = temp.substr(temp.find("=") + 1, temp.size());
            p->m_rules.push_back(rule);

            var = "";
            rule = "";

            // Erase the current line that we just processed.  This just proved to be a lot easier to
            // deal with, than trying to constantly seek through the entire 'file_content' string.
            file_content.erase(0, temp.size() + 1);

            // Grab all of the alternate rules, if any exist.
            while (file_content.at(0) == '|')
            {
                temp = file_content.substr(0, file_content.find("\n"));

                // "+1" here because we want to grab the "\n" char.  'find' only reads up to a delimiter,
                // but doesn't include it.
                rule = temp.substr(temp.find("|") + 1, temp.size());
                p->m_rules.push_back(rule);

                rule = "";
                file_content.erase(0, temp.size() + 1);
            }

            // 'move' transfers ownership of the object that p pointed to, to the unique pointer inside
            //  the m_variables vector.  Dereferencing p after this would throw an exception.
            m_variables.push_back(move(p));
        }
        else
        {
            // Delete any lines that we are not concerned with (i.e. comments starting with "#")
            temp = file_content.substr(0, file_content.find("\n"));
            file_content.erase(0, temp.size() + 1);
        }
    }
}

// Determines if any capital letters are left in the string.
bool Grammar::AnyCapitalLettersLeft(const std::string &s)
{
    for (auto iter = s.begin(); iter != s.end(); iter++)
    {
	    if (isupper(*iter))
		    return true;
    }
    return false;
}

// Replaces a substring, within a given string, with a different substring.
bool Grammar::replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
	    return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

//  This function calls the variable's GetRule() member function, which in turn, 
//  returns (randomly) one of its associated rules.
std::string Grammar::GetRule(const std::string &variable)
{
    for (auto iter = m_variables.begin(); iter != m_variables.end(); iter++)
    {
        if ((*iter)->m_name == variable)
        {
	        return (*iter)->GetRule();
	        break;
        }
    }
return "";
}

