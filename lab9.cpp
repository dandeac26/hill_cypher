#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>

using namespace std;

ifstream f_keys("KEYS.txt");


ofstream of_engl("ENGL.txt");

#define ALPHA_SIZE 26

int alphabet[256];
char inverseAlph[256];


void gen_alpha(){
    int start = int('A');
    int end = int('Z');
    int num = 0;
    for(int i = start; i<=end; i++){
        alphabet[i] = num;
        num++;
    }
    for(int i = 0; i<26; i++){
        inverseAlph[i] = char(65+i);
    }
}

string encrypt2x2(string plain_message, string key){
    string encrypted_message = "";

    int a = alphabet[toupper(key[0])], b = alphabet[toupper(key[1])], 
        c = alphabet[toupper(key[2])], d = alphabet[toupper(key[3])];

    for(int i = 0; i < plain_message.size(); i+=2){

        int x = alphabet[toupper(plain_message[i])];
        int y = alphabet[toupper(plain_message[i+1])];

        encrypted_message += char(65 +( (a * x + b * y)%26));
        encrypted_message += char(65 +( (c * x + d * y)%26));

    }
    return encrypted_message;
}

int detKey(string key){
    int a = alphabet[toupper(key[0])], b = (alphabet[toupper(key[1])]), 
        c = (alphabet[toupper(key[2])]), d = alphabet[toupper(key[3])];

    int det = (a*d-b*c)%26 < 0 ? 26+(a*d-b*c)%26 : (a*d-b*c)%26 ;

    return det;
}


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}



string decrypt2x2(string encrypted_message, string key){
    string decrypted_message = "";

    int a1 = alphabet[toupper(key[0])], b1 = (alphabet[toupper(key[1])]), 
        c1 = (alphabet[toupper(key[2])]), d1 = alphabet[toupper(key[3])];

    int det = detKey(key);
    int one_over_det = modInverse(det,26);
    
    int a_inv = d1, b_inv = -b1,
        c_inv = -c1, d_inv = a1;

  
    int a = (a_inv*(one_over_det))%26 < 0? 26+(a_inv*(one_over_det))%26: (a_inv*(one_over_det))%26 , b = (b_inv*(one_over_det))%26 < 0 ? 26+(b_inv*(one_over_det))%26 :(b_inv*(one_over_det))%26 ,
        c = (c_inv*(one_over_det))%26 < 0? 26+(c_inv*(one_over_det))%26: (c_inv*(one_over_det))%26, d = (d_inv*(one_over_det))%26 < 0 ? 26+(d_inv*(one_over_det))%26: (d_inv*(one_over_det))%26;

    /**
     * ABBA
     * 
     * A    B   inverse:      1/det *  |    d    -b   |  %26
     * B    A                          |   -c     a   |
     */
   
    for(int i = 0; i < encrypted_message.size(); i+=2){

        int x = alphabet[toupper(encrypted_message[i])];
        int y = alphabet[toupper(encrypted_message[i+1])];

       
        int d1 = (a * x + b * y)%26 < 0 ? 26 + (a * x + b * y)%26 :  (a * x + b * y)%26 ;
        
        int d2 = (c * x + d * y)%26 < 0 ? 26 + (c * x + d * y)%26 :  (c * x + d * y)%26 ;
   
       
        decrypted_message += char(97 + (d1));
        
        decrypted_message += char(97 + (d2));
     
    }

    return decrypted_message;
}




void bruteforce(string encrypted_message){

    // put all possible words in MESG.txt
    ofstream of_msg("MESG.txt");
    string key;
    while(getline(f_keys, key)){
        of_msg << decrypt2x2(encrypted_message, key) << endl;
    }
    of_msg.close();
    f_keys.close();

    // read MESG.txt to see which are english words
    string word;
    ifstream f_msg("MESG.txt");
    
    string eng_word;
     
    while(getline(f_msg, word)){
        
        
        ifstream f_words("10LetterWords.txt");
        while(getline(f_words, eng_word)){
            if(word == eng_word)
            {
                of_engl << eng_word << std::endl;
            }
            
        }
        
        f_words.close();
    }

    
    f_msg.close();
    of_engl.close();
}

