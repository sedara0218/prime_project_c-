#include "bigint.h"
#include <iostream>
#include <string>
#include <sstream>
#include <utility> //std::pair
#include <iterator>
#include <algorithm>
#include <vector>

//Deconstructor
bigint::~bigint() {}

//Constructors
bigint::bigint() //bigint = 0
{
    neg_sign = false;
    num.push_back(0);
}

//Class Utility Functions
void bigint::parseToNum(std::string s)
{
    for (std::string::reverse_iterator itr=s.rbegin(); itr!=s.rend(); ++itr) {
        int cur_n = *itr - '0';
        bigint::num.push_back(cur_n);
    }

    int zero_ind = 0;
    for (std::vector<int>::reverse_iterator itr=num.rbegin(); itr!=num.rend(); ++itr) {
        if (*itr == 0)
            zero_ind++;
        else
            break;
    }
    if (zero_ind == num.size()) {
        std::vector<int> new_num;
        new_num.push_back(0);
        num = new_num;
    }
    else {
        std::vector<int> new_num_zeroSplice(num.begin(), num.end()-zero_ind);
        num = new_num_zeroSplice;
    }
}

std::string bigint::to_string()
{
    std::string out = "";
    if (neg_sign)
        out += '-';
    for(std::vector<int>::reverse_iterator itr=num.rbegin(); itr!=num.rend(); ++itr)
        out += std::to_string(*itr);
    return out;
}

int bigint::size() const
{
    return num.size();
}

std::vector<int>::iterator bigint::begin()
{
    return num.begin();
}

std::vector<int>::iterator bigint::end()
{
    return num.end();
}

std::vector<int>::reverse_iterator bigint::rbegin()
{
    return num.rbegin();
}

std::vector<int>::reverse_iterator bigint::rend()
{
    return num.rend();
}

std::vector<int>::const_reverse_iterator bigint::crbegin() const
{
    return num.rbegin();
}

std::vector<int>::const_reverse_iterator bigint::crend() const
{
    return num.rend();
}

std::vector<int> bigint::getNum()
{
    return bigint::num;
}

bool bigint::getSign() const
{
    return neg_sign;
}

void bigint::setSign(bool new_neg_sign)
{
    neg_sign = new_neg_sign;
}

void bigint::setNum(std::vector<int> new_num)
{
    num = new_num;
}

bool bigint::is_even()
{
    int last_digit = get_last_digit();
    if (last_digit % 2 == 0)
        return true;
    return false;
}
int bigint::get_last_digit()
{
    if (num.size() >= 1)
        return num.at(0);
    return 0;
}
bigint bigint::abs()
{
    if (neg_sign)
        return negate();
    else
        return *this;
}
bigint bigint::negate() //-1 * *this
{
    bigint b_tmp = *this;
    if (b_tmp.getSign())
        b_tmp.setSign(false);
    else
        b_tmp.setSign(true);
    return b_tmp;

}


//Operator Overloading Functions
//= Set Equal comparator
void bigint::operator = (bigint &b)
{
    num = b.getNum();
    neg_sign = b.getSign();
}

// == Equal To comparator
bool bigint::operator == (bigint &b)
{
    if (neg_sign != b.getSign())
        return false;

    if (b.size() != num.size())
        return false;
    else {
        typedef std::vector<int>::iterator vecIter;
        for (std::pair<vecIter, vecIter> itr(num.begin(), b.begin()); itr.first != num.end() && itr.second != b.end(); ++itr.first, ++itr.second) {
            if (*itr.first != *itr.second)
                return false;
        }
        return true;
    }
}

//!= Not Equal comparator
bool bigint::operator != (bigint &b)
{
    if (*this == b)
        return false;
    return true;
}

//< Less than comparator
bool bigint::operator < (const bigint &b) const
{
    if (b.getSign() && !neg_sign)
        return false;
    else if (!b.getSign() && neg_sign)
        return true;
    else {
        if (b.size() > num.size()) {
            if (neg_sign)
                return false;
            return true;
        }
        else if (b.size() < num.size()) {
            if (neg_sign)
                return true;
            return false;
        }
        else {
            typedef std::vector<int>::const_reverse_iterator vecIter;
            for (std::pair<vecIter, vecIter> itr(num.rbegin(), b.crbegin()); itr.first != num.rend() && itr.second != b.crend(); ++itr.first, ++itr.second) {
                if (*itr.first > *itr.second) {
                    if (neg_sign)
                        return true;
                    return false;
                }
                else if (*itr.first < *itr.second) {
                    if (neg_sign)
                        return false;
                    return true;
                }
                if (itr.first+1 == num.rend()) {//most significant digit
                    if (*itr.first == *itr.second)
                        return false;
                }
            }
            if (neg_sign)
                return false;
            return true;
        }
    }
}
bool bigint::operator < (bigint &b)
{
    if (b.getSign() && !neg_sign)
        return false;
    else if (!b.getSign() && neg_sign)
        return true;
    else {
        if (b.size() > num.size()) {
            if (neg_sign)
                return false;
            return true;
        }
        else if (b.size() < num.size()) {
            if (neg_sign)
                return true;
            return false;
        }
        else {
            typedef std::vector<int>::const_reverse_iterator vecIter;
            for (std::pair<vecIter, vecIter> itr(num.rbegin(), b.crbegin()); itr.first != num.rend() && itr.second != b.crend(); ++itr.first, ++itr.second) {
                if (*itr.first > *itr.second) {
                    if (neg_sign)
                        return true;
                    return false;
                }
                else if (*itr.first < *itr.second) {
                    if (neg_sign)
                        return false;
                    return true;
                }
                if (itr.first+1 == num.rend()) {//most significant digit
                    if (*itr.first == *itr.second)
                        return false;
                }
            }
            if (neg_sign)
                return false;
            return true;
        }
    }
}

