#include "InfInt.h"
#include <iostream>
#include <string>
#include <sstream>
#include <utility> //std::pair
#include <iterator>
#include <algorithm>
#include <time.h> //calc runtime of program
#include <list>
#include <vector>
#include <map>

typedef InfInt bigint;

class prime {
    private:
        int i;
        bigint b;
    public:
        prime(bigint &b_int, int index) {
            b = b_int;
            i = index;
        }
        bool cont(prime &prev) {
            if (prev.get_ind() > i)
                return false;
            return true;
        }
        int get_ind() {
            return i;
        }
        bigint get_bigint() {
            return b;
        }
        void set_ind(int new_i) {
            i = new_i;
        }
        void set_bigint(bigint &b_new) {
            b = b_new;
        }
};

/*
InfInt utility functions
*/
int get_last_digit(bigint &b)
{
    std::string s = b.toString();
    return s.at(s.length()-1) - '0';
}
bool is_even(bigint &b)
{
    int ld = get_last_digit(b);
    return ld % 2 == 0;
}

/*
This function returns the next possible prime
A Possible Prime is determined as a number which ends in either 1,3,7,9
*/
bigint get_next_poss(bigint &b)
{
    if (is_even(b)) {                                               // Check if b is even
        b += 1;                                                      // If even make b odd by adding one
        int ld = get_last_digit(b);
        if (ld != 5)                                                 // If b doesn't end in 5 return
            return b;
    }

    // If b is not even then it must be an odd number
    int ld = get_last_digit(b);
    if (ld == 3)                                                     // If b is currently ending in 3 then add 4 to get next prime
        return b + 4;
    return b + 2;                                                    // Else adding 2 to the number will produce the next possible prime
}

/*
This functions returns the maximum possible prime which can be determined in the current iteration
*/
bigint min_next_poss(bigint &b)
{
    bigint maxNxt = b * 3;

    if (is_even(maxNxt)) {
        maxNxt -= 1;                                                    // If the maxVal is even subtract 1 to make odd
        int ld = get_last_digit(maxNxt);
        if (ld != 5)                                                    // If this val is not ending in 5 return it
            return maxNxt;
    }

    int ld = get_last_digit(maxNxt);
    if (ld == 7)                                                        // If this val is odd and ending in 7 return the previous poss prime ending in 3.
        return maxNxt - 4;
    return maxNxt - 2;                                      // If val is odd and not ending in 7 then return val-2
}

/*
This function, given starting and ending possible primes, will return a linkedhashmap
containing a list of possible primes between the two poss primes.
This function assumes => s = starting possible prime, e = ending possible prime
The BigInteger value in p is the possible prime, and the Boolean value is initially set to true
*/
std::map<bigint, bool> get_poss_array(bigint &s, bigint &e)
{
    std::map<bigint, bool> p;
    for (bigint b = s; b <= e; b+=2) {
        p.insert(std::make_pair(b, true));
        if (get_last_digit(b) == 3)
            b += 2;
    }

    return p;
}

int main(int argc, char** argv)
{
    /*Initial Value Set*/
    std::vector<bigint> comb;   
    bigint ini3 = 3;    
    comb.push_back(ini3);
    
    std::vector<prime> primes; 
    prime ini_p(ini3, 0); 
    primes.push_back(ini_p);

    bigint start = get_next_poss(ini3);
    bigint end = min_next_poss(start);
    std::map<bigint, bool> poss = get_poss_array(start, end);

    std::istringstream iss( argv[1] );
    int iter;
    iss >> iter;

    clock_t start_time, end_time;
    start_time = clock();

    int prime_print_ind = 0;
    /*Iteration*/
    for (int z=0; z<iter; z++) {
        int max_ind = comb.size();
        for (std::vector<prime>::iterator p=primes.begin(); p!=primes.end(); ++p) {
            int index = p -> get_ind();
            bigint curB = p -> get_bigint();

            for (int i=index; i<max_ind; i++) {
                bigint mTmp = curB * comb.at(i);
                if (mTmp > end)
                    break;
                poss[mTmp] = false;
                p -> set_ind(p -> get_ind()+1);
            }
            max_ind = p -> get_ind();
        }
        for (std::map<bigint, bool>::iterator it=poss.begin(); it!=poss.end(); ++it) {
            bigint key = it -> first;
            bool value = it -> second;
            comb.push_back(key);
            if (value == true) {
                prime new_tmp_prime(key, comb.size()-1);
                primes.push_back(new_tmp_prime);
            }
        }

        // for (int print_st=prime_print_ind; print_st < primes.size(); print_st++)
        //     std::cout << ((primes.at(print_st)).get_bigint()).toString() << std::endl;

        // prime_print_ind = primes.size();
        // std::cout << "Iteration: " << z << std::endl;

        if (z+1 != iter) {
            bigint nxt_start = primes.at(primes.size()-1).get_bigint();
            start = get_next_poss(nxt_start);
            end = min_next_poss(start);
            poss = get_poss_array(start, end);
        }
    }

    for (int print_st=0; print_st < primes.size(); print_st++)
        std::cout << ((primes.at(print_st)).get_bigint()).toString() << std::endl;

    // prime_print_ind = primes.size();
    // std::cout << "Iteration: " << z << std::endl;

    end_time = clock();
    float run_time (((float)end_time - (float)start_time) / (CLOCKS_PER_SEC/1000));
    std::cout << "Time for C++ PrimeFactor Algo: " << run_time  << " ms" << std::endl;
}
