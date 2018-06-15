#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <sstream>
#include <utility> //std::pair
#include <iterator>
#include <algorithm>
#include <vector>

namespace std {
	template <typename T>
	string to_string(const T& value) {
		return string(value);
	}
}

class bigint
{
	private:
		std::vector<int> num;
		bool neg_sign;
		void parseToNum(std::string);

	public:
		~bigint();

		bigint();
		template <class T>
		bigint(T n) {
			std::string s = std::to_string(n);
			neg_sign = false;
		    if (s.at(0) == '-') {
		        s = s.substr(1);
		        neg_sign = true;
		    }
		    parseToNum(s);
		}

		template <class T>
		inline void tmpFunc(T a) {
			T tmp = a+1;
			std::cout << tmp << std::endl;
		}

		std::string to_string();
		int size() const;
		std::vector<int>::iterator begin();
		std::vector<int>::iterator end();
		std::vector<int>::reverse_iterator rbegin();
		std::vector<int>::reverse_iterator rend();
		std::vector<int>::const_reverse_iterator crbegin() const;
		std::vector<int>::const_reverse_iterator crend() const;
		std::vector<int> getNum();
		bool getSign() const;
		void setSign(bool);
		void setNum(std::vector<int>);

		bool is_even();
		int get_last_digit();
		bigint abs();
		bigint negate(); //-1 * *this

		template <class T>
		void operator = (T i)
		{
			bigint b_tmp(i);
			*this = b_tmp;
		}
		template <class T>
		bool operator == (T i)
		{
			bigint b_tmp(i);
		    return *this == b_tmp;
		}
		template <class T>
		bool operator != (T i)
		{
			bigint b_tmp(i);
		    return *this != b_tmp;
		}
		template <class T>
		bool operator < (T i)
		{
			bigint b_tmp(i);
		    return *this < b_tmp;
		}
		template <class T>
		bool operator > (T i)
		{
			bigint b_tmp(i);
		    return *this > b_tmp;
		}
		template <class T>
		bool operator <= (T i)
		{
			bigint b_tmp(i);
		    return *this <= b_tmp;
		}
		template <class T>
		bool operator >= (T i)
		{
			bigint b_tmp(i);
		    return *this >= b_tmp;
		}
		template <class T>
		bigint operator + (T i)
		{
			bigint b_tmp(i);
		    return *this + b_tmp;
		}
		template <class T>
		bigint operator - (T i)
		{
			bigint b_tmp(i);
		    return *this - b_tmp;
		}
		template <class T>
		void operator += (T i)
		{
			bigint b_tmp(i);
			*this = *this + b_tmp;
		}
		template <class T>
		void operator -= (T i)
		{
			bigint b_tmp(i);
			*this = *this - b_tmp;
		}
		template <class T>
		bigint operator % (T i)
		{
			bigint b_tmp(i);
			return *this % b_tmp;
		}
		template <class T>
		bigint operator * (T i)
		{
			bigint b_tmp(i);
			return *this * b_tmp;
		}

		void operator = (bigint &b);
		bool operator == (bigint &b);
		bool operator != (bigint &b);
		bool operator < (const bigint &b) const;
		bool operator < (bigint &b);
		bool operator > (bigint &b);
		bool operator <= (bigint &b);
		bool operator >= (bigint &b);
		bigint operator + (bigint &b);
		bigint operator - (bigint &b);
		void operator += (bigint &b);
		void operator -= (bigint &b);
		bigint operator * (bigint &b);

		void operator ++ ();
		void operator -- ();


		//EXTENSION FUNCTIONS TO ADD
		bigint operator / (bigint &b);
		bigint operator % (bigint &b);
		bigint pow(int exponent);
		int hashCode();
		double to_double();
		float to_float();
		long long to_longlong();
		long to_long();
		int to_int();
};
#endif
