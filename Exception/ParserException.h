//
// Created by robbe on 10-3-2022.
//

#ifndef CAR_SIMULATOR_PARSEREXCEPTION_H
#define CAR_SIMULATOR_PARSEREXCEPTION_H
#include <iostream>
#include <exception>

class ParserException : public std::exception{
    const char* message;
public:
    ParserException (const char* messages):
        message(messages){}
    const char* what () const throw(){
        return message;
    }
};


#endif //CAR_SIMULATOR_PARSEREXCEPTION_H
