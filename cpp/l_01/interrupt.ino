const gpioNum = 2;

void setup()
{
    // ustawiamy GPIO 2 jako wejście podciągnięte do plusa
    Serial.begin(9600);
    pinMode(gpioNum, INPUT_PULLUP);
}
void loop()
{
       /* pooling */
    static lastValue = 1;
    bool currentValue == digitalRead(gpioNum);
    if (currentValue == 0 && lastValue == 1){
        /* Wystąpił warunek przerwania */
        Serial.println("Warunek spełniony");
    }
    lastValue = currentValue;
}