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


  std::string a = "0";
  std::string c = "aB";
  /**
  encode(c);
  **/


  /**
  std::string t = "Hey";
  std::string r = " World";
  std::string tr = t + r;
  std::cout << tr << std::endl;
  **/

 // encode("A");
  
  std::string res = encode(c);
  std::cout << res << std::endl;
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
  
  while(result.length() < 8) {
    result.push_back('0');
  }
  reverse(result.begin(), result.end()); 
  return result;

}


std::string encode(std::string input) {
  short len = input.length();
  char c;
  short bits_len;
  short bits_start = 0;
  //short bits_end = 5;

  std::string result = "";
  std::string bin = "";
  std::string bin_cache = "";
  

  for(short j = 0; j < len; j++) {
    c = input[j];
    bin_cache = char_to_bin(c);
    bin += bin_cache;
  }

  augment_bits(&bin);
  bits_len = bin.length();
  
  std::cout << bin << std::endl;
  std::cout << bits_len << std::endl;
  
  //exit(0);
  
  while(bits_start < bits_len) {
    //std::cout << bits_start << " : " << bits_end << std::endl;

    std::string substr_cache = bin.substr(bits_start, 5);
    const char* sub = &substr_cache[0];
    
    std::cout << "this: " << substr_cache << std::endl;

    result += encode_symbols[strtoull(sub, NULL, 2)];

    //std::cout << rs << std::endl;
    
    //exit(0);
    bits_start += 5;
    //bits_end += 5;
    /**    
    std::string tre = bin.substr(15,20);
    std::cout << tre << std::endl;
    exit(0);
    **/
  }

  return result;
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
