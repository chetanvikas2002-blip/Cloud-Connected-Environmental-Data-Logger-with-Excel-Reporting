# Cloud-Connected-Environmental-Data-Logger-with-Excel-Reporting
Developed an IoT-based Environmental Data Logger using LPC2148, LM35, and MQ-2 sensors to monitor temperature and gas levels in real time. Data is transmitted via ESP-01 Wi-Fi to ThingSpeak for cloud monitoring and Excel reporting. The system features EEPROM- based threshold storage, LCD display, and buzzer alerts for abnormal conditions


# FEATURES:
1)Real-time temperature monitoring using LM35 sensor.\
2)Gas leakage detection using MQ-2 sensor.\
3)16x2 LCD display for live sensor readings and system status.\
4)ESP-01 Wi-Fi module for cloud connectivity.\
5)Uploads sensor data to ThingSpeak.\
6)Buzzer/LED alert when gas is detected or temperature exceeds the set limit.\
7)EEPROM (AT24C256) stores the temperature set point.\
8)Cloud data can be exported to Excel for reports and analysis.\


# BLOCK DIAGRAM:
<img width="1043" height="697" alt="WhatsApp Image 2026-09-22 at 6 58 56 PM" src="https://github.com/user-attachments/assets/42f2ade5-4b9c-4d74-8a50-c2d9c3edf9db" />


# HARDWARE COMPONENTS:
1)LPC2148 ARM7 Microcontroller\
2)ESP-01 Wi-Fi Module\
3)LM35 Temperature Sensor\
4)MQ-2 Gas Sensor\
5)AT24C256 EEPROM (I2C)\
6)16x2 LCD Display\
7)Buzzer/LED\
8)Power Supply (3.3V / 5V)\
9)Keypad(4x4).\


# SOFTWARE USED:
1)Keil µVision.\
2)Flash Magic.\
3)Embedded C Programming.\
4)ThingSpeak Cloud Platform.\


# WORKING:
# Step 1: System Initialization
* LPC2148 initializes all hardware and peripherals.
* LCD, UART, I2C, and ADC are initialized.
* ESP-01 connects to the Wi-Fi network using AT commands.
* RTC and EEPROM are initialized.
* LCD displays "System Ready" after successful initialization.

# Step 2: Temperature Measurement (LM35)
* LM35 senses the surrounding temperature.
* The sensor sends an analog voltage to the LPC2148 ADC.
* ADC converts the analog voltage into a digital value.
* LPC2148 calculates the temperature in °C.
* Temperature is continuously updated.

# Step 3: Gas Detection (MQ-2)
* MQ-2 detects combustible gases and smoke.
* The sensor output is connected to an ADC channel.
* LPC2148 reads the gas sensor value.
* The value is compared with a predefined threshold.
* If the value exceeds the threshold, the system indicates Gas Detected.

# Step 4: RTC Operation
* RTC maintains the current date and time.
* RTC communicates with LPC2148 through I2C.
* Each sensor reading is associated with a timestamp.
* The timestamp supports cloud logging and report generation.

# Step 5: LCD Display
The 16×2 LCD displays:
* Temperature value.
* Gas sensor status.
* Date and time.
* Wi-Fi connection status.
* Cloud upload status.
This allows the user to monitor the system in real time.

# Step 6: Temperature Set Point and EEPROM
* The temperature set point is stored in AT24C256 EEPROM.
* LPC2148 reads the stored value during startup.
* The user can change the set point using a keypad or switch.
* Updated values are written to EEPROM through I2C.
* The stored value remains available after power is switched OFF.

# Step 7: Threshold Comparison and Alarm
* LPC2148 compares temperature and gas sensor values with their thresholds.
* If temperature exceeds the set point or gas exceeds the threshold:
    * Buzzer turns ON.
    * Warning message appears on the LCD.
    * Alert data is prepared for cloud transmission.
