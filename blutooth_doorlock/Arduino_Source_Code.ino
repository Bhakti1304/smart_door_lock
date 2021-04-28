#include <Servo.h>
#include <EEPROM.h>
#include <Keypad.h>

Servo servo;
char state;

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
bool door = true;

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
void setup() {
  // put your setup code here, to run once:
  servo.attach(11);

  if(EEPROM.read(0) == 1) 
  {                       
    servo.write(70); 
    delay(200);
  }
  else if(EEPROM.read(0) == 2)
  {
    servo.write(120); 
    delay(200);
  }
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    char data;
    data = Serial.read(); 

    switch(data)
    {
      case '1': 
        if(EEPROM.read(0) == 1) 
        {
          EEPROM.write(0, 2);
          Serial.print("3"); 

          for(int a = 70; a <= 120; a++) 
          {
            servo.write(a);
            delay(15);
            Serial.println(servo.read());
          }
        }
        else if(EEPROM.read(0) == 2) 
        {
          EEPROM.write(0, 1); 
          Serial.print("4"); 
          for(int x = 120; x >= 70; x--) 
          {
            servo.write(x);
            delay(15);
          }
        }
        break;
      case '3': 
     
        if(EEPROM.read(0) == 1)
        {
          Serial.print("4");
        }
        else if(EEPROM.read(0) == 2)
        {
          Serial.print("3");
        }
        break;
    }
  }
  
}
