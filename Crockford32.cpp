#include <iostream>
#include <string>
#include "Crockford32.h"
#include <bits/stdc++.h>

int main() {

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
    
 //   std::cout << bin << std::endl;              -> 10 bit binary
 //   std::cout << bin.size() << std::endl;
    
    char_result = encode_char(bin);
    result += char_result;
  }
  
  std::cout << result << std::endl;

  exit(0);

  return result; 
  

  /** 
  
  - get char
  - to bin 
  - augment to multiple of 5 

  - get ascii version of binary

  - add characters to result

  **/

}

// takes 10 bit binary chunk as input

/** 

-> convert 5-bit chunks from binary to decimal 
-> look up encode values & add to result 

**/

std::string encode_char(std::string bits) {
  std::string result = "";
 
  std::string p_1 = bits.substr(0,5);
  std::string p_2 = bits.substr(5,10);
  

  const char* n1 = &p_1[0];
  const char* n2 = &p_2[0];

  unsigned long long int dec1 = strtoull(n1, NULL, 2);
  unsigned long long int dec2 = strtoull(n2, NULL, 2);

  /**
  std::cout << bits << std::endl;
  std::cout << dec1 << std::endl;
  std::cout << dec2 << std::endl;
  **/

  //std::cout << bits << std::endl;
  //std::cout << p_1 << std::endl;
  //std::cout << p_2 << std::endl;
  
  result += encode_symbols[dec1];
  result += encode_symbols[dec2];

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
