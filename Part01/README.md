# Smart Air Quality Monitor ☁️
## Part 01 — Hardware Setup & Raw Sensor Reading

**ESP8266 NodeMCU V2 + Sharp GP2Y1014 Dust Sensor**

Welcome to Part 01 of my Smart Air Quality Monitor project!

โปรเจกต์นี้เป็นการเรียนรู้ระบบสมองกลฝังตัว (Embedded Systems) ผ่านการเชื่อมต่อไมโครคอนโทรลเลอร์ ESP8266 กับเซนเซอร์ตรวจจับอนุภาคฝุ่น GP2Y1014 โดยเริ่มต้นจากการอ่านสัญญาณ Analog และแสดงผลผ่าน Serial Monitor

This tutorial introduces the fundamentals of interfacing an optical dust sensor with an ESP8266 microcontroller, reading analog signals, and observing raw sensor data.

---

## 1. Learning Objectives | วัตถุประสงค์

เมื่อจบบทเรียนนี้ ผู้เรียนจะสามารถ:

1. อธิบายหลักการทำงานเบื้องต้นของ GP2Y1014 ได้
2. ระบุหน้าที่ของขาเซนเซอร์และ ESP8266 ได้
3. เข้าใจการใช้วงจรขับ LED และการป้องกัน ADC
4. เขียนโปรแกรมอ่านค่า Analog ด้วย Arduino IDE
5. แสดงผล Raw ADC ผ่าน Serial Monitor
6. สังเกตการเปลี่ยนแปลงของสัญญาณจากเซนเซอร์ได้

**English:** By the end of this lesson, you will understand the sensor interface, LED pulse control, ADC sampling, and serial data output.

## 2. Required Components | อุปกรณ์

| Component | Quantity |
|---|---:|
| ESP8266 NodeMCU V2 | 1 |
| Sharp GP2Y1014 Dust Sensor | 1 |
| 150 Ω Resistor | 1 |
| 220 µF / 16 V Capacitor | 1 |
| Suitable LED driver components | As required |
| ADC voltage protection/scaling circuit | As required |
| Jumper Wires | As required |
| USB Cable | 1 |

**Software:** Arduino IDE and a Serial Monitor such as Arduino Serial Monitor or CoolTerm.

## 3. How the Sensor Works | หลักการทำงาน

GP2Y1014 เป็นเซนเซอร์ตรวจจับอนุภาคในอากาศโดยอาศัยหลักการกระเจิงของแสง (Optical Light Scattering)

ภายในเซนเซอร์มี LED และตัวรับแสง เมื่อมีอนุภาคผ่านบริเวณตรวจจับ แสงจะเกิดการกระเจิงและทำให้สัญญาณเอาต์พุตเปลี่ยนแปลง

The GP2Y1014 detects airborne particles using optical light scattering. Its analog output changes in response to scattered light detected by the internal optical receiver.

**Important:** The raw ADC value is not a calibrated PM2.5 concentration or an official AQI value.

## 4. Hardware Connections | การต่อวงจร

### Sensor pin functions

| GP2Y1014 Pin | Function |
|---|---|
| 1 — LED-GND | LED ground |
| 2 — LED | LED control terminal |
| 3 — LED power | LED supply circuit |
| 4 — S-GND | Signal ground |
| 5 — Vo | Analog output |
| 6 — VCC | Sensor supply |

ตรวจสอบหมายเลขขาและทิศทางของคอนเนกเตอร์จาก Datasheet ก่อนต่อสายทุกครั้ง

### ESP8266 interface

| ESP8266 | Purpose |
|---|---|
| Vin / 5 V supply | Sensor supply, when verified |
| GND | Common ground |
| D1 / GPIO5 | LED driver control |
| A0 | Analog input from a properly scaled Vo signal |

**Safety and compatibility notes**

- Do not assume the GP2Y1014 LED can be driven directly by an ESP8266 GPIO.
- Use a suitable active-low LED driver circuit.
- Verify the actual ADC input range of your NodeMCU board.
- Use voltage scaling or protection if the sensor output can exceed the allowed ADC input.
- Check the polarity of the electrolytic capacitor.
- Do not connect or power the circuit solely from an AI-generated wiring illustration.

The hardware wiring diagram will be published after verification against the actual circuit and sensor datasheet.

## 5. Software Setup | การตั้งค่า Arduino IDE

1. Install Arduino IDE.
2. Install the ESP8266 board package.
3. Connect the NodeMCU to your computer using USB.
4. Select **Tools → Board → NodeMCU 1.0 (ESP-12E Module)**.
5. Select the correct Serial Port.
6. Open `SmartAirMonitor.ino`.
7. Upload the program.

## 6. Source Code | โค้ดตัวอย่าง

Open the file:

`SmartAirMonitor.ino`

The program performs three operations:

1. Generates an LED control pulse.
2. Samples the analog input using `analogRead(A0)`.
3. Reports averaged raw ADC readings through Serial at 115200 baud.

The example uses a nominal 10 ms measurement cycle and reports the average approximately every 500 ms.

**Note:** The LED timing and ADC input voltage must be verified on the actual hardware before relying on the readings.

## 7. Serial Monitor | การอ่านค่า

Open Arduino Serial Monitor or CoolTerm.

Set the baud rate to **115200**.

Example output (illustrative values):

```csv
Time(s),RawADC
1.500,185.42
2.000,184.76
2.500,187.10
3.000,183.94
```

`Time(s)` represents elapsed time in seconds.

`RawADC` represents the average of raw ADC readings over the reporting interval.

The ESP8266 ADC typically uses a nominal 10-bit output range of 0–1023. Readings near the upper limit may indicate saturation and should be investigated.

## 8. Experiment | การทดลอง

ทดลองสังเกตค่า ADC ในสภาพแวดล้อมที่แตกต่างกัน เช่น ห้องที่มีเครื่องฟอกอากาศ ห้องทำงานทั่วไป และบริเวณนอกอาคาร

บันทึกว่าค่า ADC เปลี่ยนแปลงอย่างไร และพิจารณาว่าการเปลี่ยนแปลงนั้นอาจเกิดจากอนุภาคในอากาศ สัญญาณรบกวน หรือปัจจัยด้านวงจร

Avoid spraying aerosols or dispersing powders near people or directly into the sensor.

### Questions for learners

1. What does an ADC measure?
2. Why must the sensor LED be pulsed?
3. Why is ADC voltage protection important?
4. Does a higher ADC value always mean a higher PM2.5 concentration?
5. Why do we need calibration before reporting dust concentration?

## 9. Limitations | ข้อจำกัด

This is an introductory sensor-reading experiment.

- Raw ADC is not equivalent to PM2.5 concentration.
- The sensor response depends on particle properties and measurement conditions.
- ADC scaling depends on the specific development board.
- Accurate concentration measurements require further characterization and calibration against an appropriate reference.

## 10. What's Next? | บทเรียนถัดไป

**Part 02 — Data Collection & Signal Processing**

In the next part, we will explore:

- Serial data logging using CoolTerm
- CSV data collection
- ADC signal analysis
- Moving Average filtering
- Sensor response characterization

---

**Project:** Smart Air Quality Monitor

**Author:** Tuang Ratana

**GitHub:** https://github.com/mmtuang-em/Smart-Air-Quality-Monitor

**Homealearn:** @homealearn.tuang

*Learning by building, testing, and understanding.*
