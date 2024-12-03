const uint8_t gpioNum = 2;

void ISRfunc(){
    Serial.println("Warunek spełniony (INT)");
}

void setup()
{
    // ustawiamy GPIO 2 jako wejście podciągnięte do plusa
    Serial.begin(9600);
    pinMode(gpioNum, INPUT_PULLUP);
}
void loop()
{
    Serial.println("Random print...");
    delay(100);
}