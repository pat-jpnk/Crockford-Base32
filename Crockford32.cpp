#include <iostream>
#include <string>
#include "Crockford32.h"
#include <bits/stdc++.h>

#include <stdexcept>
#include <limits>
#include <vector>
#include <cmath>

#include <float.h>

// DBL_MAX         = 1.79769e+308
// DBL_MAX         = 179769000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

// 64 unsigned max = 18446744073709551615

// SAFE ?


/*
char: 0 num: 48
char: 1 num: 49
char: 2 num: 50
char: 3 num: 51
char: 4 num: 52
char: 5 num: 53
char: 6 num: 54
char: 7 num: 55
char: 8 num: 56
char: 9 num: 57

char: A num: 65
char: B num: 66
char: C num: 67
char: D num: 68
char: E num: 69
char: F num: 70
char: G num: 71
char: H num: 72

char: J num: 74
char: K num: 75

char: M num: 77
char: N num: 78

char: P num: 80
char: Q num: 81
char: R num: 82
char: S num: 83
char: T num: 84

char: V num: 86
char: W num: 87
char: X num: 88
char: Y num: 89
char: Z num: 90

char: * num: 42
char: ~ num: 126
char: $ num: 36
char: = num: 61
char: U num: 85

*/


// TODO: Enforce correct input characters to prevent errors

// valid for encode: all ?

/* all valid:
1234567890!@#$%^&*()_;'/./?,mzxcvbnmasdfghjkl;qwertyuiopÜл_=
*/

// valid for decoding: encode_symbols


// TODO: should checksum be recognized automatically?


//throw std::invalid_argument("Invalid checksum.");

int main() {

 // std::cout << DBL_MAX << std::endl;

  //std::cout << ( ( (20 % 37) + (30 % 37)) % 37  ) << std::endl;

  // (a + b) mod x = ( (a mod x) + (b mod x) ) mod x


 // 9HMPARK59N6Q6S3KC5J62S0
    // std::string res2 = encode(rr, true); // 85TQ8VSME8H                   // works with 'false' => 9HMPARK59N6Q6S3KC5J62S0
                                                                        // true => 9HMPARK59N6Q6S3KC5J62S0= (works not)

  //std::string rr = "LiebeMMsdsadad";
  //std::string rr = "Auto4randwkjandndawjdknadwMMMMM";
  std::string rr = "Auto4randwkjandndawjdknadwMMMMMNNSddadodnjAJADNALDWNALDNALDNADLANDADNLADNAJDKadadamcac";

  std::string rr2 = "Liebe*";
  
  std::string rr3 = "9HMPARK59N6Q6S3KC5J62S0=";

  std::string rr4 = "9HMPARK";
  

        //std::string res = encode(rr, true);  
                                                                       
        //std::cout << res << std::endl;


  std::string tt = decode(rr2, true);
  std::cout << tt << std::endl;
  
   //std::string tt2 = decode(res2, true);
   //std::cout << tt2 << std::endl;


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

bool validate_decode_input(std::string input, bool checksum) {

  int input_len;

  if (checksum == true) {
    input_len = input.length() - 1;
  } else {
    input_len = input.length();
  }

  for (int i = 0; i < input_len; i++) {
    int c = ((int)input.at(i));
    std::cout << "c: " << input.at(i) << std::endl;

    std::cout << "i: " << i << std::endl;
    if ((c < 48) || (c > 57 && c < 65) || (c > 72 && c < 74) || (c > 75 && c < 77) || (c > 78 && c < 80) || (c > 84 && c < 86) || (c > 90)) {
      return false;
    }
  }

  if (checksum == true) {
    int j = ((int)input.at(input_len));
    std::cout << input_len << std::endl;
    if ( (j < 36) || (j > 36 && j < 42) || (j > 42 && j < 48) || (j > 57 && j < 61) || (j > 61 && j < 65) || (j > 65 && j < 72) || (j > 72 && j < 74) || (j > 75 && j < 77) || (j > 78 && j < 80) || (j > 90 && j < 126) && (j > 126)) {
      return false;
    }
  }

  return true;

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
  
  if(checksum) {
    check_sum = create_checksum(input);
    result.append(1,check_sum);
  }

  return result;
}


std::string decode(std::string input, bool checksum) {   


  if (!validate_decode_input(input, checksum)){
    throw std::invalid_argument("Invalid input character for decoding.");
  }


  exit(0);    // TODO: remove

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
  
  if(checksum) { 
    if(validate_checksum(result,check_sum)) {
      return result;
    } else {
      return NULL;
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

  // divide into (64, 32, 16, 8) increments

  while(covered < binary_len) {

    binary_segment seg;

    if (remaining >= eight_bytes) {
      seg.size = eight_bytes;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;

    } else if (remaining >=  four_bytes) {
      seg.size = four_bytes;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;

    } else if (remaining >= two_bytes) {
      seg.size = two_bytes;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;

    } else {
      seg.size = one_byte;
      seg.index = covered;
      seg.largest_exponent = binary_len - covered - 1;
    }

    covered += seg.size;
    segments.push_back(seg);
    remaining = binary_len - covered;
  }

  // calculate values 

  for (auto& s : segments) {

    long double val = 0;
    double exp = (double) s.largest_exponent;
    int index = s.index;

  for(int j = s.size; j > 0; j--) {
      char c = input_bin.at(index);
      int i = c - '0';            // https://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int
      if (i == 1){
        val += (std::pow(2, exp));
      }

      index++;
      exp--;

    }

    values.push_back(val);

  }

  // create mod sum

  long double result = 0;

  for (auto& v : values) {
    result += std::fmod(v,37.0);  
  }

  result = std::fmod(result, 37.0);
  int k = static_cast<int>(result);

  // get checksum character  
  
  return encode_symbols[k];
  
}


bool validate_checksum(std::string input, char checksum) {
  if(create_checksum(input) == checksum) {
    return true;
  } else {
    return false;
  }
}
