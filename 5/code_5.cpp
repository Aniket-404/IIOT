// EXTERNAL LIBRARIES
#include <Keypad.h>
#include <LiquidCrystal.h>
// DECLARE PINCODE
#define pinLength 6
char pinCode[pinLength] = {'1', '2', '3', '4', '5', '6'};
char tmpCode[pinLength];
char dots[pinLength + 1]; // +1 is a blank space
// DEFINE COLUMNS ROWS NUMBER OF THE KEYPAD
#define alarm 3
#define rows 4
#define columns 5
// MAP KEYS
char key[rows][columns] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '2', '3', 'C'},
    {'*', '0', '#', 'D'},
};
// DEFINE KEYPAD PINS
byte rowPin[rows] = {11, 10, 9, 8};
byte columPin[columns] = {7, 6, 5, 4};
// DECLARE KEYPAD OBJECT
Keypad pad = Keypad(makeKeymap(key), rowPin, columPin, rows, columns);
// DECLARE LCD OBJCET
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
// CONTROL VARIABLES
char tmpChar;
byte insertChars = 0;
void display(byte row, char text[])
{
    lcd.setCursor(0, row);
    lcd.print(text);
}
// VERIFY THE PIN
void verify()
{
    boolean correct = true;
    for (byte i = 0; i < pinLength; i++)
    {
        if (pinCode[i] != tmpCode[i])
        {
            correct = false;
        }
    }
    if (correct)
    {
        lcd.clear();
        display(0, "THE DOOR IS OPEN");
        delay(4000);
        lcd.clear();
        display(0, "DOOR LOCKED");
        delay(3000);
    }
    else
    {
        lcd.clear();
        display(0, "INCORRECT PIN");
        display(1, "RETRY");
        Serial.println("alert");
        for (byte i = 0; i < 10; i++)
        {
            digitalWrite(alarm, 1);
            delay(50);
            digitalWrite(alarm, 0);
            delay(50);
        }
        delay(500);
    }
    lcd.clear();
    display(0, "INSERT THE PIN");
    for (byte i = 0; i < pinLength; i++)
    {
        tmpCode[i] = '.';
        dots[i] = ' ';
    }
    insertChars = 0;
}
// ADD A DIGIT
void addChar()
{
    tmpCode[insertChars] = tmpChar;
    dots[insertChars] = '*';
    insertChars++;
    if (insertChars == pinLength)
    {
        verify();
    }
    else
    {
        display(0, "INSERT THE PIN");
        display(1, dots);
    }
}
// CANCE LAST DIGIT
void canc()
{
    if (insertChars >= 1)
    {
        dots[insertChars] = ' ';
        insertChars--;
    }
    lcd.clear();
    display(0, "INSERT THE PIN");
    display(0, dots);
}
// EXECUTE ONCE
void setup()
{
    lcd.begin(16, 2);
    pinMode(alarm, OUTPUT);
    Serial.begin(9600);
    display(0, "INSERT THE PIN");
}
// EXCUTE IN LOOP
void loop()
{
    tmpChar = pad.getKey();
    if (tmpChar)
    {
        switch (tmpChar)
        {
        case '*':
            verify();
            break;
        case '#':
            canc();
            break;
        default:
            addChar();
            break;
        }
    }
}