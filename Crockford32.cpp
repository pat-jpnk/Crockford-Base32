#include <iostream>
#include <string>
#include "Crockford32.h"
#include <bits/stdc++.h>

#include <stdexcept>
#include <limits>
#include <vector>
#include <cmath>

// TODO: Enforce correct input characters to prevent errors

// valid for encode: all ?

/* all valid:
1234567890!@#$%^&*()_;'/./?,mzxcvbnmasdfghjkl;qwertyuiopÜл_=
*/

// valid for decoding: encode_symbols


// TODO: should checksum be recognized automatically?

int main() {


  //std::string d = "0100110001101001011001010110001001100101010010110100101101001011";
   
  //std::cout << std::stoul(d, NULL, 2) % 37 << std::endl;

  //std::cout << std::numeric_limits<unsigned long>::max() << std::endl;

  //std::cout << std::numeric_limits<unsigned int>::max() << std::endl;

  //exit(1);
  
  std::string fif = "110010";

  //std::cout << std::stoul(fif, NULL, 2) % 37 << std::endl; 

  //std::cout << encode_symbols[13] << std::endl;

      //  std::cout << create_checksum("tree") << std::endl;  // G

      // std::cout << create_checksum2("tree") << std::endl;  // G




  //std::cout << ( ( (20 % 37) + (30 % 37)) % 37  ) << std::endl;

  // (a + b) mod x = ( (a mod x) + (b mod x) ) mod x

  /*
  new checksum algo:


  - count binary digits 

  - divide into (64, 32, 16, 8) increments

  - calculate values 
  
  - create mod sum

  - get checksum character  
  
  
  
  */

//9HMPARK59N6Q6S3KC5J62S0 =

//9HMPARK59N6Q6S3KC5J62S0 E

  std::string rr = "LiebeMMsdsadad";
      //std::string rr = "Auto4r";
  
  std::string res = encode(rr, true);  
                                                                        // 9HMPARK59N6Q6S3KC5J62S0
    // std::string res2 = encode(rr, true); // 85TQ8VSME8H                   // works with 'false' => 9HMPARK59N6Q6S3KC5J62S0
                                                                        // true => 9HMPARK59N6Q6S3KC5J62S0= (works not)
  std::cout << res << std::endl;

      //std::cout << res2 << std::endl;

  //std::string m = "9HMPARK59N6Q6S3KC5J62S0=";

  //std::string tt = decode(m, true);



  //std::string tt = decode(res, false);
  //std::cout << tt << std::endl;
  
   //std::string tt2 = decode(res2, true);
   //std::cout << tt2 << std::endl;
  

  // 0100110001101001011001010110001001100101010011010100110101110011011001000111001101100001011001000110000101100100

 // std::string tt3 = "LiebeMMsdsadad";
 // std::cout << create_checksum(tt3) << std::endl;
  




  /*
  try {
    std::string tt2 = decode("EHS7AS8", true); //Libef4
    std::cout << "res:" << tt2 << std::endl;
  }
  catch (const std::invalid_argument & ex) {
        std::cout << "exception entered" << std::endl;
        std::cerr << "ex: " << ex.what() << '\n';
  }
  */
  

  return 0;
}


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

  std::cout << "res: " << result << std::endl;

  
  if(checksum) {
    std::cout << "HEYYYY 1" << std::endl;
    check_sum = create_checksum(input);
    result.append(1,check_sum);
  }

  return result;
}


std::string decode(std::string input, bool checksum) {   
  char check_sum;

  if(checksum) {
    check_sum = input[input.length() - 1];
    input.pop_back();
  }
  
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
      bin_cache = char_to_bin(decode_val); // return 5-bit binary  
      augment_decode_bits(&bin_cache);
      bin += bin_cache;
    } else {
      bin_cache = "00000";
      bin += bin_cache;
    }    
  }
  

  short bin_len = bin.length(); 
  short bin_start = 0;
  unsigned long ds;
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
  
  // IMPROVE SOLUTION FOR CHECKSUM
  if(checksum) { 
    if(validate_checksum(result,check_sum)) {
      return result;
    } else {
      std::cout << "ELSE" << std::endl;
      return NULL;

      //throw std::invalid_argument("Invalid checksum.");
    }
  }

  return result;
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

