#include "Rational.hpp"
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>

int main() {

std::fstream in{"./input.txt"};
Rational rational;

if(!in){
  std::cout<<"Error while loading file" << std::endl;
}

while ( in >> rational ){
  std::cout << rational << std::endl;
};

in.close();

};

