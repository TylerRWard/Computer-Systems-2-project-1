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
            _line_num++;
        }else if(ch == '#'){
          while (is.get(ch) && ch!='\n'){
            //do nothing
          }
          if (ch =='\n'){
            lineNum++;
          }
        }else if (!isspace(ch)){
          break; // Break on the first non-whitespace character
        }  
    }

    if (!is) {
        _type = EOF_TOK;
        return;
    }


  static unsigned int DFA[20][256]; 
  static bool initialized = false;
  

  if(!initialized){
    for (int i = 0; i < 20; i++){
      for (int j = 0; j < 256; j++){
        DFA[i][j] = ERROR;
      }
    }

        // Populate DFA based on the automaton state 0 transitions
        for (char c = '0'; c <= '9'; c++) DFA[0][(unsigned int)c] = 2;
        for (char c = 'a'; c <= 'z'; c++) DFA[0][(unsigned int)c] = 1;
        for (char c = 'A'; c <= 'Z'; c++) DFA[0][(unsigned int)c] = 1;
        DFA[0][(unsigned int)'+'] = 5;
        DFA[0][(unsigned int)'-'] = 5;
        DFA[0][(unsigned int)'*'] = 6;
        DFA[0][(unsigned int)'/'] = 6;
        DFA[0][(unsigned int)'<'] = 7;
        DFA[0][(unsigned int)'>'] = 7;
        DFA[0][(unsigned int)'='] = 9;
        DFA[0][(unsigned int)'('] = 10;
        DFA[0][(unsigned int)')'] = 11;
        DFA[0][(unsigned int)'&'] = 12;//another &? 13
        DFA[0][(unsigned int)'|'] = 14;//another |? 15
        DFA[0][(unsigned int)';'] = 16;
        DFA[0][(unsigned int)'['] = 17;
        DFA[0][(unsigned int)']'] = 18;
        DFA[0][(unsigned int)','] = 19;
        // state 1 transitions
        for (char c = 'a'; c<= 'z'; c++) DFA[1][(unsigned int)c]=1;
        for (char c = 'A'; c<= 'Z'; c++) DFA[1][(unsigned int)c]=1;
        for (char c = '0'; c<= '9'; c++) DFA[1][(unsigned int)c]=1;
        //state 2 transitions
        for (char c = '0'; c <= '9'; c++) DFA[2][(unsigned int)c] = 2;
        DFA[2][(unsigned int)'.'] = 3;
        //state 3 transitions 
        for (char c = '0'; c <= '9'; c++) DFA[3][(unsigned int)c] = 4;
        //state 4 transitions
        for (char c = '0'; c <= '9'; c++) DFA[4][(unsigned int)c] = 4;
        //state 7
        DFA[7][(unsigned int)'='] = 8;
        //state 9
        DFA[9][(unsigned int)'='] = 8;
        //state 12
        DFA[12][(unsigned int)'&'] = 13;
        //state 14
        DFA[14][(unsigned int)'|'] =15;

        initialized = true;
  }

  unsigned int state =0;
  _line_num = lineNum;

  do{
    unsigned int nextState = DFA[state][(unsigned int) ch];
    if (nextState == ERROR) break;

    state = nextState;
    _value +=ch;

    //check if we can fetch the next char

    if(!is.get(ch)) break;
    if (ch=='\n') lineNum++;

  } while(true);

      // Determine the token type based on the final state
    switch (state) {
        case 1:  // ID or Keyword
            if (_value == "int") _type = INTEGER;
            else if (_value == "float") _type = FLOAT;
            else if (_value == "while") _type = WHILE;
            else if (_value == "if") _type = IF;
            else if (_value == "then") _type = THEN;
            else if (_value == "else") _type = ELSE;
            else if (_value == "void") _type = VOID;
            else if (_value == "begin") _type = BEGIN;
            else if (_value == "end") _type = END;
            else _type = ID;
            break;
        case 2:
            _type = NUM_INT;
            break;
        case 4:
            _type = NUM_REAL;
            break;
        case 5:
            _type = ADDOP;
            break;
        case 6:
            _type = MULOP;
            break;
        case 7:
        case 8:
            _type = RELOP;
            break;
        case 9:
            _type = ASSIGNOP;
            break;
        case 10:
            _type = LPAREN;
            break;
        case 11:
            _type = RPAREN;
            break;
        case 13:
            _type = AND;
            break;
        case 15:
            _type = OR;
            break;
        case 16:
            _type = SEMICOLON;
            break;
        case 17:
            _type = LBRACK;
            break;
        case 18:
            _type = RBRACK;
            break;
        case 19:
            _type = COMMA;
            break;
        default:
            _type = ERROR;
            break;
    }
}
