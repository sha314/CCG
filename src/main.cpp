// g++ src\main.cpp -std=c++11 -o debug\main.exe && debug\main.exe

#include "ccg.h"
#include "parse_args.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <cstring>

using namespace std;

//global variables
bool print_time = false;
bool statistics_flag = false;
const char* filename="\0";
const char* char_set="!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
size_t width=0;
clock_t t;
const char *special_chars = "\\-,[]";

constexpr unsigned int str2int(const char* str, int h=0)
{
    // converts string to integer
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

int main(int argc, char const *argv[]) {

    if (argc==1) {
        cout << "No argument found!!!" << endl;
        help();
        return 0;
    }
    cout << "Character Combination Generator (CCG)" << endl << endl;

    //starts parsing arguments
    for(int i=1 ; i < argc ; i++){
        switch (str2int(argv[i])) {
            case str2int("-c"):
            case str2int("--char_set"):
                if (i+1 < argc) {//ensures that argument exists
                    char_set=get_char_set(argv[i+1]);
                    i++;
                }else{
                    cout << "Argument is not given for \'-c\'" << endl;
                    cout << "Try \'-h\' argument for help" << endl;
                    return 1;
                }
                break;

            case str2int("-f"):
            case str2int("--file"):
                if (i+1 < argc) {//ensures that argument exists
                    filename = argv[i+1];
                    i++;
                }else{
                    cout << "File name is not given" << endl;
                    cout << "Try \'-h\' argument for help" << endl;
                    return 3;
                }
                break;

            case str2int("-h"):
            case str2int("--help"):
                help();
                return 0;
                break;

            case str2int("-s"):
            case str2int("--statistics"):
                statistics_flag = true;
                break;
            case str2int("-t"):
            case str2int("--time"):
                print_time = true;
                break;

            case str2int("-v"):
            case str2int("--verbose"):
                verbose = true;
                break;

            case str2int("-w"):
            case str2int("--width"):
                cout << "--width" << endl;////////////debugging
                if (i+1 < argc) {//ensures that argument exists
                    width = atoi(argv[i+1]);
                    i++;
                }else{
                    cout << "String width is not specified (argument \'-w\' is not given)" << endl;
                    cout << "Try \'-h\' argument for help" << endl;
                    return 1;
                }
                cout << width << endl;////////////debugging
                break;

            default:
                cout << "No argument found!!!" << endl;
                help();
                return 1;
        }
    }
    //end parsing arguments

    if (width == 0) {
        cout << "String width is not valid" << endl;
        return 1;
    }
    size_t len = strlen(char_set);
    if (statistics_flag){//when statistics_flag is on view some information
        size_t sn = count_combination(len, width); //string number
        //each line contains a string of (width+1) characters. The +1 must be included
        //because of the newline character
        double size = (double)sn*(width+1)/(1024); // in Kilo bytes (KB)
        cout << "Character set used   " << char_set << endl;
        cout << "Total number of string " << sn << endl;
        cout << "Required space " << size << " KB or " << size/1024 << " MB" << endl;
    }

    if (print_time) { t = clock(); }
    ccg(char_set, len, width, filename);// TODO does not work when filename=="\0"
    if (print_time) {print_time_interval(t, clock(), true);}

    return 0;
}
