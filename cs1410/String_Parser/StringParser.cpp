//
//  StringParser.cpp
//  String_Parser
//
//  Created by Steven Proctor on 2/29/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

#include "StringParser.hpp"

/**
 * @brief The constructor
 */
StringParser::StringParser(void)
{
    // Empty
}

/**
 * @brief Parse a file line by line
 *
 * @param pFileName The file name
 *
 * @return True if parse was successful, else false
 */

bool StringParser::parseFile(const char* pFileName)
{
    bool ret = true;
    std::ifstream file(pFileName, std::ifstream::in);
    
    if (file.is_open())
    {
        char aLine[MAX_LINE_LENGTH];
        
        memset(aLine, 0, MAX_LINE_LENGTH);
        
        while (!file.eof() && ret)
        {
            file.getline(aLine, MAX_LINE_LENGTH);
            
            int length = strlen(aLine);
            if (length > 0)
            {
                ret = parseLine(aLine, length);
                printf("\n");
                memset(aLine, 0, length);
            }
        }
        
        if (ret)
        {
            printf("Parsing of file %s is complete\n", pFileName);
        }
        
        file.close();
    }
    else
    {
        ret = false;
    }
    
    return ret;
}

/**
 * @brief Parse a line of the input file
 *
 * @param pLine The input line
 * @param length the length of the input file
 *
 * @return True if line was successfully parse, else false
 */
bool StringParser::parseLine(const char* pLine, int length)
{
    // TODO
    if (pLine[1] != 'N') {
        switch(pLine[0]) {
            case 'I': printf("Integer: %i\n",parseInt(pLine));
                break;
            case 'F': printf("Float: %f\n",parseFloat(pLine));
                break;
            case 'D': printf("Double: %f\n",parseDouble(pLine));
                break;
            case 'S': printf("String:%s\n",parseString(pLine));
                break;
            case 'Y': separateArguement(pLine);
                break;
        }
    }
    else {
        separateCommand(pLine);
       // parseCommand(pLine, <#char delimiter#>, <#const char *pArgument#>)
    }
    return true;
}

/**
 * @brief Parse a command
 *
 * @param pCommand The command string
 * @param delimiter The delimiter between command and arguments
 * @param pArgument The command argument
 *
 * @return True if successfully parsed, else false
 */
bool StringParser::parseCommand(const char* pCommand, const char* pArgument)
{
    // TODO
    char str[MAX_LINE_LENGTH];
    char subStr[MAX_LINE_LENGTH];
    char location, length;
    int j;
    
    if (strcmp(pCommand, "INPUT") == 0) {
        for (int i = strlen(str); i >= 0; i--) {
            str[i] = '\0';
        }
        j = 0;
        for (int i = 0; i < strlen(pArgument); i++) {
            str[j++] = pArgument[i];
        }
        str[strlen(pArgument)] = '\0';
    }
    
    if (strcmp(pCommand, "CONCAT") == 0) {
        strcat (str, pArgument);
        printf("Concat: %s\n", str);
    }
    else if (strcmp(pCommand, "SUBSTRING") == 0) {
            location = *pArgument;
            time++;
    }
    else if (time > 0) {
        length = *pArgument;
        j = 0;
        for (int i = (location-48); i < ((location-48) + (length-48)); i++) {
            subStr[j++] = str[i];
        }
        subStr[j] = '\0';
        printf("Substring: %s\n", subStr);
    }
    
    
    return true;
}

/**
 * @brief Convert a double string into a double
 *
 * @param pDouble The string containing the double
 *
 * @return A double
 */
double StringParser::parseDouble(const char* pDouble)
{
    // TODO
    if(pDouble[1]!= ':') {
        printf("Error\n");
        exit(34);
    }
    
    double d;
    d = atof(&pDouble[2]);
    return d;
}

/**
 * @brief Convert a float string into a float
 *
 * @param pFloat The string containing the float
 *
 * @return The float
 */
float StringParser::parseFloat(const char* pFloat)
{
    // TODO
    if(pFloat[1]!= ':') {
        printf("Error\n");
        exit(34);
    }
    
    float f;
    f = atof(&pFloat[2]);
    return f;
}

