#include "Rot13Cipher.h"

Rot13Cipher::Rot13Cipher() {
    // Constructor sets the shift value directly to 13 via the base class method | autmatically runs every time an object of this class is created (this is for the tournament)
    setShiftValue(13); 
}