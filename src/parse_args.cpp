
#include "parse_args.h"
#include "flags.h"

#include <iostream>
#include <cstring>

int char_to_int(char c){
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -999;
    }
}

//non-inclusive funciton
int str_to_int(const char * chs, int &begin, char end){
    int k=0, i=0, p=1;
    int l = begin;
    while(chs[begin] != end){
        begin++;
    }
    for(int i=begin-1; i>=l ; i--){
        // std::cout << chs[i] << " -> " << char_to_int(chs[i]) << std::endl; //debugging
        k += char_to_int(chs[i])*p;
        p *= 10;
    }
    return k;
}

// //non-inclusive funciton
// const char * substring(const char * chs, int &begin, char end){
//
//     int l = strlen(chs);
//     char * c;
//     int k=0;
//     for(; begin<l ; begin++){
//         if(chs[begin] == end)
//             break;
//         c[k++] = chs[begin];
//         // std::cout << chs[begin] << std::endl;
//     }
//     // std::cout << "reached " << __LINE__ << std::endl;//////////////////////
//     // std::cout << "k " << k << std::endl;
//     char *c2 = new char[k];
//     strncpy(c2, c, 2);
//     // std::cout << strncpy(c2, c, 2) << std::endl;
//     // std::cout << "len <> c2 "<< strlen(c2) << " " << c2 << std::endl ;//////////////
//     return c2;
// }

int characterSetLegth(int *arr, int len){
    int l=0;
    if (len%2 !=0) {
        std::cout << "odd number of position" << std::endl;
        return -1;
    }
    for(int i=0; i<len ; i += 2){
        l += (arr[i+1] - arr[i]) + 1;
    }
    return l;
}

const char * get_char_set(const char * chs){
    int char_set_len = 0;
    bool flag = false;
    int arr[256];
    int chars[100];
    int k=0, k1=0;
    int chs_len = strlen(chs);
    if(debugging){
        std::cout << "function get_char_set() File entered " << " ->FILE:LINE "<<__FILE__  << std::endl;
        std::cout << "char_set , char_set_len : " << chs << "," << chs_len << " ->LINE " << __LINE__ << std::endl;
    }

    for(int i=0 ; i<chs_len ; i++){
        switch (chs[i]){
            case '-':
                if(debugging){
                    std::cout << "case \'-\' ->LINE "<< __LINE__ << std::endl;
                }
                break;
            case ',':
                if(debugging){
                    std::cout << "case \',\' ->LINE "<< __LINE__ << std::endl;
                }
                break;
            case '\\':
                if(debugging){
                    std::cout << "case \'\\\' ->LINE "<< __LINE__ << std::endl;
                }
                chars[k1++] = int(chs[i+1]);
                i++;
                break;
            case '[':
                if(debugging){
                    std::cout << "case \'[\' ->LINE "<< __LINE__ << std::endl;
                }
                i++;
                // std::cout << "reached " << __LINE__ << std::endl;//////////////////////
                // arr[k++] = atoi(substring(chs, i, '-'));
                arr[k++] = str_to_int(chs, i, '-');

                i++;
                // arr[k++] = atoi(substring(chs, i, ']'));
                arr[k++] = str_to_int(chs, i, ']');
                if(debugging){
                    std::cout << arr[k-2] << " ->LINE "<< __LINE__ << std::endl;
                    std::cout << arr[k-1] << " ->LINE "<< __LINE__ << std::endl;
                }
                break;

            case '(':
                if(debugging){
                    std::cout << "case \'(\' ->LINE "<< __LINE__ << std::endl;
                }
                i++;
                arr[k++] = int(chs[i]);
                i += 2;
                arr[k++] = int(chs[i]);
                if(debugging){
                    std::cout << arr[k-2] << " ->LINE "<< __LINE__ << std::endl;
                    std::cout << arr[k-1] << " ->LINE "<< __LINE__ << std::endl;
                }
                i++;
                break;
            default:
                if(debugging){
                    std::cout << "default ->LINE " << __LINE__ << std::endl;
                }
                chars[k1++] = int(chs[i]);

        }
    }

    char_set_len = characterSetLegth(arr, k) + k1;
    if(debugging){
        std::cout << "char_set_len, k , k1 :" << char_set_len << ", " << k << ", " << k1 <<" ->LINE " << __LINE__ << std::endl;
    }
    char * char_set = new char[char_set_len];
    // if(debugging){
    //     for(int i=0 ; i<k ; i++){
    //         std::cout << i << " -> " << arr[i] << std::endl;
    //     }
    // }
    //stores char() from each pair of arr array
    
    int l=0;
    for(int i=0 ; i<k ; i+=2){
        for(int j=arr[i]; j<= arr[i+1]; j++){
            // str.append(char(j));/////////////
            char_set[l++] = char(j);
        }
    }
    for(int i=0; i<k1; i++){
        // std::cout << char(chars[i]) << " ";///////////
        // str.append(char(i));/////////////
        char_set[l++] = char(chars[i]);
    }
    // std::string str(char_set);////////////
    // std::cout << char_set << std::endl;////////////
    // std::cout << str.substr(0, char_set_len) << std::endl;////////////
    //ensures that only the relevent characters passes
    char *c = new char[char_set_len];
    strncpy(c, char_set, char_set_len);
    if(debugging){
        // std::cout << "len : set -> " << strlen(c) << " : " << c << std::endl;
        std::cout << "function get_char_set() File exiting " << " ->FILE:LINE "<<__FILE__  << std::endl;
    }
    return c;
    // return str.substr(0, char_set_len).c_str();
}
