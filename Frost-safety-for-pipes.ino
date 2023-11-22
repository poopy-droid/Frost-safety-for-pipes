const int temperaturePin = A0; // Analog pin for temperature sensor
const int waterShutoffValvePin = 2; // Digital pin for water shutoff valve
const int compressorPin = 3; // Digital pin for compressor
const int pressureSwitchPin = 4; // Digital pin for pressure switch
const int releaseValvePin = 5; // Digital pin for release valve

void setup() {
  pinMode(waterShutoffValvePin, OUTPUT);
  pinMode(compressorPin, OUTPUT);
  pinMode(pressureSwitchPin, INPUT);
  pinMode(releaseValvePin, OUTPUT);

  // Initialize the components to their default state
  digitalWrite(waterShutoffValvePin, LOW); // Assuming LOW opens the valve
  digitalWrite(compressorPin, LOW);
  digitalWrite(releaseValvePin, HIGH); // Assuming HIGH closes the valve
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 5; ++i) {
    float temperature = analogRead(temperaturePin) * 0.48828125; // Convert analog reading to temperature in degrees Celsius

    if (temperature < 5) {
      closeWaterShutoffValve();
      delay(5000); // 5 seconds
      openReleaseValve();
      startCompressor();
    }

    while (digitalRead(pressureSwitchPin) == LOW) {
      // Wait for the pressure switch to go high
    }

    stopCompressor();
    delay(5000); // 5 seconds
    openReleaseValve();

    
    Serial.print("Iteration: ");
    Serial.println(i + 1);

    // Reset the system for the next iteration
    resetSystem();
  }

  // The loop will exit after running five times
}

void closeWaterShutoffValve() {
  digitalWrite(waterShutoffValvePin, HIGH); // Assuming HIGH closes the valve
}

void openReleaseValve() {
  digitalWrite(releaseValvePin, LOW); // Assuming LOW opens the valve
  delay(5000); // 5 seconds
  digitalWrite(releaseValvePin, HIGH); // Close the release valve
}

void startCompressor() {
  digitalWrite(compressorPin, HIGH); // Turn on the compressor
}

void stopCompressor() {
  digitalWrite(compressorPin, LOW); // Turn off the compressor
}

void resetSystem() {
  digitalWrite(waterShutoffValvePin, HIGH); // Assuming HIGH closes the valve
  digitalWrite(compressorPin, LOW);
  digitalWrite(releaseValvePin, HIGH); // Assuming HIGH closes the valve
}