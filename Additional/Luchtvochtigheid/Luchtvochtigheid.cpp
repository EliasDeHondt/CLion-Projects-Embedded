// Definieer de pinnen die zijn aangesloten op de DHT11 sensor
#define DHT11_PIN 7

// Definieer de pinnen die zijn aangesloten op het LCD-scherm
#define RS_PIN 12
#define EN_PIN 11
#define D4_PIN 5
#define D5_PIN 4
#define D6_PIN 3
#define D7_PIN 2

// Functie om een karakter te verzenden naar het LCD-scherm
void lcdWrite(uint8_t data, bool rs) {
    digitalWrite(RS_PIN, rs);
    digitalWrite(EN_PIN, HIGH);
    digitalWrite(D4_PIN, (data >> 4) & 1);
    digitalWrite(D5_PIN, (data >> 5) & 1);
    digitalWrite(D6_PIN, (data >> 6) & 1);
    digitalWrite(D7_PIN, (data >> 7) & 1);
    digitalWrite(EN_PIN, LOW);
    digitalWrite(D4_PIN, data & 1);
    digitalWrite(D5_PIN, (data >> 1) & 1);
    digitalWrite(D6_PIN, (data >> 2) & 1);
    digitalWrite(D7_PIN, (data >> 3) & 1);
    digitalWrite(EN_PIN, HIGH);
    digitalWrite(D4_PIN, LOW);
    digitalWrite(D5_PIN, LOW);
    digitalWrite(D6_PIN, LOW);
    digitalWrite(D7_PIN, LOW);
}

// Functie om een commando naar het LCD-scherm te verzenden
void lcdCommand(uint8_t command) {
    lcdWrite(command, false);
    delayMicroseconds(50);
}

// Functie om een karakter naar het LCD-scherm te verzenden
void lcdChar(char character) {
    lcdWrite(character, true);
    delayMicroseconds(50);
}

// Functie om de luchtvochtigheidswaarde van de DHT11-sensor uit te lezen
uint8_t readDHT11Humidity() {
    uint8_t data[5];
    pinMode(DHT11_PIN, OUTPUT);
    digitalWrite(DHT11_PIN, LOW);
    delay(18);
    digitalWrite(DHT11_PIN, HIGH);
    delayMicroseconds(40);
    pinMode(DHT11_PIN, INPUT);
    while (digitalRead(DHT11_PIN) == LOW);
    while (digitalRead(DHT11_PIN) == HIGH);
    for (int i = 0; i < 5; i++) {
        uint8_t byte = 0;
        for (int j = 0; j < 8; j++) {
            while (digitalRead(DHT11_PIN) == LOW);
            delayMicroseconds(30);
            if (digitalRead(DHT11_PIN) == HIGH) {
                byte |= (1 << (7 - j));
            }
            while (digitalRead(DHT11_PIN) == HIGH);
        }
        data[i] = byte;
    }
    return data[0];
}

void setup() {
    // Initialiseer de pinnen die zijn aangesloten op het LCD-scherm
    pinMode(RS_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(D4_PIN, OUTPUT);
    pinMode(D5_PIN, OUTPUT);
    pinMode(D6_PIN, OUTPUT);
    pinMode(D7_PIN, OUTPUT);

    // Initialiseer het LCD-scherm
    lcdCommand(uint8_t(0x02)); // Ga naar de eerste regel van het scherm
    lcdCommand(uint8_t(0x28)); // Initialiseer het scherm met 2 lijnen en 5x8 karakters per regel
    lcdCommand(uint8_t(0x0C)); // Zet het scherm aan en zet de cursor uit
}

void loop() {
    // Lees de luchtvochtigheid van de DHT11-sensor
    uint8_t humidity = readDHT11Humidity();

    // Schrijf de luchtvochtigheid naar het LCD-scherm
    lcdCommand(uint8_t(0x80)); // Ga naar de eerste positie van de eerste regel
    lcdChar('H');
    lcdChar('u');
    lcdChar('m');
    lcdChar('i');
    lcdChar('d');
    lcdChar(':');
    lcdChar(' ');
    lcdChar((humidity / 10) + '0'); // Zet het tiental van de luchtvochtigheid om naar een karakter en schrijf het naar het scherm
    lcdChar((humidity % 10) + '0'); // Zet het eenheid van de luchtvochtigheid om naar een karakter en schrijf het naar het scherm

    // Wacht 1 seconde voordat de luchtvochtigheid weer wordt gelezen
    delay(1000);
}