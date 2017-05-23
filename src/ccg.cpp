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
