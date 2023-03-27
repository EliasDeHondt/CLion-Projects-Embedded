void setup() {
    Serial.begin(9600); // start de seriële communicatie op 9600 baud
    pinMode(LED_BUILTIN, OUTPUT); // stel de ingebouwde LED in als uitgang
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH); // zet de LED aan
    delay(1000); // wacht 1 seconde
    digitalWrite(LED_BUILTIN, LOW); // zet de LED uit
    delay(1000); // wacht 1 seconde
    Serial.println("Hello, world!"); // stuur "Hello, world!" naar de seriële monitor
}

