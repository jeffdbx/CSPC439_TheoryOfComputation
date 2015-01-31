#include "Ook.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Reads the Ook program from the input file.
void Ook::LoadOokProgram(const std::string &m_filename)
{
    std::ifstream fin; 
    fin.open(m_filename.c_str());

    if (!fin.is_open())
    {
        std::cerr << "ERROR: file not found." << std::endl; 
        exit(EXIT_FAILURE);
    }

    char x;
    int count = 0;
    while (fin >> x)
    {
        if ((x == '.') || (x == '!') || (x == '?'))
        {
            m_program += x; 
            count++;
        }
    }

    fin.close();

    // Make sure that we have a correct number of Ook commands. 
    if ((m_program.size() < 2) || ((count % 2) != 0))
    {
        std::cerr << "ERROR: invalid number of Ook commands." << std::endl; 
        exit(EXIT_FAILURE);
    }
    m_program_is_loaded = true;
}

// Interprets the Ook program and prints out the results to the console.
void Ook::InterpretOok()
{
    if (!m_program_is_loaded)
    {
        std::cerr << "ERROR: No Ook program has been loaded." << std::endl;
        exit(EXIT_FAILURE);
    }

    BuildJumpTable(m_program);

    // I want to protect m_program from being modified since InterpretOok() is a public method.
    // There is probably a better way to do this, but this will work for now... 
    const std::string &program = m_program;

    // Interpret the Ook instructions.
    while (m_intruction_ptr < program.size())
    {
        // Ook. Ook? Increment the data pointer.
        if (program.at(m_intruction_ptr) == '.' && program.at(m_intruction_ptr + 1) == '?')
        {
            m_current_byte++;
            // We will always increment the instruction pointer by 2, because Ook commands come in pairs. 
            m_intruction_ptr += 2;
        }
        // Ook? Ook. Decrement the data pointer.
        else if (program.at(m_intruction_ptr) == '?' && program.at(m_intruction_ptr + 1) == '.')
        {
            m_current_byte--; 
            m_intruction_ptr += 2;
        }
        // Ook. Ook. Increment the current byte.
        else if (program.at(m_intruction_ptr) == '.' && program.at(m_intruction_ptr + 1) == '.')
        {
            (*m_current_byte)++; 
            m_intruction_ptr += 2;
        }
        // Ook! Ook! Decrement the current byte.
        else if (program.at(m_intruction_ptr) == '!' && program.at(m_intruction_ptr + 1) == '!')
        {
            (*m_current_byte)--; 
            m_intruction_ptr += 2;
        }
        // Ook! Ook. Write the current byte to stdout.
        else if (program.at(m_intruction_ptr) == '!' && program.at(m_intruction_ptr + 1) == '.')
        {
            std::cout << (*m_current_byte); 
            m_intruction_ptr += 2;
        }
        // Ook. Ook! Read a char from stdin and overwrite the current byte with it.
        else if (program.at(m_intruction_ptr) == '.' && program.at(m_intruction_ptr + 1) == '!')
        {
            std::cin >> (*m_current_byte); 
            m_intruction_ptr += 2;
        }
        // Ook! Ook? Start of a loop, "["
        else if (program.at(m_intruction_ptr) == '!' && program.at(m_intruction_ptr + 1) == '?')
        {
            // if m_current_byte is zero, jump to the first instruction just past the matching Ook? Ook! 
            if (*m_current_byte == 0)
            {
                m_intruction_ptr = m_jump_table[m_intruction_ptr];
            }
            // otherwise, enter the loop. 
            else
            {
                m_intruction_ptr += 2;
            }
        }
        // Ook? Ook! End of a loop, "]"
        else if (program.at(m_intruction_ptr) == '?' && program.at(m_intruction_ptr + 1) == '!')
        {
            // if m_current_byte is zero, exit the loop. 
            if (*m_current_byte == 0)
            {
                m_intruction_ptr += 2;
            }
            // otherwise, jump back to the first instruction past its matching Ook! Ook? 
            else
            {
                m_intruction_ptr = m_jump_table[m_intruction_ptr];
            }
        }
    }
}

// Prints out the jump table to the console. (Used for debugging).
void Ook::DisplayJumpTable(const std::map<int, int> &m_jump_table)
{
    std::cout << "\tTotal size: " << m_jump_table.size() << std::endl;
    for (auto iter = m_jump_table.begin(); iter != m_jump_table.end(); iter++)
    {
        std::cout << std::setw(10) << iter->first << std::setw(5) << iter->second << std::endl;
    }
    std::cout << std::endl;
}

void Ook::BuildJumpTable(const std::string &m_program)
{
    for (unsigned i = 0; i < m_program.size(); i++)
    {
        // Ook! Ook? Start of a loop, "["
        if (m_program.at(i) == '!' && m_program.at(i + 1) == '?')
        {
            // Push its position on the stack. 
            m_brackets_stack.push(i);
        }
        // Ook? Ook! End of a loop, "]"
        else if (m_program.at(i) == '?' && m_program.at(i + 1) == '!')
        {
            if (m_brackets_stack.size() == 0)
            {
                // The stack is empty, which means there is no matching opening bracket "[" for
                // this closing bracket.
                std::cerr << "ERROR: unmatched \"Ook? Ook!\" at position " << i << std::endl; 
                exit(EXIT_FAILURE);
            }
            else
            {
                // The "]" has a matching "[". Add the location of both to the jump table. 
                int open_bracket_position = m_brackets_stack.top();
                m_brackets_stack.pop();

                // Remember that this jump table is a map. Where we have m_jump_table[KEY] = VALUE.
                // Here we map the position of the opening bracket (key) with the first instruction past its
                // matching closing bracket (value). 
                m_jump_table[open_bracket_position] = i + 2;

                // Here we map the position of the closing bracket (key) with the first instruction past its
                // matching opening bracket (value). 
                m_jump_table[i] = open_bracket_position + 2;
            }
        }

        // We need to increment by an additional +1 here because Ook commands come in pairs. 
        i++;
    }

    if (m_brackets_stack.size() > 0)
    {
        // The stack still has opening brackets "[" in it after reading all of the closing brackets "]". 
        std::cerr << "ERROR: unmatched \"Ook! Ook?\" at position " << m_brackets_stack.top() << std::endl;
        exit(EXIT_FAILURE);
    }
}

