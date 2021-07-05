

#include <LiquidCrystal.h>
#include<Keypad.h>
#include<EEPROM.h>
#include<dht.h>
#define outpin 7 //dht11 sensor pin
#define soilsenpin A0
#define relayPower 6
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A5, A4, A3, A2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,9 ,10 ,13 }; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
dht DHT;
void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
int a=0;
EEPROM.get(0,a);
int b=0;
EEPROM.get(2,b);
if(a==550&&b==200){
EEPROM.put(0,550);
EEPROM.put(2,200);}
pinMode(relayPower, OUTPUT);
}

void loop() 
{
 int readData = DHT.read11(outpin);
 int soilmax=0;
  EEPROM.get(2,soilmax);
  int soilmin=0;
  EEPROM.get(0,soilmin);
 float t = DHT.temperature;
 float h = DHT.humidity;
int val = analogRead(soilsenpin); // Read the analog value form soil sensor
int value=analogRead(A1);
  char n;
  lcd.clear();
 lcd.setCursor(4, 0);
lcd.print("WELCOME");
delay(3000);
/*while(1){
  if(val>soilmax){
    digitalWrite(relayPower, HIGH);
  }
  else{digitalWrite(relayPower, LOW);
  break;
  }
  
}
*/
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Enter code:");
lcd.setCursor(0,1);
n= keypad.waitForKey();
 
 lcd.print(n);
  delay(2000);
  lcd.clear();
if(n=='A'){
  lcd.setCursor(0,0);
  lcd.print("Temp.: ");
  lcd.print(t);
  lcd.print((char)223);//shows degrees character
  lcd.print("C");
  delay(3000);
}
else if(n=='B'){
    lcd.setCursor(0,0);
   lcd.print("Temp.: ");
  lcd.print((t*9.0)/5.0+32.0);  // Convert celsius to fahrenheit
   lcd.print((char)223);//shows degrees character
  lcd.print("F");
  delay(3000);
  }
else if(n=='C'){
    lcd.setCursor(0,0);
    lcd.print("Humi.: ");
  lcd.print(h);
  lcd.print("%");
  delay(3000);
}
else if (n=='1'){
  lcd.setCursor(0,0);
  lcd.print("Sensor output:");
  lcd.setCursor(0,1);
  lcd.print(val);
  delay(3000);
  }
else if(n=='2'){
  lcd.setCursor(0,0);
   lcd.print("Min moist.read:");
  lcd.setCursor(0,1);
  lcd.print(soilmin);
  delay(3000);
  }
else if(n=='3'){
  lcd.setCursor(0,0);
   lcd.print("Max moist.read:");
  lcd.setCursor(0,1);
  lcd.print(soilmax);
  delay(3000);
  } 
 
  else if(n=='4'){
  lcd.setCursor(0,0);
   lcd.print("Intensity :");
  lcd.setCursor(0,1);
  lcd.print(value,DEC);
  delay(3000);
  } 
   else if(n=='5'){
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Enter value:");
lcd.setCursor(0,1);
int n= printt();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("soil max moist=");
lcd.setCursor(0,1);
lcd.print(n);
EEPROM.put(2,n);
  delay(3000);
  } 
   else if(n=='6'){
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Enter value:");
lcd.setCursor(0,1);
int n= printt();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("soil min moist=");
lcd.setCursor(0,1);
lcd.print(n);
EEPROM.put(0,n);
  delay(3000);
  } 
  else if(n=='7'){
  char m;
   lcd.clear();
lcd.setCursor(0,0);

  m=keypad.waitForKey();
  lcd.print(m);
if(m=='1'){
    digitalWrite(relayPower, HIGH);
  }
  lcd.setCursor(1,0);
  m=keypad.waitForKey();
  lcd.print(m);
  
  if(m=='2'){
    digitalWrite(relayPower, LOW);
  }
}
}
int printt(){
int n=0;
while(1){
     char i;
   i=keypad.waitForKey();
   lcd.setCursor(0,0);
   if(i=='#'){
    lcd.clear();
     lcd.print("Enter value:");
    n=n/10;
    lcd.setCursor(0,1);
     lcd.print(n);
   
   }
else if(i=='D'){
   break;
 } 
 else{
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Enter value:");
lcd.setCursor(0,1);
 n=(n*10)+(i-'0');
 lcd.print(n);

 }}
return n; 
}
 
