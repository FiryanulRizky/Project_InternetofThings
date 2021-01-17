#include  <Wire.h>
#include <Adafruit_MLX90614.h>
#include  <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;

int jarak = 0;
float data = 0;
float rata = 0;
const int tirgPin = 5;
const int echoPin = 6;
long duration;
int distance;
const int buzzer = 2; //buzzer to arduino pin 2
int pos = 00;

void setup() 
{
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  mlx.begin();
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  myservo.attach(9);
}

void loop() 
{
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  duration  = pulseIn(6, HIGH);
  distance  = duration * 0.034 / 2;
  rata = data;
  
  if (distance <=5) { 
    data = mlx.readObjectTempC();
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Cek Suhu Tubuh");
    lcd.setCursor(0, 1);
    lcd.print("Suhu Tubuh: ");
    lcd.print(data);
    delay(2000);
     
  if (rata >=37){
    myservo.write(90);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Suhu Melebihi");
    lcd.setCursor(0, 1);
    lcd.print("Suhu Tubuh: ");
    lcd.print(data);
    tone(buzzer, 450); // Send 1KHz sound signal...
    delay(2000);
    noTone(buzzer);     // Stop sound...
    delay(2000);                     
  }
  lcd.clear();
  }  
  else {
     myservo.write(00);
     lcd.setCursor(1, 0);
     lcd.print("Cek Suhu Tubuh");
     lcd.setCursor(0, 1);
     lcd.print("Dekatkan Kepala");
     delay (2000);
  }
}
