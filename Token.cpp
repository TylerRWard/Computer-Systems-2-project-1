/*******************************************
 * File: Token.cpp                         *
 * Author: S. Blythe                       *
 * Date: 12/2024                           *
 * PURPOSE: implementation for Token       *
 *******************************************/

#include "Token.hpp"

#include <fstream>
#include <iomanip>

using namespace std;

// the promised global for string equivalents of TokenType enumeration
string TokStr[]=
{ "ERROR", "EOF_TOK", "NUM_INT", "NUM_REAL", "ADDOP", "MULOP", "ID", "RELOP", "ASSIGNOP", "LPAREN", "RPAREN",  "SEMICOLON",  "LBRACK", "RBRACK", "COMMA", "AND", "OR", "INTEGER", "FLOAT", "WHILE", "IF", "THEN", "ELSE", "VOID", "BEGIN", "END"};

// This is a "list" of the keywords. Note that they are in the same order
//   as found in the TokenType enumaration. 
static string reserved[]={"int" , "float", "while", "if", "then", "else", "void", "begin", "end" };



/******************************************************
 *  just prints out the info describing this Token    *
 *    to specified stream                             *
 *                                                    *
 *   os  - the stream to add the Token to             *
 *                                                    *
 *   returns: the updated stream                      *
 ******************************************************/
ostream&
Token::print(ostream& os) const
{
  os
     << "{ Type:"   << left << setw(10) << TokStr[_type] 
     << " Value:"   << left << setw(10) << _value
     << " Line Number:" << _line_num
     << " }";
  return os;
}

/******************************************************
 *  Fills in information about this Token by reading  *
 *    it from specified input stream                  *
 *                                                    *
 *   is  - the stream to read the Token from          *
 *                                                    *
 *   returns: nothing                                 *
 *                                                    *
 *     **** YOU MUST CODE THIS !!!!!! ****            *
 ******************************************************/
void Token::get(istream &is){
  static int lineNum = 1; // Tracks the current line number
    _value.clear();
    _type = ERROR;

    char ch;
    // Skip whitespace and comments
    while (is.get(ch)) {
        if (ch == '\n') {
            lineNum++;
        } else if (isspace(ch)) {
            continue; // Ignore whitespace
        } else if (ch == '#') {
            // Skip to the end of the line for comments
            while (is.get(ch) && ch != '\n');
            if (ch == '\n') lineNum++;
        } else {
            is.unget(); // Put back the non-whitespace, non-comment character
            break;
        }
    }

    if (!is) {
        _type = EOF_TOK;
        _line_num = lineNum;
        return;
    }


  static int DFA[20][256]; 
  static bool initialized = false;
  

  if(!initialized){
    for (int i = 0; i < 20; i++){
      for (int j = 0; j < 256; j++){
        DFA[i][j] = ERROR;
      }
    }

        // Populate DFA based on the automaton
        for (char c = '0'; c <= '9'; c++) DFA[0][c] = 2;
        for (char c = 'a'; c <= 'z'; c++) DFA[0][c] = 1;
        for (char c = 'A'; c <= 'Z'; c++) DFA[0][c] = 1;
        DFA[0]['+'] = 5;
        DFA[0]['-'] = 5;
        DFA[0]['*'] = 6;
        DFA[0]['/'] = 6;
        DFA[0]['<'] = 7;
        DFA[0]['>'] = 7;
        DFA[0]['='] = 9;
        DFA[0]['('] = 10;
        DFA[0][')'] = 11;
        DFA[0]['&'] = 12;//another &? 13
        DFA[0]['|'] = 14;//another |? 15
        DFA[0][';'] = 16;
        DFA[0]['['] = 17;
        DFA[0][']'] = 18;
        DFA[0][','] = 19;




  }

}
