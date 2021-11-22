#include <iostream>
#include <string>
#include "Crockford32.h"
#include <bits/stdc++.h>


//int main() {

//  std::string rr = "a";
  
//  char c = 'Q';
  /**
  char d = create_checksum(rr);

  std::cout << d << std::endl;
  **/

  //bool res = validate_checksum(rr,c);  // "a", 'Q'
  //std::cout << res << std::endl;  
  
  /**
  
  std::string re = "C4Q";
  
  std::string d = decode(re);
  std::cout << d << std::endl;
  
  return 0; **/
//}


// 7-bit ascii -> 8-bit binary 
std::string char_to_bin(char str) {
  
  std::string result = ""; 
  short val = short(str);
  short step;
  
  while(val > 0) {       
    step = val % 2;

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

// return 5-bit binary
std::string char_to_bin(short val) {
  std::string result = "";
  while(val > 0) {
    short step = val % 2;

    if(step) {
      result.push_back('1');
    } else {
      result.push_back('0');
    }

    val /= 2;
  }

  reverse(result.begin(),result.end());
  return result;
}

std::string encode(std::string input, bool checksum) {

  char check_sum;
  short len = input.length();
  char c;
  short bits_len;
  short bits_start = 0;

  std::string result = "";
  std::string bin = "";
  std::string bin_cache = "";
  
  if(checksum) {
    check_sum = create_checksum(input);  
  }

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
  
  if(checksum) {
    result.append(1,check_sum);
  }

  return result;
}


std::string decode(std::string input) {

  char check_sum = input[input.length() - 1];
  input.pop_back();
  
  //std::cout << check_sum << std::endl;

  //exit(0);

  short len = input.length();
  char c;
  short decode_val;
  std::string result = "";
  std::string bin_cache = "";
  std::string bin = "";
  std::string substr_cache = "";

  for(short k = 0; k < len; k++) {
    c = input[k];
    
    if(c != '0') {
      decode_val = decode_symbols[c];
      bin_cache = char_to_bin(decode_val); // return 5 bit binary     
      augment_decode_bits(&bin_cache);
      bin += bin_cache;
    } else {
      bin_cache = "00000";
      bin += bin_cache;
    }    
  }
  
  short bin_len = bin.length(); 
  short bin_start = 0;
  short ds;
  short remain;
  char ret;
  
  while(bin_start < bin_len) {
    
    if((bin_len - bin_start) >= 8) {
      substr_cache = bin.substr(bin_start, 8);
      ds = std::stoul(substr_cache, NULL, 2);
      result.append(1, (char) ds);
      bin_start += 8;

    } else {
      remain = (bin_len - bin_start);
      substr_cache = bin.substr(bin_start, remain);
      ds = std::stoul(substr_cache, NULL, 2);

      if(ds == 0) {
        break;
      }

      ret = (char) ds;
      result.append(1, (char) ds);
      bin_start += remain; 
    }
  }
 
  
 //std::cout << result << std::endl;
 //std::cout << check_sum << std::endl;
 //exit(0);
 // return result;
 
  if(validate_checksum(result,check_sum)) {
    return result;
  } else {
    result = "";
    return result;
  }

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

char create_checksum(std::string input) {
  std::string input_bin = "";
  short len = input.length();
  for(short i = 0; i < len; i++) {
    input_bin += char_to_bin(input[i]);
  }
  return encode_symbols[(std::stoul(input_bin, NULL, 2) % 37)];
}

bool validate_checksum(std::string input, char checksum) {
  if(create_checksum(input) == checksum) {
    return true;
  } else {
    return false;
  }
}
