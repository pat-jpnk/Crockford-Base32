### Crockford's Base32 encoding

some nice resources:

http://www.crockford.com/base32.html<br/> 
https://www.youtube.com/watch?v=aUdKd0IFl34<br/> 
https://www.asciitable.com/<br/>


Trying to implement a character encoding, read about this one in the book ""

At first I made the mistake of trying to encode character by character,
then I realized 

"a" -> "C4"  
"B" -> "88" 

but "aB" is not "C488", but rather 

"aB" -> "C510" 

so I knew that was wrong, too bad

I also realized that you have to add more than one '0' to some
binary representations to get an 8-bit value to work with when the encoding
of '0' was wrong.

# requirements 

- all letters in the encoding output must be capitalized, therefore
  only letters that are capitalized are valid input to the decoding 
  method

- checksum adding is automatically added
