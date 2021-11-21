#include <iostream>
#include <string>
#include "Crockford32.hpp"
#include <bits/stdc++.h>

int main(void) {

  //std::cout << encode_symbols[24] << std::endl; 

 // std::cout << char_to_bin('B') << std::endl;

  /**
  std::string c = "001";

  augment_bits(&c);

  std::cout << c << std::endl;
  **/


  
  std::string c = "a";
  
  encode(c);
  


  /**
  std::string t = "Hey";
  std::string r = " World";
  std::string tr = t + r;
  std::cout << tr << std::endl;
  **/

 // encode("A");

  return 0;
}


// 7-bit ascii -> 8-bit binary 

std::string char_to_bin(char str) {
  std::string result = ""; 
  short val = short(str);
  
  while(val > 0) {       
    short step = val % 2;

    if(step) {
      result.push_back('1');
    } else { 
      result.push_back('0');
    }

    val /= 2;
  }

  result.push_back('0');
  reverse(result.begin(), result.end()); 
  return result;

}


std::string encode(std::string input) {

  short len = input.length();
  char c;
  std::string result = "";                    
  std::string bin;
  std::string char_result; 

  for(short j = 0; j < len; j++) {                // 'j < len' => ignore '\0' character at end of std::string
    c = input[j];
    bin = char_to_bin(c);
    augment_bits(&bin);
    
    std::cout << bin << std::endl;
 //   std::cout << bin.size() << std::endl;
    exit(0);
    
    char_result = encode_char(bin);
    result += char_result;
  }
  
  return result; 
  

  /** 
  
  - get char
  - to bin 
  - augment to multiple of 5 

  - get ascii version of binary

  - add characters to result

  **/

}


std::string encode_char(std::string bits) {
  std::string result = "";
  



  return result;
}

std::string decode(std::string input) {
  return input; // delete 
}


void augment_bits(std::string* input) {
  while((input->length() % 5) != 0) {
    input->push_back('0');
  }
}


std::string add_checksum(std::string input) {
  return input; // delete
}

bool validate_checksum(std::string input) {
 return false;
}
