### Crockford's Base32 encoding

some nice resources:

http://www.crockford.com/base32.html<br/> 
https://www.youtube.com/watch?v=aUdKd0IFl34<br/> 
https://www.asciitable.com/<br/>


Trying to implement a character encoding, read about this one in the book 
"API Design Patterns" - chpt. 6 "Resourse identification", p. 92

# notes

- this implementation could include more validation
- this implementation relies on string manipulation,
  could probably be done more efficiently

# requirements 

- all letters in the encoding output must be capitalized, therefore
  only letters that are capitalized are valid input to the decoding 
  method

- checksum is automatically added and checked
