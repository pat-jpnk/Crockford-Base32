#include <string>
#include <unordered_map>

#pragma once

std::string char_to_bin(char str);
std::string char_to_bin(short val);
std::string encode(std::string input, bool checksum = true);
std::string decode(std::string input, bool checksum = true);
char create_checksum(std::string input);
void augment_encode_bits(std::string* input);
void augment_decode_bits(std::string* input);
bool validate_checksum(std::string input, char checksum);

char create_checksum2(std::string input); // remove

// 0 - 31  => encoding 
// 32 - 36 => checksum

// TODO: separate last 5 in different or validation ?

enum segment_size {
  one_byte = 8,
  two_bytes = 16,
  four_bytes = 32,
  eight_bytes = 64

};

struct binary_segment {
  segment_size size;
  int largest_exponent;     // use short?
  int index;
};


inline char encode_symbols[37] = {

'0', '1', '2', '3', 

'4', '5', '6', '7',

'8', '9', 'A', 'B',

'C', 'D', 'E', 'F',

'G', 'H', 'J', 'K', 

'M', 'N', 'P', 'Q', 

'R', 'S', 'T', 'V', 

'W', 'X', 'Y', 'Z',

'*', '~', '$', '=',

'U'

};

inline std::unordered_map<char, short> decode_symbols = {
  {'0',0},  {'1',1},  {'2',2},  {'3',3},
  {'4',4},  {'5',5},  {'6',6},  {'7',7},
  {'8',8},  {'9',9},  {'A',10}, {'B',11},
  {'C',12}, {'D',13}, {'E',14}, {'F',15},
  {'G',16}, {'H',17}, {'J',18}, {'K',19},
  {'M',20}, {'N',21}, {'P',22}, {'Q',23},
  {'R',24}, {'S',25}, {'T',26}, {'V',27},
  {'W',28}, {'X',29}, {'Y',30}, {'Z',31},
};
