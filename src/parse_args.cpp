
#include "parse_args.h"
#include "flags.h"
#include <iostream>
#include <cstring>


//non-inclusive funciton
const char * substring(const char * chs, int &begin, char end){
    int l = strlen(chs);
    char * c;
    int k=0;
    for(; begin<l ; begin++){
        if(chs[begin] == end)
            break;
        c[k++] = chs[begin];
    }
    return c;
}

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
        std::cout << chs << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
        std::cout << chs_len << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
    }
    for(int i=0 ; i<chs_len ; i++){
        if (debugging) {
            std::cout << chs[i] << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
        }
        switch (chs[i]){
            case '-':
                if(debugging)
                    std::cout << "case -" << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                break;
            case ',':
                if(debugging)
                    std::cout << "case ," << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                break;
            case '\\':
                if(debugging)
                    std::cout << "case \\" << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                chars[k1++] = int(chs[i+1]);
                i++;
                break;
            case '[':
                if(debugging)
                    std::cout << "case [" << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                i++;
                arr[k++] = atoi(substring(chs, i, '-'));
                if(debugging)
                    std::cout << arr[k-1] << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                i++;
                arr[k++] = atoi(substring(chs, i, ']'));
                if(debugging)
                    std::cout << arr[k-1] << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                break;
            case '(':
                if(debugging)
                    std::cout << "case (" << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                i++;
                arr[k++] = int(chs[i]);
                if(debugging)
                    std::cout << arr[k-1] << " -> " << chs[i] << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                i += 2;
                arr[k++] = int(chs[i]);
                if(debugging)
                    std::cout << arr[k-1] << " -> " << chs[i] << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                i++;
                break;
            default:
                if(debugging)
                    std::cout << "default" << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
                chars[k1++] = int(chs[i]);

        }
    }

    char_set_len = characterSetLegth(arr, k) + k1;
    if(debugging)
        std::cout << "char_set_len, k " << char_set_len << ", " << k << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
    char * char_set = new char[char_set_len];
    if(debugging){
        for(int i=0 ; i<k ; i++){
            std::cout << i << " -> " << arr[i] << "FILE:LINE "<<__FILE__ << ":" << __LINE__ << std::endl;
        }
    }

    //stores char() from each pair of arr array
    int l=0;
    for(int i=0 ; i<k ; i+=2){
        for(int j=arr[i]; j<= arr[i+1]; j++){
            char_set[l++] = char(j);
        }
    }
    for(int i=0; i<k1; i++){
        char_set[i+l] = char(chars[i]);
    }

    // for(int i=0 ; i < char_set_len ; i++){
    //     std::cout << char_set[i] << ' ';
    // }
    return char_set;
}
