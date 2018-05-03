
#include <Wire.h>
#include "RTClib.h"
#include <TimerOne.h>
#include "DHT.h"

#define DHTPIN 7     // what digital pin we're connected to
#define DHTTYPE DHT11 

#include <LiquidCrystal.h>
RTC_DS1307 RTC;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

DHT dht(DHTPIN, DHTTYPE);

void setup () {
    Serial.begin(9600);
    Serial.println("DHTxx test!");

    dht.begin();
    
    Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  Timer1.initialize(1000000);  //setup interrupt which occurs every 1 second
  Timer1.attachInterrupt(displayData);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.display();
  lcd.setCursor(0, 1);
  
}

String message1, message2, message3;

//Interrupt function - Displays data
void displayData(void){
  lcd.clear();
  lcd.print(message1);
  lcd.setCursor(0, 1);
  lcd.print(message2);
  lcd.print((char)223);
  lcd.print(message3);
}

void loop () {
    DateTime now = RTC.now(); 
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

// Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

    String slash = "/";
    String space = " ";
    String spaces = "   ";
    String colon = ":";
    String C = "C";
    String percent = "%";
    String RH = "RH";
    //Construct messages to be displayed in interrupt
    message1 = now.month() + slash + now.day() + spaces + now.hour() + colon + now.minute() + colon + now.second();
    message2 = space + t;
    message3 = C + spaces + spaces + h + percent + RH;
}
