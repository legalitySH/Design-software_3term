#include "stdafx.h"
#include "In.h"
#include "Error.h"
namespace In
{
    IN getin(wchar_t infile[])
    {
        IN in;
        in.size = 0;
        in.lines = 1;
        in.ignore = 0;
        int col = 1;

        unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];

        std::ifstream fin(infile);
        if (fin.fail())
            throw ERROR_THROW(110);

        while (in.size < IN_MAX_LEN_TEXT)
        {
            char c;
            fin.get(c);
            unsigned char x = c;

            if (fin.eof())
            {
                text[in.size] = '\0';
                break;
            }

            if (x == IN_CODE_ENDL)
            {
                text[in.size] = '|';
                in.lines++;
                col = 1;
                in.size++; 
            }
            else
            {
                switch (in.code[x])
                {
                case in.T:
                    text[in.size] = x;
                    in.size++;
                    col++;
                    break;
                case in.I:
                    in.ignore++;
                    col++;
                    break;
                case in.F:
                    throw ERROR_THROW_IN(111, in.lines, col);
                    break;
                default:
                    text[in.size] = in.code[x];
                    in.size++;
                    col++;
                    break;
                }
            }
        }
        in.text = text;
        return in;
    }

}
