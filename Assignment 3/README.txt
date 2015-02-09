 This program acts as an Ook programming language interpreter.

 Here are the rules for Ook, along with the language it was derived from (Brainf*ck):

 Brainf*ck   Ook!       Description

    >        Ook. Ook?  Move the pointer to the right.
    <        Ook? Ook.  Move the pointer to the left.
    +        Ook. Ook.  Increment the memory cell under the pointer.
    -        Ook! Ook!  Decrement the memory cell under the pointer.
    .        Ook! Ook.  Output the character signified by the cell at the pointer.
    ,        Ook. Ook!  Input a character and store it in the cell at the pointer.
    [        Ook! Ook?  Jump past the matching "Ook? Ook!" if the cell under the pointer is 0.
    ]        Ook? Ook!  Jump back to the matching "Ook! Ook?" (to the first instruction just after it)