// error for wrong symbol
char create_checksum2(std::string input) {
  //std::cout << "input: " << input << std::endl;

  std::string input_bin = "";
  short len = input.length();
  for(short i = 0; i < len; i++) {
    input_bin += char_to_bin(input[i]);
  }

  std::cout << "bin: " << input_bin << std::endl;

  // -- ok -- 

  //std::cout << "in: " << std::stoul(input_bin, NULL, 2) << std::endl;   // stoul

  std::cout << "res chk 1: " << std::stoul(input_bin, NULL, 2) % 37 << std::endl;


  return encode_symbols[(std::stoul(input_bin, NULL, 2) % 37)];
  
}


char create_checksum(std::string input) {

  std::vector<binary_segment> segments;
  std::vector<long double> values;
  int covered = 0;
  

  // count binary digits 

  std::string input_bin = "";
  short len = input.length();
  for(short i = 0; i < len; i++) {
    input_bin += char_to_bin(input[i]);
  }

  int binary_len = input_bin.length();
  int remaining = binary_len;

  std::cout << "bin: " << input_bin << std::endl;

  std::cout << "bin: " << binary_len << std::endl;

  //int len = input.length();

  // divide into (64, 32, 16, 8) increments

  std::cout << " " << std::endl;


  while(covered < binary_len) {

    binary_segment seg;

    if (remaining >= eight_bytes) {
      seg.size = eight_bytes;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;


      std::cout << "--CALC-- 64" << std::endl;
      std::cout << "covered: " << covered << std::endl;
      std::cout << "largest expo: " << seg.largest_exponent<< std::endl;
      std::cout << "index: " << seg.index<< std::endl;
      std::cout << " " << std::endl;

    } else if (remaining >=  four_bytes) {
      seg.size = four_bytes;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;

      std::cout << "--CALC-- 32" << std::endl;
      std::cout << "covered: " << covered << std::endl;
      std::cout << "largest expo: " << seg.largest_exponent<< std::endl;
      std::cout << "index: " << seg.index<< std::endl;
      std::cout << " " << std::endl;

    } else if (remaining >= two_bytes) {
      seg.size = two_bytes;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;

      std::cout << "--CALC-- 16" << std::endl;
      std::cout << "covered: " << covered << std::endl;
      std::cout << "largest expo: " << seg.largest_exponent<< std::endl;
      std::cout << "index: " << seg.index<< std::endl;
      std::cout << " " << std::endl;

    } else {
      seg.size = one_byte;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;
    }

    covered += seg.size;
    segments.push_back(seg);
    remaining = binary_len - covered;
    std::cout << "rem: : " << remaining << std::endl;

  }

//  std::cout << input_bin << std::endl;

  // calculate values 

//  long double bigval = 0;

  for (auto& s : segments) {

    long double val = 0;
    double exp = (double) s.largest_exponent;
    int index = s.index;

/*
    std::cout << " " << std::endl;
    std::cout << "size: " << s.size << std::endl;
    std::cout << "exp: " << exp << std::endl;
    std::cout << "index: " << index << std::endl;

    std::cout << " " << std::endl;
*/


    for(int j = s.size; j > 0; j--) {
      char c = input_bin.at(index);
      int i = c - '0';            // https://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int
      if (i == 1){
        val += (std::pow(2, exp));
      }

/*
      std::cout << "exp: " << exp << std::endl;
      std::cout << "index: " << index << std::endl;
      std::cout << std::fixed << "val: " << val << std::endl;
      
*/

      index++;
      exp--;

 
      //std::cout << "exp: " << exp << std::endl;
      //std::cout << "val: " << val << std::endl;
    }

    std::cout << "size, val : " << s.size << "; " << val <<std::endl;

    values.push_back(val);


  //  bigval += val;
  }



  std::cout<<std::fixed<<"VAL: "<< values.at(0) << std::endl; 

 // std::cout<<std::fixed<<"val size: "<< values.size() << std::endl;


  //exit(0);

  // create mod sum

  //unsigned long result = 0;

  long double result = 0;

  for (auto& v : values) {
    //int k = static_cast<int>(v);
    //std::cout << "k: " << k << std::endl;
    //result += (k % 37);
    
    std::cout << "mod res: " << std::fmod(v,37.0) << " v: " << v<<std::endl;

    result += std::fmod(v,37.0);
  
  }

  //result %= 37;

  std::cout << "mod res ibetween: " << result << std::endl;

  result = std::fmod(result, 37.0);

  std::cout << "res: " << result << std::endl;


  int k = static_cast<int>(result);

  //exit(0);

  // get checksum character  
  
  return encode_symbols[k];
  
//return 'd';
}


bool validate_checksum(std::string input, char checksum) {
  if(create_checksum(input) == checksum) {
    return true;
  } else {
    return false;
  }
}
