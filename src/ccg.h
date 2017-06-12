
#ifndef CCG_CCG_H
#define CCG_CCG_H

#include <cstdlib>
#include <ctime>

extern bool verbose;

void ccg(const char *char_set, size_t char_set_len,
     const size_t WIDTH,  const char * filename);// NAF -> Not A File

void help();    // reads from a file and then prints them out
void help2();   // prints from raw-string defined within the function

double print_time_interval(clock_t t0, clock_t t1, bool flag);

size_t count_combination(size_t char_set_len, size_t width);

#endif
