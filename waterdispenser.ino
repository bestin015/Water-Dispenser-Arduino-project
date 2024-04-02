  #include <LiquidCrystal_I2C.h>
  #include <SPI.h>
  #include <MFRC522.h>

  #define SS_PIN 10
  #define RST_PIN 9
  String UID = "03 7D A7 9B";

  const int motor1=7 ;
  const int motor2=6 ;
  const int motor3=5 ;
  const int motor4=4 ;
  const int en1=8;
  const int en2=3;

  LiquidCrystal_I2C lcd(0x27, 16, 2);
  MFRC522 rfid(SS_PIN, RST_PIN);


  void setup() {
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    pinMode(motor3, OUTPUT);
    pinMode(motor4, OUTPUT);
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);
    SPI.begin();
    rfid.PCD_Init();
  }

  void loop() {
    lcd.setCursor(4, 0);
    lcd.print("Welcome!");
    lcd.setCursor(1, 1);
    lcd.print("Put your card");

    if ( ! rfid.PICC_IsNewCardPresent())
      return;
    if ( ! rfid.PICC_ReadCardSerial())
      return;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scanning");
    Serial.print("NUID tag is :");
    String ID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      lcd.print(".");
      ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      ID.concat(String(rfid.uid.uidByte[i], HEX));
      delay(300);
    }
    ID.toUpperCase();

    if (ID.substring(1) == UID ) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Put your container!!");
      delay(1500);
      analogWrite(en1,255);
      analogWrite(en2,255);
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, LOW);
      delay(10000);
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
      lcd.clear();
    }
  else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong card!");
      delay(1500);
      lcd.clear();
    }
  }