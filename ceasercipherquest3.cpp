#include <iostream>
#include <string> //string manipulation

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
    string encode(const string& message) { //for memory management and speed
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


public: //Anyone can use this.
    void setShiftValue(int value) { //setter | acts like a person at a bank window.
        shiftValue = value;
    }

    int getShiftValue() { //getter
        return shiftValue;
    }

    // Authorized bridge to access the protected encode function from main()
    string generateEncryption(const string& message) { //Like a person at a bank window, you ask them to do this, and they'll do it.
        return encode(message);  //Takes the exact address of the message without changing it in any way, and pass it into the encode function that is privated.
    }

    // Decode function utilizing the protected encode function
    string decode(const string& message) {
        int originalShift = shiftValue; //Store the original shift in a temporary container
        
        // Decoding is just encoding with the opposite shift (26 - shiftValue) | change shiftvalue to a # that  pushes us all the way around the alphabet to our original starting point
        shiftValue = 26 - originalShift; 
        string decodedMessage = encode(message); //run the message through encode using the new shift variable
        
        // Restore original shift value | put original shift value back where it belongs
        shiftValue = originalShift;  
        
        return decodedMessage; 
    }
};



// Derived Class for Rot13
class Rot13Cipher : public CaesarCipher { //Uses inheritance
public:
    Rot13Cipher() {
        // Constructor sets the shift value directly to 13 via the base class method | autmatically runs every time an object of this class is created (this is for the tournament)
        setShiftValue(13); 
    }
};



int main() {
    string pick; //pick will hold yes or no answers
    string currentMessage = ""; //holds the text
    bool isMessageCaptured = false; //a bool/flag to remember is the user a;ready typed in a message during the encoding process so we dont force them to type again

    cout << "~~~~~~~~~~ Welcome to the Cipher Program! ~~~~~~~~~~\n\n";

    cout << "Do you want to encode a new message? (y/n or yes/no): ";
    cin >> pick; //input in console


    if (pick == "y" || pick == "yes") {
        cout << "Enter the message to be encoded: ";
        cin.ignore(); // Clear the input buffer before reading the string
        getline(cin, currentMessage); //reads the whole sentence, including the spaces.


        int shift; //input for shift value 
        cout << "Enter a shift value (1-13) to encode the message accordingly: ";
        cin >> shift;

        // Input validation
        while (shift < 1 || shift > 13) {
            cout << "Error, enter a shift value between 1 and 13: ";
            cin >> shift;
        }


        CaesarCipher encryptor; //create a object of type caesarcipher
        encryptor.setShiftValue(shift); //based on the methods, we can set the shift value to the shift we want it to be.
        
        // Using our public bridge to encode from outside the class
        currentMessage = encryptor.generateEncryption(currentMessage); //with our currentmessage varaible that we made up on top, we set it = to our encrpyted message that we generated
        isMessageCaptured = true; //set our flag/bool to true since we now have a saved ciphertext

        cout << "Encoded message using Caesar Cipher (shift value " << shift << "): " << currentMessage << "\n";
    }


    //-------------------------------------------------------------------------------------------------------------------------------
    //DECIPHERING PART
    cout << "Do you want to decode a captured message? (y/n or yes/no): ";
    cin >> pick;

    if (pick == "y" || pick == "yes") {
        if (!isMessageCaptured) { //if a message is NOT captured
            //Analogy: Like a coffee shop; the encryptor is where you place your order. At the pickup counter (the decryptor), the cashier has your order down.
            //They shouldn't ask you "what do oyu want to order" all over again. This is why we have the !IsMessageCaptured.
            //At the start of the program, that bool value is FALSE (cup empty). If you choose to be the encryptor, the message gets saved in currentmessage, and the bool is set to TRUE.
            //Later, the code asks if you want to be the decryptor. The IF statement says 'if it is not true that a message has been captured)
            //Without the if-statement, the user would have to retype the entire encrypted message again.
            cout << "Enter the captured message: ";
            cin.ignore(); //clear buffer
            getline(cin, currentMessage); //read entire message
        }


        bool guessedCorrectly = false; //default bool value
        
        while (!guessedCorrectly) {
            int guess;
            cout << "Enter your guess for the shift value (1-13) to decode the message: ";
            cin >> guess;

            while (guess < 1 || guess > 13) { //error check 
                cout << "Error, enter a shift value between 1 and 13: ";
                cin >> guess;
            }


            // Dynamic memory allocation using a base class pointer
            CaesarCipher* cipherPtr; //pointer oject that is not looking at anything at the moment in this line

            if (guess == 13) {
                cipherPtr = new Rot13Cipher(); //we build a NEW rot13 obj in memory, we link the pointer object we made up above so it points to this newely built object
                //Becuase we set our correct shift value to 13, the object, by default, has the shift value 13
                cout << "Decoding message using Rot13 Cipher (shift value 13):\n";
            } 
            else {
                cipherPtr = new CaesarCipher(); //create the new object due to inheritance
                cipherPtr->setShiftValue(guess); //constuctor
                cout << "Decoding message using Caesar Cipher (shift value " << guess << "):\n";
            }

            cout << "Encoded Message: " << currentMessage << "\n";
            string decodedMessage = cipherPtr->decode(currentMessage); //shove the decoded message in this varaible (cipherptr has access to decode)
            cout << "Decoded message: " << decodedMessage << "\n";

            cout << "Is the decoded message correct? (y/n or yes/no): ";
            cin >> pick;

            if (pick == "y" || pick == "yes") {
                cout << "Congratulations! You decoded the message correctly.\n";
                guessedCorrectly = true;
            } 
            else {
                cout << "Do you want to try again with a different shift value? (y/n or yes/no): ";
                cin >> pick;
                if (pick == "n" || pick == "no") {
                    guessedCorrectly = true; // Exit loop if they give up
                }
            }

            // Free the dynamically allocated memory to prevent memory leaks
            delete cipherPtr; 
        }
    }

    cout << "Exiting the program...\n";
    return 0;
}