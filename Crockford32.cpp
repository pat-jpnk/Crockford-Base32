#include <iostream>
#include <string>
#include "Crockford32.h"
#include <bits/stdc++.h>


int main() {
  
  short d = decode_values['C'];

  std::cout << d << std::endl;

  /**

  //std::cout << encode_symbols[24] << std::endl; 

 // std::cout << char_to_bin('B') << std::endl;

  std::string c = "001";

  augment_bits(&c);

  std::cout << c << std::endl;


  std::string a = "Patrick";
  std::string c = "aB";
  
  encode(c);


  std::string t = "Hey";
  std::string r = " World";
  std::string tr = t + r;
  std::cout << tr << std::endl;

 // encode("A");
  
  std::string res = encode(a);
  std::cout << res << std::endl;
  return 0;
  **/
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

  std::string result = "";
  std::string bin = "";
  std::string bin_cache = "";

  for(short j = 0; j < len; j++) {
    c = input[j];
    bin_cache = char_to_bin(c);
    bin += bin_cache;
  }

  augment_encode_bits(&bin);
  bits_len = bin.length();
  
  while(bits_start < bits_len) {
    std::string substr_cache = bin.substr(bits_start, 5);
    const char* sub = &substr_cache[0];    
    result += encode_symbols[strtoull(sub, NULL, 2)];
    bits_start += 5;
  }

  return result;
}


std::string decode(std::string input) {
  short len = input.length();
  char c;
  std::string bin = "";

  for(short k = 0; k < len; k++) {
    c = input[k];
    //bin += encode();
  }

  return "";

}



void augment_encode_bits(std::string* input) {
  while((input->length() % 5) != 0) {
    input->push_back('0');
  }
}

void augment_decode_bits(std::string* input) {
  while((input->length() % 5) != 0) {
    input->insert(0,"0");
  }
};

std::string create_checksum(std::string input) {
  return input; // delete and implement
}

bool validate_checksum(std::string input) {
 return false;
}
