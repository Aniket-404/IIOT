void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  delay(1000);

  int temp = analogRead(A3);
  float volt = (5.00 * temp) / 1023;
  float temp_c = (volt - 0.5) / 0.01;

  Serial.print("Temperature = ");
  Serial.print(temp_c);
  Serial.println();

  if (temp_c >= 24)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}