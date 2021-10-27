#pragma once

#include <cassert>
#include <vector>
#include <string>

//#include "value.h"
//#include "data_types.h"

#ifdef HAHA

namespace tlisp {

    /** tinyLISP tokenizer.

     */
    class Scanner {
    public:

        /** Parses the given tinyLISP source in a string and returns the vector of its tokens.
         */
        static Value Scan(std::string const & input);

    private:

        Scanner(std::string const & input):
            input_(input),
            i_(0),
            line_(1),
            col_(1) {
        }
        

        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        bool isLetter(char c) {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        }

        bool isSymbolCharacter(char c) {
            return isLetter(c) || isDigit(c) || c == '_';
        }

        void addToken(Value const & o);

        bool eof();
        char top();
        char pop();
        char pop(char what);
        bool condPop(char what);


        void skipWhitespace();
        void skipComment();
        void scanNumber();
        void scanSymbol();
        
        void scan();

        std::string const & input_;

        size_t i_;
        size_t line_;
        size_t col_;


        List tokens_;

        
    }; // tlisp::Scanner


    /** tinyLISP parser.

        Using the list of tokens, parses the tinyLISP source code into the s-expressions. The grammar for this is extremely simple:

        ITEM := [ '\'' ] (number | symbol | LIST_OR_CONS)
        LIST_OR_CONS := '(' { ITEM } ')'
                     := '(' ITEM '.' ITEM ')'

        SOURCE := { ITEM }
        
     */
    class Parser {
    public:

        static Value Parse(Value tokens);

    private:

        Parser(Value tokens):
            start_(tokens),
            cur_(tokens) {
        }

        bool eof() {
            return cur_ == Nil;
        }

        Value top();
        Value pop();

        Value ITEM();
        Value LIST_OR_CONS();
        Value SOURCE();

        Value start_;
        Value cur_;
        
    }; // tlisp::Parser
    
} // namespace tlisp

#endif
