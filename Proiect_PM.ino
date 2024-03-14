
#include  <DHT.h> ;
#include  <LiquidCrystal_I2C.h> ;
#include  <Wire.h> ;

#define  DHTPIN 7   
#define DHTTYPE DHT11
#define R_LED 6
#define G_LED 5

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,20,4);  


int chk;
float hum;  
float temp; 
const int TEMP_THRESHOLD_UPPER = 35; 
const int TEMP_THRESHOLD_LOWER = 35; 


byte grade[8] ={0b00111,0b00101,0b00111,0b00000,0b00000,0b00000,0b00000,0b00000};

byte Led_OFF_ST[8] ={0b00000,0b00011,0b00100,0b00100,0b00100,0b01111,0b00010,0b00010};

byte Led_OFF_DR[8] ={0b00000,0b11000,0b00100,0b00100,0b00100,0b11110,0b01000,0b01000};

byte Led_ON_ST[8] ={0b00000,0b00011,0b00111,0b00111,0b00111,0b01111,0b00010,0b00010};

byte Led_ON_DR[8] ={0b00000,0b11000,0b11100,0b11100,0b11100,0b11110,0b01000,0b01000};


void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.begin(16,4);               
  dht.begin();                       
  lcd.backlight();
  lcd.setBacklight(HIGH);
  
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  lcd.createChar(1, grade);
  lcd.createChar(2, Led_OFF_ST);
  lcd.createChar(3, Led_OFF_DR);
  lcd.createChar(4, Led_ON_ST);
  lcd.createChar(5, Led_ON_DR);
}

void  loop()
{
  delay(100);

    hum = dht.readHumidity();
    temp= dht.readTemperature();

    lcd.setCursor(3,0);
    lcd.print("HUM:");
    lcd.print(hum);
    lcd.print("%");
    lcd.setCursor(2,1);
    lcd.print("Temp:"); 
    lcd.print(temp);
    lcd.write(byte(1));
    lcd.print("C");



    delay(10); 


    if(temp < TEMP_THRESHOLD_UPPER){
    lcd.setCursor(0,2);
    lcd.print("G");
    lcd.write(byte(4));
    lcd.write(byte(5));

    lcd.setCursor(5,2);
    lcd.print("R");
    lcd.write(byte(2));
    lcd.write(byte(3));
    } 
    else if(temp >= TEMP_THRESHOLD_LOWER){
    lcd.setCursor(0,2);
    lcd.print("G");
    lcd.write(byte(2));
    lcd.write(byte(3));

    lcd.setCursor(5,2);
    lcd.print("R");
    lcd.write(byte(4));
    lcd.write(byte(5));
    }

    delay(10); 
    


    if(temp >= TEMP_THRESHOLD_UPPER){
      Serial.println("Red_led_High");
      digitalWrite(R_LED, HIGH);
      digitalWrite(G_LED, LOW); 
    } else if(temp < TEMP_THRESHOLD_LOWER){
      Serial.println("Green_led_High");
      digitalWrite(R_LED, LOW);  
      digitalWrite(G_LED, HIGH); 
    }
    
    lcd.setCursor(-2, 3);
    lcd.print("Manta Mihai");
}
