
#include  <DHT.h> ;
#include  <LiquidCrystal_I2C.h> ;
#include <Wire.h> ;

//Constants
#define  DHTPIN 7   
#define DHTTYPE DHT11
#define R_LED 6
#define G_LED 5
LiquidCrystal_I2C lcd(0x27,16,2);  
DHT dht(DHTPIN, DHTTYPE);

//Variables
int chk;
float hum;  
float temp; 
const int TEMP_THRESHOLD_UPPER = 35; // upper threshold of temperature, change to your desire value
const int TEMP_THRESHOLD_LOWER = 35; // lower threshold of temperature, change to your desire value

void setup()
{
    Serial.begin(9600);
    lcd.init();
    dht.begin();                       
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setBacklight(HIGH);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
}

void  loop()
{
  delay(100);

    hum = dht.readHumidity();
    temp= dht.readTemperature();

    //Print temp and humidity values to LCD

    lcd.setCursor(0,0);
    lcd.print("Humidity:  ");
    lcd.print(hum);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Temp: "); 
    lcd.print(temp);
    lcd.println(" C");

    delay(100); //Delay 2 sec between temperature/humidity check.

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" C");

    delay(100); //Delay 2 sec.

    if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if(temp > TEMP_THRESHOLD_UPPER){
      Serial.println("The relay is turned on");
      digitalWrite(R_LED, HIGH);
      digitalWrite(G_LED, LOW); 
    } else if(temp < TEMP_THRESHOLD_LOWER){
      Serial.println("The relay is turned off");
      digitalWrite(R_LED, LOW);  
      digitalWrite(G_LED, HIGH); 
    }
  }
}