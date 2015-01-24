#pragma once

#include <string>
#include <vector>

// This class should probably be abstracted away and nested within the Grammar class, 
// but for debugging purposes, it was much easier to make everything public.
class Variable
{
public:
    // Default constructor
    Variable() { m_name == ""; }

    //  Constructor.
    //  @param name: the name of the variable.
    //
    Variable(std::string name) : m_name(name) {}

    //  PrintRules
    //
    //  Prints all of the rules associated with the variable object.
    //  This was used primarily for debugging purposes.
    //
    void PrintRules();

    //  GetRule
    //
    //  Retrieves a rule that's associated with the variable object.
    //  @return: a rule (string) chosen randomly from the possible rules.
    //
    std::string GetRule();

    // The name of the variable.
    std::string  m_name;

    // The rules associated with this variable.
    std::vector<std::string> m_rules;
};
