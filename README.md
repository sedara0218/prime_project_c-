# prime_project_cpp

## Steps to run with my version of bigint:
#### 1. Download all files to a local directory
#### 2. Open terminal and go to the directory where the files are located
#### 3. Type: 
  * Ubuntu or Mac: ./main 5
  * Windows: main 5

*Note: you can replace the 5 with another number, this is the iterations you want to run the program. The lower the number the less primes you will find, the higher the number the higher amount of primes you will find.

#### Compile with:
* Ubuntu or Windows: g++ main.cpp bigint.cpp -o main -std=c++11
* Mac: clang++ main.cpp bigint.cpp -o main -std=c++11

## Steps to run with InfInt (http://sercantutar.github.io/infint/):
#### Pre: Download InfInt and place the InfInt.h file in the InfInt folder
#### 1. Download all files to a local directory
#### 2. Open the terminal inside the InfInt folder
#### 3. Type: 
  * Ubuntu or Mac: ./main 5
  * Windows: main 5

*Note: you can replace the 5 with another number, this is the iterations you want to run the program. The lower the number the less primes you will find, the higher the number the higher amount of primes you will find.

#### Compile with:
* Ubuntu or Windows: g++ main.cpp -o main
* Mac: clang++ main.cpp -o main

## Steps to run with Arbitrary-precision arithmetic (https://sites.google.com/site/indy256/algo_cpp/bigint):
#### Pre: Download Arbitrary-precision arithmetic and place the struct inside the main.cpp file.  You will also need to add these functions inside the struct:
```
    int get_last_digit() {
        std::string s = std::to_string(a.at(0));
        return s.at(s.length()-1) - '0';
    }
    bool is_even() {
        return this -> get_last_digit() % 2 == 0;
    }
    std::string to_string() {
        std::string s = "";
        if (!sign)
            s += "-";
        for (std::vector<int>::reverse_iterator it=a.rbegin(); it!=a.rend(); ++it) {
            
            s += std::to_string(*it);
        }
        return s;
    }
```
#### 1. Download all files to a local directory
#### 2. Open the terminal inside the Arbitrary-precision folder
#### 3. Type: 
  * Ubuntu or Mac: ./main 5
  * Windows: main 5

*Note: you can replace the 5 with another number, this is the iterations you want to run the program. The lower the number the less primes you will find, the higher the number the higher amount of primes you will find.

#### Compile with:
* Ubuntu or Windows: g++ main.cpp -o main
* Mac: clang++ main.cpp -o main
