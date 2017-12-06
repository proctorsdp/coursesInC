//
//  StringParser.hpp
//  String_Parser
//
//  Created by Steven Proctor on 2/29/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef _STRING_PARSER_HPP
#define _STRING_PARSER_HPP

/**
 * @class StringParser
 *
 * @brief A class used to parse a set of string conversion and manipulation arguments
 */
class StringParser
{
public:
    StringParser();
    
    bool parseFile(const char* pFile);
    
    /**
     * @brief Important values
     */
    enum
    {
        MAX_LINE_LENGTH = 1000,
        
        // TODO add enums as needed
        INPUT = 'INPUT',
        CONCAT = 'CONCAT',
        SUBSTR = 'SUBSTRING'
    };
    
private:
    bool parseCommand(const char* pCommand, const char* pArgument);
    bool parseLine(const char* pLine, int length);
    
    double parseDouble(const char* pDouble);
    float parseFloat(const char* pFloat);
    int parseInt(const char* pInt);
    char * parseString(const char* pString);
    
    
    // TODO Implement any needed functions below here
    void separateArguement(const char * pLine);
    void separateCommand(const char * pLine);
    int locateTilda(const char * tempLine, int start);
    int locateColon(const char * tempLine, int start);
    int time = 0;
};

#endif //_STRING_PARSER_HPP