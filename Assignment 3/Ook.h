#pragma once

#include <string>
#include <map>
#include <stack>

const int ARRAY_SIZE = 30000;

class Ook
{
public:
    // Constructor
    //
    // @param filename: The name of the input file specified by the user.
    //  Note: "m_data{}" initializes all of the elements in the array to zero.
    //
    Ook() : m_data{}, m_current_byte(m_data), m_intruction_ptr(0), m_program_is_loaded(false) {}

    // LoadOokProgram
    //
    // Reads the Ook program from the input file.
    // @param m_filename: the name of the input file.
    //
    void LoadOokProgram(const std::string &m_filename);

    // InterpretOok
    //
    // Interprets the Ook program and prints out the results to the console.
    // (See the comments within the method itself for more details.)
    //
    void InterpretOok();

    //
    // Default destructor.
    //
    ~Ook() {}

private:

    // DisplayJumpTable
    //
    // Prints out the jump table to the console. (Used for debugging).
    // @param m_jump_table: a mapping of each pair of opening and closing
    //  brackets (Ook! Ook? means "[" and Ook? Ook! means "]").
    //
    void DisplayJumpTable(const std::map<int, int> &m_jump_table);

    // BuildJumpTable
    //
    // Builds the jump table. (See the comments inside the method itself more details.)
    // @param m_program: the Ook program.
    //
    void BuildJumpTable(const std::string &m_program);

    std::string m_program;              // A copy of the Ook progarm read from the input file.
    std::stack<int> m_brackets_stack;   // Keeps track of opening/closing brackets.
    std::map<int, int> m_jump_table;    // Keeps track of nested bracket locations.
    char m_data[ARRAY_SIZE];            // Ook program "memory."
    char *m_current_byte;               // The current memory location.
    unsigned m_intruction_ptr;          // The current instruction.
    bool m_program_is_loaded;           // True if the Ook program has been loaded.
};