int main(int argc, char **argv){
    string key = "ABBA";
    if (argc>1) key = argv[1];

    gen_alpha();

    string message = encrypt2x2("cryptomonede", key);//FZGJ  ZZZY HMDN

    cout << decrypt2x2(message, key);
    
    bruteforce("FRAKEAHDBM");

    // for(int i = int('A'); i <= int('Z'); i++){
    //     cout<<char(i)<< ' '<< alphabet[i]<<endl;
    // }
    return 0;
}








// string decrypt2x2(string encrypted_message, string key){
//     string decrypted_message = "";

//     int a1 = alphabet[toupper(key[0])], b1 = (alphabet[toupper(key[1])]), 
//         c1 = (alphabet[toupper(key[2])]), d1 = alphabet[toupper(key[3])];

//     int det = detKey(key);
//     int one_over_det = modInverse(det,26);
    
//     int a_inv = d1, b_inv = -b1,
//         c_inv = -c1, d_inv = a1;

//     // cout << endl << a_inv << ' ' << b_inv << '\n' << c_inv << ' ' << d_inv<<endl;

//     int a = (a_inv*(one_over_det))%26 < 0? 26+(a_inv*(one_over_det))%26: (a_inv*(one_over_det))%26 , b = (b_inv*(one_over_det))%26 < 0 ? 26+(b_inv*(one_over_det))%26 :(b_inv*(one_over_det))%26 ,
//         c = (c_inv*(one_over_det))%26 < 0? 26+(c_inv*(one_over_det))%26: (c_inv*(one_over_det))%26, d = (d_inv*(one_over_det))%26 < 0 ? 26+(d_inv*(one_over_det))%26: (d_inv*(one_over_det))%26;


//     // int a = (a_inv*(one_over_det)), b = (b_inv*(one_over_det)),
//     //     c = (c_inv*(one_over_det)), d = (d_inv*(one_over_det));


//     // cout<< key << "'s det: "<<det << " 1/det = "<< (1/det) << ":\n" << '\t' << a<< ' ' << b << '\n' << '\t' << c << ' ' << d<< endl; 
//     /**
//      * ABBA
//      * 
//      * A    B         1/det *  |    A    -B   |  %26
//      * B    A                  |   -B     A   |
//      */
   
//     for(int i = 0; i < encrypted_message.size(); i+=2){

//         int x = alphabet[toupper(encrypted_message[i])];
//         int y = alphabet[toupper(encrypted_message[i+1])];

//         // cout<< endl << endl;
//         // cout<< char(toupper(encrypted_message[i]) )<< '=' << x <<' ' << char(toupper(encrypted_message[i+1]))<<'=' << y << endl;
//         // cout<< a << ' '<< b<< ' '<<c <<' ' <<d << "; \n ";
        
//         // (a*d-b*c)%N < 0 ? 26-(a*d-b*c)%N : (a*d-b*c)%N
//         int d1 = (a * x + b * y)%26 < 0 ? 26 + (a * x + b * y)%26 :  (a * x + b * y)%26 ;
//         // cout << (a * x + b * y)%26 << " : " << d1 << '\n';
//         int d2 = (c * x + d * y)%26 < 0 ? 26 + (c * x + d * y)%26 :  (c * x + d * y)%26 ;
   
       
//         // cout<<"terms: ";
//         // cout<< "brute : "<<(a * x + b * y)%26 << ", d1: " << d1 << ", char: " <<char(97 + (26+d1))<< endl;
//         // cout<< "brute : "<<(c * x + d * y)%26 << ", d2: " << d2 << ", char: " <<char(97 + (26+d2)) << endl;
//         decrypted_message += char(97 + (d1));
        
//         decrypted_message += char(97 + (d2));
//         // cout<<endl << endl;
     
//     }
//     return decrypted_message;
// }

// void bruteforce(string encrypted_message){

//     // put all possible words in MESG.txt
//     ofstream of_msg("MESG.txt");
//     string key;
//     while(getline(f_keys, key)){
//         of_msg << decrypt2x2(encrypted_message, key) << endl;
//     }
//     of_msg.close();
//     f_keys.close();

//     // read ME