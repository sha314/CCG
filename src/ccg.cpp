// Character Combination Generator (CCG)
//Recursive Character Combination Generator (RCCG)

//compile with
// g++ src\ccg.cpp -std=c++11 -o debug\ccg.exe && debug\ccg.exe
// g++ src\ccg.cpp -std=c++11 -o debug\ccg.exe && debug\ccg.exe -w 2 -f test.txt -s -t

#include "ccg.h"


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

bool verbose = false;

//functions
void ccg(const char *char_set, size_t char_set_len,
     const size_t WIDTH,  const char * filename="\0")
{
    std::string s="\0";
    ofstream fout;

    //open the filename file if the filename is valid
    if (strcmp(filename, "\0")) {
        fout.open(filename);
    }
    //using a general stream object
    std::ostream &out = (!strcmp(filename, "\0")) ?  std::cout : fout;//TODO

    int index[WIDTH];
    for(size_t i=0; i < WIDTH ; i++){
        index[i] = 0;
    }
    // run a loop as long as index[0]  < char_set_len
    while (index[0] < char_set_len) {

        for(int i=0 ; i < WIDTH ; i++){
            if(verbose) {
                //prints index
                s.append(" [");
                s.append(std::to_string(i));
                s.append("] ");
                s.append(std::to_string(index[i]));
            }
            //prints character combination
            out << char_set[index[i]];
        }
        if (verbose) {
            out << " <-" << s;
            s="\0";
        }
        out << endl;

        index[WIDTH-1] ++;//increase index at each iteretion
        for(int i=WIDTH-1 ; i > 0 ; i--){ // check index limit
            if (index[i] >= char_set_len) {
                //increase previous order value when current order value is reached its limit
                index[i] = 0;
                index[i-1] ++;
            }
        }
    }
    // out.close();
    if (fout.is_open()) {// close the file only when it is open
        fout.close();
    }

}

void help(){
    ifstream fin("manual/rccg_manual.txt");
    if (!fin) {
        std::cout << "\"manual/rccg_manual.txt\" File not found" << endl;
        return;
    }
    string text;
    while(!fin.eof())
    {
        getline(fin, text);
        if (text[0]=='#') {
            //if the first character is a hash-tag
            continue;
        }
        cout << "" << text << "\n" ;
    }
    fin.close();
}

void help2(){
    std::string hlp = R"**(
#Character Combination Generator (CCG)

Created by : Shahnoor

Usage: ccg [OPTION]

List help about the ccg program.

Mandatory arguments to long options are mandatory for short options too.
    -c, --char_set      The character set which to be used. If not specified all the
                        printable characters of ASCII standard will be used.

    -f,	--file          The file where the output will be store.
                        If not specified the information will be sent to standard output.
                        The file will be created but if the file exists program will exit.

    -h,	--help          display this help and exit

    -m,	--max_size      Maximum file size in KB.

    -s, --statistics    Turns on the statics argument

        --schar         To specify separation character. By default it is newline character
                        or '\n'

    -t, --time          Turns on the time flag. Print time taken to do the job. Bu default it prints the
                        time taken to generate the output.

    -v,	--verbose       Information about index will be directed to the output

    	--version       output version information and exit

    -w,	--width         Width of the combination


Special Characters:
    1. '\' (back slash) as an escape character.

    2. '-' (dash) to set a range, e.g., "A-Z" to set "ABCDEFGHIJKLMNOPQRSTUVWXYZ" or

    3. ',' (comma) to set multiple range, e.g., "A-Z,a-z" to set
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

    4. '[' and ']' (square brackets) to use ASCII character numbering to select character, e.g.,
            "[65-90]" to set "ABCDEFGHIJKLMNOPQRSTUVWXYZ" or
            "[65-90],[97-122]" to set "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz".
            "[0x41-0x54]" is in hexadecimal fomar but does the same thing as "[65-90]".

    5. '(' and ')' (parentheses) to use ASCII character to select character, e.g.,
            "(a-z)" to set "abcdefghijklmnopqrstuvwxyz".
            "(A-Z),(a-z)" to set "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz".


Exit status:
    0  if OK,
    1  Missing one or more argument.
    2  File exists.
    3  Invalid file name or file name is not given.
    4  Permission denied to create new file.
    5  Invalid character set

    )**";
    std::cout << hlp << std::endl;
}

double print_time_interval(clock_t t0, clock_t t1, bool flag=false){
    double t = double(t1-t0)/CLOCKS_PER_SEC;
    if(flag)
        cout << "Total time taken by the program is " << t << " sec" << endl;
    return t;
}

size_t count_combination(size_t char_set_len, size_t width){
    double a = 1;
    for(size_t i=0; i < width ; i++){
        a *= char_set_len;
    }
    return a;
}
