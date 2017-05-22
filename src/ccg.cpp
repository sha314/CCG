// Character Combination Generator (CCG)
//Recursive Character Combination Generator (RCCG)

//compile with
// g++ src\ccg.cpp -std=c++11 -o debug\ccg.exe && debug\ccg.exe
// g++ src\ccg.cpp -std=c++11 -o debug\ccg.exe && debug\ccg.exe -w 2 -f test.txt -s -t
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

//global variables
bool verbose = false;
bool print_time = false;
bool statistics_flag = false;
bool help_flag = false;
const char* filename="\0";
const char* char_set="!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
size_t width=0;
clock_t t;
const char *special_chars = "\\-,[]";


//functions
void ccg(const char *char_set, size_t char_set_len,
     const size_t WIDTH,  const char * filename='\0')
{
    std::string s="\0";
    ofstream fout(filename);
    std::ostream &out = (filename != "\0") ? fout : cout;
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
}

void help(){
    ifstream fin("man/rccg_manual.txt");
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

// void rccg_func_test(){
//     clock_t t0 = clock();
//     // rccg("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26, 4);
//     ccg("QWERTYUIOPLKJHGFDSAZXCVBNM", 26, 5, "char5.txt");
//     cout << "Time taken " << (double)(clock()-t0)/CLOCKS_PER_SEC << " sec" << endl;
// }

constexpr unsigned int str2int(const char* str, int h = 0)
{
    // converts string to integer
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

const char * get_char_set(const char* c){
    //parse the char_set from command line argument
    size_t a1, a2, l = strlen(c);
    if (c[0] == '\"') {
        a1 = int(c[1]);
        a2 = int(c[l-1]);
    }
    cout << a1 << "\t" << a2 << endl;
    char *chs = new char[a2-a1];
    for(size_t i=0; i<= a2-a1 ; i++){
        chs[i] = char(i+a1);
    }
    cout << chs << endl; ////////////// debugging
    return chs;
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


int main(int argc, char const *argv[]) {

    if (argc==1) {
        cout << "No argument found!!!" << endl;
        help();
        return 0;
    }
    cout << "Character Combination Generator (CCG)" << endl << endl;
    // cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

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

            case str2int("-h"):
            case str2int("--help"):
                help_flag = true;
                return 0;

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
                if (i+1 < argc) {//ensures that argument exists
                    width = atoi(argv[i+1]);
                    i++;
                }else{
                    cout << "String width is not specified (argument \'-w\' is not given)" << endl;
                    cout << "Try \'-h\' argument for help" << endl;
                    return 1;
                }
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
    if (filename == "\0") {// when no file name is given
        if (print_time) { t = clock(); }
        ccg(char_set, len, width);
        if(print_time){print_time_interval(t, clock(), true);}
        return 0;
    }
    if (filename != "\0") {//when there is a filename given
        if (print_time) { t = clock(); }
        ccg(char_set, len, width, filename);
        if (print_time) {print_time_interval(t, clock(), true);}
        return 0;
    }

    return 0;
}
