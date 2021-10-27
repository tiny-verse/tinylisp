//#include "runtime.h"
#include <iostream>

#include "frontend.h"

#ifdef HAHA

namespace tlisp {


    Value Scanner::Scan(std::string const & input) {
        Scanner s(input);
        s.scan();
        return s.tokens_;
    }
    
    void Scanner::addToken(Value const & o) {
        tokens_.append(o);
    }


    bool Scanner::eof() {
        return input_[i_] == 0;
    }

    char Scanner::top() {
        char result = input_[i_];
        if (result == '\r')
            result = '\n';
        return result;
    }

    char Scanner::pop() {
        char result = input_[i_];
        if (result == '\n') {
            if (input_[i_ + 1] == '\r')
                ++i_;
        } else if (result == '\r') {
            if (input_[i_ + 1] == '\n')
                ++i_;
            result = '\n';
        }
        if (result == '\n') {
            ++line_;
            col_ = 1;
        } else {
            ++col_;
        }
        if (result != 0)
            ++i_;
        return result;
    }

    char Scanner::Scanner::pop(char what) {
        char result = pop();
        if (result != what)
            throw std::runtime_error(STR("Unexpected character " << (int) what << "(" << what << ")"));
        return result;
    }

    bool Scanner::condPop(char what) {
        if (top() == what) {
            pop();
            return true;
        } else {
            return false;
        }
    }

    void Scanner::skipWhitespace() {
        while (condPop(' ') || condPop('\n') || condPop('\t')) {
            // pass
        }
    }

    void Scanner::skipComment() {
        pop(); // ;
        while (! eof() && ! condPop('\n'))
            pop();
    }

    void Scanner::scanNumber() {
        int result = 0;
        do {
            result = result * 10 + (pop() - '0');
        } while (isDigit(top()));
        addToken(Value::Integer(result));
    }

    void Scanner::scanSymbol() {
        // FIXME this is super innefective, don't do this at home
        std::string name;
        do {
            name = name + pop();
        } while (isSymbolCharacter(top()));
        addToken(Symbol::ForName(name));
    }
    
    void Scanner::scan() {
        while (true) {
            skipWhitespace();
            if (eof())
                break;
            switch (top()) {
            case ';':
                skipComment();
                break;
            case '(':
                addToken(Symbol::ParOpen);
                pop();
                break;
            case ')':
                addToken(Symbol::ParClose);
                pop();
                break;
            case '`':
                addToken(Symbol::BackQuote);
                pop();
                break;
            case ',':
                addToken(Symbol::Comma);
                pop();
                break;
            case '.':
                addToken(Symbol::Dot);
                pop();
                break;
            case '+':
                addToken(Symbol::Add);
                pop();
                break;
            case '-':
                addToken(Symbol::Sub);
                pop();
                break;
            case '*':
                addToken(Symbol::Mul);
                pop();
                break;
            case '/':
                addToken(Symbol::Div);
                pop();
                break;
            case '\'':
                addToken(Symbol::QuoteChar);
                pop();
                break;
            case '<':
                addToken(Symbol::Lt);
                pop();
                break;
            case '>':
                addToken(Symbol::Gt);
                pop();
                break;
            default:
                if (isDigit(top()))
                    scanNumber();
                else if (isLetter(top()))
                    scanSymbol();
                else {
                    throw std::runtime_error(STR("Invalid character " << (int) top() << "(" << top() << ")"));
                }
            }
        }
    }


    Value Parser::Parse(Value tokens) {
        Parser p(tokens);
        return p.SOURCE();
    }


    Value Parser::top() {
        if (! cur_.isCons())
            throw std::runtime_error("Extra token is expected, but end of input found");
        return car(cur_);
    }

    Value Parser::pop() {
        Value result = top();
        cur_ = cdr(cur_);
        return result;
    }

    /** ITEM := number | symbol | LIST
     */
    Value Parser::ITEM() {
        Value t = top();
        if (t.isInteger()) {
            pop();
            return t;
        }
        if (t == Symbol::ParOpen) {
            return LIST_OR_CONS();
        } else if (t == Symbol::QuoteChar) {
            List result;
            pop(); // quote char
            result.append(Symbol::Quote);
            result.append(ITEM());
            return result;
        } else if (t.isSymbol()) {
            pop();
            return t;
        }
        throw std::runtime_error(STR("Expected number, symbol, or list but " << t << " found"));
    }

    /** LIST_OR_CONS := '(' { ITEM } ')'
                     := '(' ITEM '.' ITEM ')'
     */
    Value Parser::LIST_OR_CONS() {
        List result;
        pop(); // '('
        if (top() != Symbol::ParClose) {
            result.append(ITEM());
            if (top() == Symbol::Dot) {
                pop(); // .
                result.append(ITEM());
                if (top() != Symbol::ParClose)
                    throw std::runtime_error(STR("Expected closing parenthesis for cons cell, but " << top() << " found"));
                pop();
                result.prepend(Symbol::Cons);
            } else {
                while (top() != Symbol::ParClose) {
                    result.append(ITEM());
                }
                pop(); // ')'
            }
        }
        return result;
            /*

        
        while (true) {
            if (eof())
                throw std::runtime_error("Unterminated list");
            if (top() == Symbol::ParClose)
                break;
            result.append(ITEM());
        }
        pop(); // ')'
        return result;
        */
    }

    Value Parser::SOURCE() {
        List result;
        while (! eof()) {
            result.append(ITEM());
        }
        return result;
    }
    
} // namespace tlisp


#endif