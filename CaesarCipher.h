#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <string>

using namespace std;

//Class-
class CaesarCipher {
private: 
    int shiftValue; //locked variable inside the class; only the class can see/change this value.

protected:
    // Protected so derived classes can use it, but hidden from the outside; allows for inheriting classes to use it.

    //If we pass just 'string message', the computer would make an entire copy of the message, which is time wasting and memory wasting. 
    //We use & to pass the exact location of the original message.
    //Adding const to the message disallows altering or erasing. Encode reads it, but is forbidden from changing.
    string encode(const string& message); //for memory management and speed

public: //Anyone can use this.
    void setShiftValue(int value); //setter | acts like a person at a bank window.
    int getShiftValue(); //getter

    // Authorized bridge to access the protected encode function from main()
    string generateEncryption(const string& message); //Like a person at a bank window, you ask them to do this, and they'll do it.

    // Decode function utilizing the protected encode function
    string decode(const string& message);
};

#endif