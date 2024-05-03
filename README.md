# hill_cypher

2 by 2 Keys already generated in KEYS.txt. The code is in `Generate2x2Keys.cpp`

The word that the bruteforce is checking is present in the `main.cpp` file, in main(): "FRAKEAHDBM". 

The WL (wordlist) is the `10LetterWords.txt` file.

The message "FRAKEAHDBM" is decrypted with each Key from KEYS.txt, and each result is stored in MESG.txt.

For each line in MESG.txt, i compare the resulting word with the existing wordlist. If i find a match, it means that the 10 letter english word
was the one encrypted with a key to obtain the "FRAKEAHDBM" encrypted message.

The word that should result is `atomically` in the ENGL.txt file.


