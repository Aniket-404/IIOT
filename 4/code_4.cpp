const int voltagePin = A0;
const int ledPin = 8;

float voltage;
float current = 0.5; // Assuming a constant current (in Amps)
float power;
const float maxPower = 1.5; // Example power threshold in watts

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Read the analog value from the potentiometer
  int voltageReading = analogRead(voltagePin);

  // Convert the analog reading to a voltage (0-5V range)
  voltage = (voltageReading * 5.0) / 1023.0;

  // Calculate power
  power = voltage * current;

  // Print values
  Serial.print("Simulated Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Assumed Current: ");
  Serial.print(current);
  Serial.print(" A, Power: ");
  Serial.print(power);
  Serial.println(" W");

  // Check if power exceeds the threshold
  if (power >= maxPower)
  {
    digitalWrite(ledPin, HIGH); // Turn on LED
  }
  else
  {
    digitalWrite(ledPin, LOW); // Turn off LED
  }

  delay(1000);
}
