#include <string>

#pragma once

std::string char_to_bin(char str);

std::string encode(std::string input);

std::string encode_char(std::string bits);

std::string decode(std::string input);

std::string decode_char(std::string input);

std::string add_checksum(std::string input);

void augment_bits(std::string* input);

bool validate_checksum(std::string input);

extern char encode_symbols[32];


char encode_symbols[32] = {

'0', '1', '2', '3', 

'4', '5', '6', '7',

'8', '9', 'A', 'B',

'C', 'D', 'E', 'F',

'G', 'H', 'J', 'K', 

'M', 'N', 'P', 'Q', 

'R', 'S', 'T', 'V', 

'W', 'X', 'Y', 'Z'

};