/**
 * @brief Convert an integer string into an integer
 *
 * @param pInt The string containing the integer
 *
 * @return The integer
 */
int StringParser::parseInt(const char* pInt)
{
    // TODO
    if(pInt[1]!= ':') {
        printf("Error\n");
        exit(34);
    }
    
    int i;
    i = atoi(&pInt[2]);
    return i;
}

/**
 * @brief Convert a constant character string into a c-string
 *
 * @param pString The original string
 *
 * @return The new c-string
 */
char* StringParser::parseString(const char* pString)
{
    // TODO
    if(pString[1]!= ':') {
        printf("Error\n");
        exit(34);
    }
    
    char * str;
    str = strstr(pString, "S:");
    strncpy(str, "  ", 2);
    
    //char str[MAX_LINE_LENGTH];
    //strncpy(str, pString, sizeof(str));
    return str;
}

// TODO Place any extra functions below here

void StringParser::separateArguement(const char * pLine) {
    char argument[MAX_LINE_LENGTH];
    int tildaLocation1, tildaLocation2;
    int start = 0;
    
    tildaLocation1 = locateTilda(pLine, start);
    start = tildaLocation1;
    while (start != strlen(pLine)) {
        tildaLocation2 = locateTilda(pLine, start);
        start = tildaLocation2;
        int j = 0;
    for (int i = tildaLocation1 + 1; i < tildaLocation2; i++) {
        argument[j++] = pLine[i];
    }
        parseLine(argument, start);
        tildaLocation1 = tildaLocation2;
        for (int i = 0; i < j; i++) {
            argument[i] = '\0';
        }
    }
}

void StringParser::separateCommand(const char * pLine) {
    char command[MAX_LINE_LENGTH];
    char arguement[MAX_LINE_LENGTH];
    int colonLocation1, colonLocation2;
    int start = 0;
    
    colonLocation2 = locateColon(pLine, start);
    start = colonLocation2;
    
    int j = 0;
    for (int i = 0; i < colonLocation2; i++) {
        arguement[j++] = pLine[i];
    }
    
    while (start != strlen(pLine)) {
        if (strcmp(command, "INPUT") != 0) {
            for (int i = strlen(command); i >= 0; i--) {
                command[i] = '\0';
            }
            strncpy(command, arguement, sizeof(arguement));
        }
        else if (strcmp(command, "CONCAT") != 0) {
            for (int i = strlen(command); i >= 0; i--) {
                command[i] = '\0';
            }
            strncpy(command, arguement, sizeof(arguement));
        }
        else if (strcmp(command, "SUBSTRING") != 0) {
            for (int i = strlen(command); i >= 0; i--) {
                command[i] = '\0';
            }
            strncpy(command, arguement, sizeof(arguement));
        }
        
        colonLocation1 = locateColon(pLine, start);
        start = colonLocation1;
        j = 0;
        for (int i = colonLocation2 + 1; i < colonLocation1; i++) {
            arguement[j++] = pLine[i];
        }
        arguement[j] = '\0';

        parseCommand(command, arguement);
        colonLocation2 = colonLocation1;
        for (int i = 0; i < j; i++) {
            command[i] = '\0';
            arguement[i] = '\0';
        }
        
        colonLocation1 = locateColon(pLine, start);
        start = colonLocation1;
        
        j = 0;
        for (int i = colonLocation2 + 1; i < colonLocation1; i++) {
            arguement[j++] = pLine[i];
        }
        arguement[j] = '\0';
        colonLocation2 = colonLocation1;
    }
    parseCommand(command, arguement);
}

int StringParser::locateTilda(const char * tempLine, int start) {
    int location;
    for (int i = start + 1; i < strlen(tempLine); i++) {
        if (tempLine[i] == '~') {
                location = i;
            return location;
        }
    }
    location = strlen(tempLine);
    return location;
}

int StringParser::locateColon(const char * tempLine, int start) {
    int location;
    for (int i = start + 1; i < strlen(tempLine); i++) {
        if (tempLine[i] == ':') {
            location = i;
            return location;
        }
    }
    location = strlen(tempLine);
    return location;
}