This program derives strings randomly from a context free grammar(CFG) supplied as input.

The general algorithm for accomplishing this is as follows:
1. Initialize the current string to be START.
2. While the current string contains upper case letters:
  (a) Identify the variable names in the current string (there must be at least one).

  (b) Choose one name to expand randomly, where each variable name instance is equally 
  likely to be chosen.
 
  (c) Find the variable’s rules in the grammar. Choose one of the rules to expand
   randomly, where again each of the variable’s rules are equally likely to be chosen.

3. Return the current string, which contains no upper case letters.
