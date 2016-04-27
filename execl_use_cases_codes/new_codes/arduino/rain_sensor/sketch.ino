/*
 * Program to read/use rain sensor
 * Rain sensor: FC-37 
 */

/* Pin used for read from sensor */
#define SENSOR_PIN A0

int sensorValue = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    sensorValue = analogRead(SENSOR_PIN);
    
    Serial.print("Reading humidity: ");
    Serial.println(sensorValue);

    if (sensorValue > 800){
        Serial.println("==> Dry Weather <=="); 
    } else if (sensorValue <= 800 && sensorValue > 500){
        Serial.println("==> Light Rain <==");
    } else {
        Serial.println("==> Heavy Rain <==");
    }

    delay(2000);
}