//> Greater than comparator
bool bigint::operator > (bigint &b)
{
    if (!b.getSign() && neg_sign)
        return false;
    else if (b.getSign() && !neg_sign)
        return true;
    else {
        if (b.size() < num.size()) {
            if (neg_sign)
                return false;
            return true;
        }
        else if (b.size() > num.size()) {
            if (neg_sign)
                return true;
            return false;
        }
        else {
            typedef std::vector<int>::reverse_iterator vecIter;
            for (std::pair<vecIter, vecIter> itr(num.rbegin(), b.rbegin()); itr.first != num.rend() && itr.second != b.rend(); ++itr.first, ++itr.second) {
                if (*itr.first < *itr.second) {
                    if (neg_sign)
                        return true;
                    return false;
                }
                else if (*itr.first > *itr.second) {
                    if (neg_sign)
                        return false;
                    return true;
                }
                if (itr.first+1 == num.rend()) {//most significant digit
                    if (*itr.first == *itr.second)
                        return false;
                }
            }
            if (neg_sign)
                return false;
            return true;
        }
    }
}

//<= Less than or Equal to comparator
bool bigint::operator <= (bigint &b)
{
    if (b.getSign() && !neg_sign)
        return false;
    else if (!b.getSign() && neg_sign)
        return true;
    else {
        if (b.size() > num.size()) {
            if (neg_sign)
                return false;
            return true;
        }
        else if (b.size() < num.size()) {
            if (neg_sign)
                return true;
            return false;
        }
        else {
            typedef std::vector<int>::reverse_iterator vecIter;
            for (std::pair<vecIter, vecIter> itr(num.rbegin(), b.rbegin()); itr.first != num.rend() && itr.second != b.rend(); ++itr.first, ++itr.second) {
                if (*itr.first > *itr.second) {
                    if (neg_sign)
                        return true;
                    return false;
                }
                else if (*itr.first < *itr.second) {
                    if (neg_sign)
                        return false;
                    return true;
                }
                if (itr.first+1 == num.rend()) {//most significant digit
                    if (*itr.first == *itr.second)
                        return true;
                }
            }
            if (neg_sign)
                return false;
            return true;
        }
    }
}

//>= Greater than or Equal to comparator
bool bigint::operator >= (bigint &b)
{
    if (!b.getSign() && neg_sign)
        return false;
    else if (b.getSign() && !neg_sign)
        return true;
    else {
        if (b.size() < num.size()) {
            if (neg_sign)
                return false;
            return true;
        }
        else if (b.size() > num.size()) {
            if (neg_sign)
                return true;
            return false;
        }
        else {
            typedef std::vector<int>::reverse_iterator vecIter;
            for (std::pair<vecIter, vecIter> itr(num.rbegin(), b.rbegin()); itr.first != num.rend() && itr.second != b.rend(); ++itr.first, ++itr.second) {
                if (*itr.first < *itr.second) {
                    if (neg_sign)
                        return true;
                    return false;
                }
                else if (*itr.first > *itr.second) {
                    if (neg_sign)
                        return false;
                    return true;
                }
                if (itr.first+1 == num.rend()) {//most significant digit
                    if (*itr.first == *itr.second)
                        return true;
                }
            }
            if (neg_sign)
                return false;
            return true;
        }
    }
}

