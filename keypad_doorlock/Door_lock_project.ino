 #include <Keypad.h> // the library for the 4x4 keypad
#include <Servo.h> // the library to control the servo motor
#include <EEPROM.h>

Servo servo;

#define Password_Length 8 // the length of the password, if the password is 4 digits long set this to 5
int Position = 0; // position of the servo
char Particular[Password_Length]; // the password length 
char Specific[Password_Length] = "137926A"; // the password which is called specific in the code, change this to anything you want with the numbers 0-9 an dthe letters A-D
byte Particular_Count = 0, Specific_Count = 0; // counts the amount of digits and and checks to see if the password is correct
char Key; 
const byte ROWS = 4; // the amount of rows on the keypad
const byte COLS = 4; // the amount of columns on the keypad
char keys[ROWS][COLS] = { // sets the rowns and columns
  // sets the keypad digits
  {'1','2','3','A'}, 
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
bool SmartDoor = true; // the servo 
// the pins to plug the keypad into
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad myKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); // gets the data from the keypad

// locked charcater
byte Locked[8] = { 
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111
};
// open character
byte Opened[8] = {
  B01110,
  B00001,
  B00001,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111
};
void setup()
{
  servo.attach(11); // attaches the servo to pin 0
  ServoClose(); // closes the servo when you say this function

  delay(1000); // waits 4 seconds

}

void loop()
{
  if (SmartDoor == 0) // opens the smart door
  {
    Key = myKeypad.getKey(); // the word key = myKeypad which gets the value

    if (Key == '#') // when the '#' key is pressed

    {
      ServoClose(); // closes the servo motor
      delay(2000); // waits 3 seconds
      SmartDoor = 1; // closes the door
    }
  }

  else Open(); // keeps the door open
}

void clearData() // clears the data
{
  while (Particular_Count != 0) // counts the digits pressed
  {
    Particular[Particular_Count--] = 0; // counts how many digits
  }
  return; // returns the data
}

void ServoOpen() // opens the servo
{
  for (Position = 180; Position >= 0; Position -= 5) { // moves from 0 to 180 degrees
    servo.write(Position); // moves to the postion
    delay(15); // waits 15 milliseconds
  }
}

void ServoClose() // closes the servo
{
  for (Position = 0; Position <= 180; Position += 5) { // moves from position 0 to 180 degrees
    servo.write(Position); // moves to the position
    delay(15); // waits 15 milliseconds
  }
}

void Open() // function declarations
{
  
  Key = myKeypad.getKey(); // gets the keys you press from the keypad
  if (Key)
  {
    Particular[Particular_Count] = Key; 

    Particular_Count++; // counts the length of the password
  }

  if (Particular_Count == Password_Length - 1) // gets the length of the password 
  {
    if (!strcmp(Particular, Specific)) // counts the length and checks to see if the password is correct
    {
      ServoOpen(); // moves the servo 180 degrees
      SmartDoor = 0;
    }
    else {

      SmartDoor = 1; // closes the smart door
    }
    clearData(); // clears the data
  }
}
