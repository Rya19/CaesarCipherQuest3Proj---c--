#include "CaesarCipher.h"

string CaesarCipher::encode(const string& message) { 
    string result = ""; //empty string to store string that has been shifted

    //If uppercase, we shift using the shiftValue
    //If lowercase, we do the same but relative to 'a'
    //Anything else, like a space or punctuation, we leave it alone, which fulfills the directions on only applying the encoding logic to alphabetical characters.
    for (char ch : message) { //For each character in message
        if (isupper(ch)) {
            result += char((ch - 'A' + shiftValue) % 26 + 'A'); // % 26 to loop back. 26 is the len of the alphabet. Calculates shift, if it goes past 26, it wraps us back to the beginning of the alphabet.
        } else if (islower(ch)) {
            result += char((ch - 'a' + shiftValue) % 26 + 'a');
        } else {
            result += ch; 
        }
    }
    return result; //Return result after processing.
}

void CaesarCipher::setShiftValue(int value) { 
    shiftValue = value;
}

int CaesarCipher::getShiftValue() { 
    return shiftValue;
}

string CaesarCipher::generateEncryption(const string& message) { 
    return encode(message);  //Takes the exact address of the message without changing it in any way, and pass it into the encode function that is privated.
}

string CaesarCipher::decode(const string& message) {
    int originalShift = shiftValue; //Store the original shift in a temporary container
    
    // Decoding is just encoding with the opposite shift (26 - shiftValue) | change shiftvalue to a # that  pushes us all the way around the alphabet to our original starting point
    shiftValue = 26 - originalShift; 
    string decodedMessage = encode(message); //run the message through encode using the new shift variable
    
    // Restore original shift value | put original shift value back where it belongs
    shiftValue = originalShift;  
    
    return decodedMessage; 
}