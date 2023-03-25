#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <math.h>
#include <string>

int gcd(int numerator, int denominator) {
const int num = numerator;
const int denom = denominator;
int shift;
for (shift = 0; ((numerator | denominator) & 1) == 0; ++shift) {
numerator >>= 1;
denominator >>= 1;
}
while ((numerator & 1) == 0) {
numerator >>= 1;
}
while (denominator != 0) {
while ((denominator & 1) == 0) {
denominator >>= 1;
}
if (numerator > denominator) {
std::swap(numerator, denominator);
}
denominator -= numerator;
}
return numerator << shift;
}



Rational::Rational(){
numerator_= 0;
denominator_ = 1;
};

Rational::Rational(int numerator, int denominator){
if(denominator == 0)  throw std::invalid_argument{"Nazivnik ne smije biti nula!"};
numerator_ = numerator;
denominator_= denominator;
};

Rational::Rational(const char& rational){
  std::stringstream str_int;
  str_int << rational;
  str_int >> numerator_;
  denominator_ = 1;
}

Rational::Rational(const std::string& rational){
  std::stringstream separate;
  char ignore_;
  separate << rational;
  separate >> numerator_;
  separate >> ignore_;
  if(ignore_ != '/')  throw std::invalid_argument{"Delimiter nevalidan!"};
  separate >> denominator_;
}

Rational::Rational(const Rational& rational): numerator_{rational.numerator_}, denominator_{rational.denominator_} {
};

Rational::Rational(Rational&& rational) : numerator_{rational.numerator_}, denominator_{rational.denominator_} {
rational.numerator_ = 0;
rational.denominator_=1;
};

Rational& Rational::operator=(const Rational& rational){
numerator_=rational.numerator_;
denominator_= rational.denominator_;
return *this;
};

Rational& Rational::operator=(Rational&& rational){
numerator_=rational.numerator_;
denominator_= rational.denominator_;
rational.numerator_=0;
rational.denominator_=1;
return *this;
};

Rational Rational::operator+(const Rational& rational) const {
int nom,denom;
denom= rational.denominator_*denominator_;
nom = (denom/denominator_)*numerator_ + (denom/rational.denominator_)*rational.numerator_;
int normalize;
normalize= gcd(nom,denom);
nom/=normalize;
denom/=normalize;
return Rational{nom,denom};
};

Rational Rational::operator-(const Rational& rational) const {
int nom,denom;
denom= rational.denominator_*denominator_;
nom = (denom/denominator_)*numerator_ - (denom/rational.denominator_)*rational.numerator_;
int normalize;
normalize= gcd(nom,denom);
nom/=normalize;
denom/=normalize;
return Rational{nom,denom};
};

Rational Rational::operator+(int numerator) const{
int num;
num = numerator*denominator_ + numerator_;
return Rational{num,denominator_};
}

Rational Rational::operator-(int numerator) const{
int num;
num = numerator_ - numerator*denominator_ ;
return Rational{num,denominator_};
}

Rational Rational::operator*(const Rational& rational) const{
int num,denom;
num = numerator_*rational.numerator_;
denom = denominator_ * rational.denominator_;
int normalize;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
return Rational{num,denom};
};

Rational Rational::operator*(int numerator) const{
int num,denom;
denom= denominator_;
num = numerator_*numerator;
int normalize;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
return Rational{num,denom};
};

Rational Rational::operator/(const Rational& rational) const{
int num,denom;
num = numerator_*rational.denominator_;
denom = denominator_ * rational.numerator_;
int normalize;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
return Rational{num,denom};
};

Rational Rational::operator/(int numerator) const{
int num,denom;
num = numerator_;
denom = denominator_ * numerator;
int normalize;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
return Rational{num,denom};
};

Rational Rational::operator^(int pwr) const{
int num,denom;
num = pow(numerator_,pwr);
denom = pow(denominator_,pwr);
int normalize;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
return Rational{num,denom};
};

Rational& Rational::operator++(){
numerator_+= denominator_;
return *this;
};

Rational Rational::operator++(int){
numerator_+= denominator_;
return Rational{numerator_,denominator_};
};

Rational& Rational::operator--(){
numerator_-= denominator_;
return *this;
};

Rational Rational::operator--(int){
numerator_-= denominator_;
return Rational{numerator_,denominator_};
};

bool Rational::operator==(const Rational& rational) const{
int normalize,num,denom;
num=rational.numerator_;
denom= rational.denominator_;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
if( numerator_ == rational.numerator_ && denominator_ == rational.denominator_){
return true;
}else if(numerator_ == num && denominator_ == denom){
return true;
}else return false;
};

bool Rational::operator==(const char& rational) const{
if (denominator_ == 1 && numerator_ == rational){
  return true;
}else return false;
};

bool Rational::operator!=(const Rational& rational) const{
int normalize,num,denom;
num=rational.numerator_;
denom= rational.denominator_;
normalize= gcd(num,denom);
num/=normalize;
denom/=normalize;
if( numerator_ != rational.numerator_ || denominator_ != rational.denominator_){
return true;
}else if(numerator_ != num || denominator_ != denom){
return true;
}else return false;
};

bool Rational::operator!=(const char& rational) const{
if (denominator_ != 1 || numerator_ != rational){
  return true;
}else return false;
};

const int Rational::numerator() const{
return numerator_;
};

const int Rational::denominator() const{
return denominator_;
};

Rational::~Rational(){
};

std::ostream& operator<<(std::ostream& os, const Rational& rational){
int normalize,num,denom;
num = rational.numerator();
denom = rational.denominator();
normalize= gcd(num,denom);
if (num == 0 && denom == 1){
os << num;
return os;
}else{
num/=normalize;
denom/=normalize;
}
if (denom == 1){
os << num;
return os;
}else {
os << num << '/' << denom << std::endl;
return os;
};
};

std::istream& operator>>(std::istream& input, Rational& rational){
char ignore_;
int num,denom;
input >> num;
input >> ignore_;
if(ignore_ != '/'){
  if(ignore_ == '\n'){
  denom = 1;
  rational = Rational(num,denom);
  return input;
  }else throw std::invalid_argument{"Nepravilna konstrukcija!"};
};
input >> denom;
rational = Rational(num,denom);
return input;
};