//+ Addition
bigint bigint::operator + (bigint &b)
{
    if (b.getSign() && !neg_sign) {
        b.setSign(false);
        bigint subtract = *this - b;
        b.setSign(true);
        return subtract;
    }
    else if (!b.getSign() && neg_sign) {
        neg_sign = false;
        bigint subtract = b - *this;
        neg_sign = true;
        return subtract;
    }
    else {
        bool new_neg_sign = neg_sign;
        std::vector<int> new_num;
        typedef std::vector<int>::iterator vecIter;
        int carry = 0;
        for (std::pair<vecIter, vecIter> itr(num.begin(), b.begin()); itr.first != num.end() || itr.second != b.end(); ++itr.first, ++itr.second) {
            int newDig;
            if (itr.first == num.end()) {
                --itr.first;
                newDig = carry + *itr.second;
            }
            else if (itr.second == b.end()) {
                --itr.second;
                newDig = carry + *itr.first;
            }
            else
                newDig = carry + *itr.first + *itr.second;

            if (newDig > 9) {
                carry = 1;
                newDig -= 10;
            }
            else
                carry = 0;
            new_num.push_back(newDig);
        }
        if (carry != 0)
            new_num.push_back(carry);

        bigint b_ret;
        b_ret.setNum(new_num);
        b_ret.setSign(new_neg_sign);
        return b_ret;
    }
}

//- Subtraction
bigint bigint::operator - (bigint& b)
{
    if (b.getSign() && !neg_sign) {
        b.setSign(false);
        bigint sum = *this + b;
        b.setSign(true);
        return sum;
    }
    else if (!b.getSign() && neg_sign) {
        b.setSign(true);
        bigint sum = *this + b;
        b.setSign(false);
        return sum;
    }
    else {
        if (b.getSign() && neg_sign) {
            b.setSign(false);
            neg_sign = false;
            bigint sub = b - *this;
            b.setSign(true);
            neg_sign = true;
            return sub;
        }
        else {
            if (*this < b) {
                bigint sub = b - *this;
                sub.setSign(true);
                return sub;
            }
            else if (*this > b) {
                bool new_neg_sign = false;
                std::vector<int> new_num;
                typedef std::vector<int>::iterator vecIter;
                int borrow = 0;
                for (std::pair<vecIter, vecIter> itr(num.begin(), b.begin()); itr.first != num.end() || itr.second != b.end(); ++itr.first, ++itr.second) {
                    if (itr.second == b.end()) {
                        --itr.second;
                        if (*itr.first-borrow < 0) {
                            new_num.push_back(10+*itr.first-borrow);
                            borrow = 1;
                        }
                        else {
                            new_num.push_back(*itr.first-borrow);
                            borrow = 0;
                        }
                    }
                    else {
                        if (*itr.first-borrow < *itr.second) {
                            new_num.push_back(10+*itr.first-borrow - *itr.second);
                            borrow = 1;
                        }
                        else {
                            new_num.push_back(*itr.first-borrow - *itr.second);
                            borrow = 0;
                        }
                    }
                }
                bigint b_ret;
                int zero_ind = 0;
                for (std::vector<int>::reverse_iterator itr=new_num.rbegin(); itr!=new_num.rend(); ++itr) {
                    if (*itr == 0)
                        zero_ind++;
                    else
                        break;
                }
                if (zero_ind == new_num.size())
                    return b_ret;
                std::vector<int> new_num_zeroSplice(new_num.begin(), new_num.end()-zero_ind);
                b_ret.setNum(new_num_zeroSplice);
                b_ret.setSign(new_neg_sign);
                return b_ret;
            }
            else { //*this == b
                bigint b_zero;
                return b_zero;
            }
        }
    }
}

//+= Plus Equals
void bigint::operator += (bigint &b)
{
    *this = *this + b;
}

//-= Minus Equals
void bigint::operator -= (bigint &b)
{
    *this = *this - b;
}

//* Multiplication
bigint bigint::operator * (bigint &b)
{
    bigint out;
    int digit_num = 0;
    for (std::vector<int>::iterator it1=num.begin(); it1!=num.end(); ++it1) {
        int carry = 0;
        std::vector<int> partial(digit_num, 0);
        for (std::vector<int>::iterator it2=b.begin(); it2!=b.end(); ++it2) {
            int mult =  *it1 * *it2 + carry;
            if (mult > 9) {
                carry = std::to_string(mult).at(0) - '0';
                mult = mult % 10;
            }
            else
                carry = 0;
            partial.push_back(mult);
        }
        if (carry != 0)
            partial.push_back(carry);

        bigint b_tmp;
        b_tmp.setNum(partial);
        out += b_tmp;
        ++digit_num;
    }

    bigint b_ret;
    std::vector<int> new_num = out.getNum();

    int zero_ind = 0;
    for (std::vector<int>::reverse_iterator itr=new_num.rbegin(); itr!=new_num.rend(); ++itr) {
        if (*itr == 0)
            zero_ind++;
        else
            break;
    }
    if (zero_ind == new_num.size())
        return b_ret;

    std::vector<int> new_num_zeroSplice(new_num.begin(), new_num.end()-zero_ind);
    b_ret.setNum(new_num_zeroSplice);
    if ((neg_sign && b.getSign()) || (!neg_sign && !b.getSign()))
        b_ret.setSign(false);
    else
        b_ret.setSign(true);
    return b_ret;
}
