// Jeff Bohlin
// CPSC 439 - Assignment 3
// December 2nd, 2014
//
// This program acts as an Ook programming language interpreter.
//
// Here are the rules for Ook, along with the language it was derived from (Brainf*ck):
//
// Brainf*ck   Ook!       Description
// ---------   ---------  -----------------------------------
//    >       Ook. Ook?  Move the pointer to the right.
//    <       Ook? Ook.  Move the pointer to the left.
//    +       Ook. Ook.  Increment the memory cell under the pointer.
//    -       Ook! Ook!  Decrement the memory cell under the pointer.
//    .       Ook! Ook.  Output the character signified by the cell at the pointer.
//    ,       Ook. Ook!  Input a character and store it in the cell at the pointer.
//    [       Ook! Ook?  Jump past the matching "Ook? Ook!" if the cell under the pointer is 0.
//    ]       Ook? Ook!  Jump back to the matching "Ook! Ook?" (actually, to the first instruction just after it)
//
// References:
// STL Maps:
// http://www.dreamincode.net/forums/topic/57446-stl-maps/
//
// Implementation of the jump table:
// http://blog.bartwolff.com/post/2011/12/05/A-brainfuck-interpreter-in-C
//

#include "Ook.h"
#include <iostream>

int main(int argc, char** argv)
{
    // User must supply a file name.
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl; 
        return EXIT_FAILURE;
    }

    std::string filename(argv[1]);

    Ook ook; 
    ook.LoadOokProgram(filename);
    ook.InterpretOok();

    return EXIT_SUCCESS;
}
