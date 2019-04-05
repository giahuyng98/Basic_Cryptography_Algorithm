# Basic_Cryptography_Algorithm


Implement some basic historical cipher algorithm such as

    *  Caesar cipher
    *  Monoalpha betic
    *  Playfair
    *  Hill cipher
    *  Vigenere 
    *  One time pad
    
Both encryption and decryption


*  How to compile
    ```g++ -std=c++14 main.cpp -O2 -o cipher```

*  How to use
    ```
     Usage: ./cipher [Options]...
     Options:
     -h:              show this help.
     -a <algorithm>:  en/de code algorithm.
         c:           caesar.
         m:           monoalphabetic.
         p:           playfair.
         h:           hill cipher.
         v:           vigenere.
         o:           one time pad.
     -e <text>:       encode <text>.
     -d <text>:       decode <text>.
     -k <key>:        key be used to en/de code algorithm.
     
     Example: encrypt string "ptithcm" with key 5 using caesar algorithm
              ./cipher -a c -e ptithcm -k 5
     
     Notes: 
     <text> contain ALPHABET CHARACTER ONLY.
     <key> should depend on cipher algorithm, follow below:
       -a c: <key>=int.
       -a m: <key>=26 distinct alphabet character.
       -a p: <key>=string.
       -a h: <key>=3x3 matrix e.g 17,17,5,21,18,21,2,2,19.
       -a v: <key>=string.
       -a o: <key>=string with length = <text>.
    ```
