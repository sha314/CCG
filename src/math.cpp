size_t factorial(size_t n){
    double a=1;
    while(n > 0) a *= n--;
    return a;
}

//finds the permutation function nPr
size_t nPr(size_t n, size_t r){
    return factorial(n) / factorial(r);
}

//finds the Combination function nCr
size_t nCr(size_t n, size_t r){
    return factorial(n) / (factorial(r) * factorial(n-r));
}
