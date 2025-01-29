# Computer Systems 2 - Project 1

**Author:** Tyler Ward  
**Platform:** Mac  
**Compile:** Use the Makefile (e.g., `make`)  
**Run:** To run, provide a file to be parsed (e.g., `./tokenify test.myl`)  

---

## Bugs
None that I am aware of.

---

## Overview
This project involved building a lexical analyzer for a programming language. The implementation follows the automaton provided in the project outline. Here's a breakdown of the approach:

1. **DFA Array:**  
   I created a DFA (Deterministic Finite Automaton) array to handle transitions between states based on input characters. This array was initialized to map characters to their corresponding states.

2. **Tokenization:**  
   The DFA processes input characters and identifies tokens based on the final state reached. Keywords, identifiers, numbers, and operators are all handled by the DFA.

3. **Printing Tokens:**  
   The `Token` class provided most of the functionality for printing tokens. I used a `switch` statement to assign token types based on the final state of the DFA.

---

## Software Engineering Log

### Day 1
- Created the DFA array and initialized it with transitions based on the automaton provided in the project outline.

### Day 2
- Fixed bugs in the DFA array, ensuring that all transitions were correctly mapped.

### Day 3
- Worked on implementing the `switch` statement to assign token types based on the final state of the DFA.
- Debugged issues with token printing.

### Day 4
- Finalized the implementation and tested the program with various input files to ensure correctness.
- Cleaned up the code and added comments for clarity.
### Day 5
- Realized that I am having major issues with my output because it doesn't recognize && or single character tokens.
- To fix this I found out that my only issue is the fact that I didn't putback ch if the next state is error. 

---

## Notes
- The project closely follows the structure and requirements outlined in the assignment.
- The DFA implementation ensures that all tokens are correctly identified and categorized.
- The program handles comments and whitespace appropriately, skipping them during tokenization.

---

## How to Use
1. **Compile:**  
   Run `make` to compile the program.

2. **Run:**  
   Execute the program with an input file:  
   ```bash
   ./tokenify <input_file>