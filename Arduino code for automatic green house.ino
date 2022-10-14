int pump1 = 13;
int pump2 = 12;
int light1 = 11;
int device  = 10;// device for cooling and heating
 const int sensor_pin = A1;  /* Soil moisture sensor O/P pin */
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <VarSpeedServo.h> 
VarSpeedServo servol; // create 
VarSpeedServo servo2; // seisms 
const int servolPin = 7; // atract 
const int servo2Pin = 6; 
void setup() {
  servol.attach(servolPin);  // at 
  servo2.attach(servo2Pin);  // ecce 
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(device, OUTPUT);
  pinMode(light1, OUTPUT);
  Serial.begin(9600); 
  Serial.println(F("DHTxx test!"));
  dht.begin();
  lcd.begin();
}
void loop() {
  // reads the input on analog pin A0 (value between 0 and 1023)
  int analogValue = analogRead(A3);
  Serial.print("Analog reading = ");
  Serial.print(analogValue);   // the raw analog reading
  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 10) {
    Serial.println(" - Dark");
  } else if (analogValue < 200) {
    Serial.println(" - Dim");
  } else if (analogValue < 500) {
    Serial.println(" - Light");
  } else if (analogValue < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(5);
  delay(2000);
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  int f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  delay(1000);
  // Compute heat index in Fahrenheit (the default)
  int hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  int hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
 lcd.backlight();
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(F("Hum:"));
 lcd.print(h);
 lcd.print(F("%")); 
 lcd.setCursor(8,0);
 lcd.print(F("Temp:"));
 lcd.print(t);
 lcd.print(F("c"));
 lcd.setCursor(0,1);
 lcd.print("Moisture=");
 lcd.print(moisture_percentage);
 lcd.print("%");  
  digitalWrite(pump1, HIGH);
  digitalWrite(pump2, HIGH);
  digitalWrite(device, HIGH);
  digitalWrite(light1, HIGH);
  if (moisture_percentage < 50){
    digitalWrite(pump1, HIGH);
  }
  else{
    (moisture_percentage > 50);
    digitalWrite(pump1, LOW);
if( t > 27){
    servol.write(60,100,true); 
    servo2.write(0,100,true); }
else{     
    servol.write(0,15,true);
    servo2.write(60,15,true); }
  }
if (t > 27)
{    
  digitalWrite(pump2, LOW);
  delay(1000);
  digitalWrite(pump2, HIGH);
  delay(15000);
  digitalWrite(pump2, LOW);
  delay(1000);
  digitalWrite(pump2, HIGH);
  delay(15000);
  digitalWrite(pump2, LOW);
  delay(1000);
  digitalWrite(pump2, HIGH);
  delay(15000);
}
  if(t > 27){
    digitalWrite(device,HIGH);  }
  else{
    digitalWrite(device,LOW); }
if (analogValue > 4 ){
  digitalWrite(light1,LOW); }
else{
  digitalWrite(light1,HIGH); }
  }