
/*
 * Smart Air Quality Monitor
 * Part 01: Raw Sensor Reading
 *
 * Board: ESP8266 NodeMCU V2
 * Sensor: Sharp GP2Y1014
 *
 * Output: Time(s),RawADC
 *
 * Hardware requirements:
 * - D1 controls a suitable active-low LED driver.
 * - Sensor Vo is scaled to the board's safe A0 range.
 * - Sensor supply and grounds are correctly connected.
 *
 * Educational example: verify LED pulse timing
 * and electrical connections before use.
 */

const uint8_t LED_CONTROL = D1;
const uint8_t SENSOR_INPUT = A0;

const unsigned long SAMPLE_PERIOD_US = 10000;
const unsigned long REPORT_INTERVAL_MS = 500;

unsigned long lastReport = 0;
unsigned long sampleSum = 0;
unsigned int sampleCount = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_CONTROL, OUTPUT);
  digitalWrite(LED_CONTROL, HIGH);

  delay(1000);

  Serial.println("Time(s),RawADC");
}

int readDustSensor() {
  // LED ON: active-low driver
  digitalWrite(LED_CONTROL, LOW);

  // Sample approximately 280 us after LED ON
  delayMicroseconds(280);

  int adcValue = analogRead(SENSOR_INPUT);

  // Turn LED OFF immediately after sampling
  digitalWrite(LED_CONTROL, HIGH);

  return adcValue;
}

void loop() {
  unsigned long cycleStart = micros();

  int rawADC = readDustSensor();

  sampleSum += rawADC;
  sampleCount++;

  unsigned long now = millis();

  if (now - lastReport >= REPORT_INTERVAL_MS) {
    float avgADC = (float)sampleSum / sampleCount;

    Serial.print(now / 1000.0, 3);
    Serial.print(",");
    Serial.println(avgADC, 2);

    sampleSum = 0;
    sampleCount = 0;
    lastReport = now;
  }

  // Nominal 10 ms cycle
  while ((unsigned long)(micros() - cycleStart)
         < SAMPLE_PERIOD_US) {
    yield();
  }
}