* If values are within limits, the buzzer remains OFF.

# Step 8: ESP-01 Wi-Fi Communication
* LPC2148 communicates with ESP-01 through UART.
* AT commands are used to configure the Wi-Fi module.
* ESP-01 connects to the Wi-Fi network and establishes a TCP connection with ThingSpeak.
* Sensor data is sent using an HTTP GET request.
* The connection is closed after data transmission.
  
# Step 9: ThingSpeak Cloud Upload
* Temperature is uploaded to Field 1.
* Gas sensor value is uploaded to Field 2.
* Temperature set point is uploaded to Field 3.
* ThingSpeak stores the readings and displays them in graphical form.

# Step 10: Excel Report Generation
* Logged data is exported from ThingSpeak as a CSV file.
* The report contains temperature, gas values, date, and time.
* The data is used for monitoring history, analysis, and documentation.

# Step 11: Continuous Monitoring
The system continuously repeats the following process:
Read Sensors → Get RTC Time → Display on LCD → Compare Thresholds → Activate Alarm → Upload Data → Repeat
This enables continuous environmental monitoring, cloud-based data logging, and historical analysis.

# Overall Working: The LPC2148 collects temperature and gas sensor data, adds timestamps using the RTC, displays the information on an LCD, stores the temperature set point in EEPROM, and uploads sensor readings to ThingSpeak through the ESP-01 Wi-Fi module.


# FLOW CHART:
Initialize LCD
      |
Initialize UART
      |
Initialize I2C
      |
Initialize ADC
      |
Connect ESP-01 to Wi-Fi
      |
Read LM35 Temperature
      |
Read MQ-2 Gas Sensor
      |
Display Values on LCD
      |
Compare Temperature with Set Point
      |
If Temperature High or Gas Detected:
      |
Turn ON Buzzer
Send Data to ThingSpeak
Store Set Point in EEPROM
      |
Repeat Monitoring.


# PROJECT STRUCTURE:
Final_Majorp/
├── main.c
├── uart.c
├── uart.h
├── lcd.c
├── lcd.h
├── adc.c
├── adc.h
├── esp01.c
├── esp01.h
├── i2c.c
├── i2c.h
├── eeprom.c
├── eeprom.h
├── delay.c
├── delay.h
└── README.md.


# OUTPUT:
The system provides the following outputs:

1)Real-time temperature monitoring.
2)Gas leakage detection and alert generation.
3)Date and time display using RTC.
4)Permanent temperature set point storage in EEPROM.
5)Wi-Fi-based cloud monitoring using ESP-01.
6)ThingSpeak graphical visualization.
Excel/CSV report generation for recorded environmental data.


# THINKSPEAK INTEGERATION:
The ESP-01 communicates with ThingSpeak using AT commands over UART.

Example data uploaded:

Field 1 – Temperature 
Field 2 – Gas Sensor Status 
Field 3 - Temperature set point.


# CLOUD OUTPUT:
<img width="635" height="903" alt="WhatsApp Image 2026-09-22 at 7 01 32 PM" src="https://github.com/userattachments/assets/91dbaeb9-f2cf-4cea-9382-2db069f041fb" />


# HARDWARE CONNECTIONS:
<img width="1600" height="856" alt="WhatsApp Image 2026-09-22 at 7 01 48 PM" src="https://github.com/user-attachments/assets/43960bcd-87b4-4bcf-918e-8efd9e1bf85f" />


# APPLICATIONS:
1)Environmental Monitoring
2)Smart Home Safety
3)Gas Leakage Detection
4)Industrial Monitoring
5)IoT Data Logging
6)Cloud-Based Sensor Monitoring.


# FUTURE SCOPE:
1)Add humidity sensor (DHT11/DHT22).
2)Mobile app notifications.
3)Email/SMS alerts.
4)Multiple sensor support.
5)SD card data backup.


# AUTHOR
PACHIGULLA CHETAN VIKAS
