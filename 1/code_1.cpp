#define TEMP_PIN A0  // Pin where the TMP36 sensor is connected
#define BUZZER_PIN 8 // Buzzer pin

const float TEMPERATURE_THRESHOLD = 23.0; // Temperature threshold

void setup()
{
    // Initialize the buzzer pin as an output
    pinMode(BUZZER_PIN, OUTPUT);
    // Start the Serial Monitor for debugging
    Serial.begin(9600);
}

void loop()
{
    // Read the temperature from the TMP36 sensor
    int tempReading = analogRead(TEMP_PIN);
    float voltage = tempReading * (5.0 / 1023.0);
    float temperatureC = (voltage - 0.5) * 100.0; // Correct temperature conversion

    // Print the temperature to the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" C");

    // Check if the temperature exceeds the threshold
    if (temperatureC > TEMPERATURE_THRESHOLD)
    {
        // Turn on the buzzer
        digitalWrite(BUZZER_PIN, HIGH);
        // Print an alert message to the Serial Monitor
        Serial.println("ALERT: I'M BURNIN!!!");
    }
    else
    {
        // Turn off the buzzer
        digitalWrite(BUZZER_PIN, LOW);
    }

    // Wait for a short period before the next loop
    delay(500);
}
