#include "Variable.h"
#include <iostream>
#include <time.h>

// Prints all of the rules associated with the variable object.
void Variable::PrintRules()
{
    std::cout << m_name << std::endl;
    std::cout << "---------------" << std::endl;
    for (auto rules_iter = m_rules.begin(); rules_iter != m_rules.end(); rules_iter++)
    {
        std::cout << *rules_iter << std::endl;
    }
    std::cout << std::endl;
}

// Retrieves a rule (randomly) that's associated with the variable object.
std::string Variable::GetRule()
{
    srand((unsigned int)time(NULL));
    return (!m_rules.empty() ? m_rules.at(rand() % m_rules.size()) : "");
}

