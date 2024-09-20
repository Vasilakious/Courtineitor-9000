#include <ESP8266WiFi.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// WiFi credentials
const char SSID[] = "Bill";
const char WiFiPassword[] = "kappalol";

// Create an instance of the TSL2591 sensor
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

// Define the pin for the buzzer or speaker
#define BUZZER_PIN 15

// Define the threshold for intense light (in lux)
#define LIGHT_THRESHOLD 200 // Adjust this value as needed

#define MOTOR_CONTROL_PIN 9 // You can use any GPIO pin here

#define OPPOSITE_MOTOR_CONTROL_PIN 10 // You can use any GPIO pin here

// Function to control the DC motor
void controlMotor(bool state) {
  digitalWrite(MOTOR_CONTROL_PIN, state ? HIGH : LOW);
}

void controlOppositeMotor(bool state) {
  digitalWrite(OPPOSITE_MOTOR_CONTROL_PIN, state ? HIGH : LOW);
}

int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4, 

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4, 
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
   
  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
  REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,
  
  REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
  REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4, 
  NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, 
  NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

  REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

   NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
   
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

  NOTE_E5,4, NOTE_D5,2, REST,4
};

// Variables to store web request values
int timezoneOffset = 3;
int openHour = 0;
int openMinute = 0;
int closeHour = 0;
int closeMinute = 0;
bool alarmEnabled = false;
bool morningEnabled = true;

// Define NTP client and UDP
const char* ntpServer = "pool.ntp.org";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, timezoneOffset);

// Create a WiFi server on port 80
WiFiServer server(80);

// HTML components
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>Control Panel</title></head><body><div id='main'><h2>Control Panel</h2>";
String html_2 = "<form id='T1' action='SETTIMEZONE'><input name='offset' type='number' min='-12' max='12' placeholder='Timezone Offset'><input type='submit' value='Set Timezone'></form><br>";
String html_3 = "<form id='T2' action='SETOPENTIME'><input name='openhour' type='number' min='0' max='23' placeholder='Open Hour'><input name='openmin' type='number' min='0' max='59' placeholder='Open Minute'><input type='submit' value='Set Open Time'></form><br>";
String html_4 = "<form id='T3' action='SETCLOSETIME'><input name='closehour' type='number' min='0' max='23' placeholder='Close Hour'><input name='closemin' type='number' min='0' max='59' placeholder='Close Minute'><input type='submit' value='Set Close Time'></form><br>";
String html_5 = "<form id='A1' action='SETALARM'><input type='submit' value='Enable Alarm'></form><br>";
String html_6 = "<form id='M1' action='SETMORNING'><input type='submit' value='Enable Morning'></form><br>";
String html_7 = "</div></body></html>";

// Sensor read interval
unsigned long previousMillis = 0;
const long interval = 5000; // 5 seconds

// Function to display sensor details
void displaySensorDetails(void) {
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print(F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(F(" lux"));
  Serial.print(F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(F(" lux"));
  Serial.print(F("Resolution:   ")); Serial.print(sensor.resolution, 4); Serial.println(F(" lux"));
  Serial.println(F("------------------------------------"));
  delay(500);
}

// Function to configure the sensor
void configureSensor(void) {
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  Serial.println(F("------------------------------------"));
  Serial.print(F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
  switch(gain) {
    case TSL2591_GAIN_LOW:
      Serial.println(F("1x (Low)"));
      break;
    case TSL2591_GAIN_MED:
      Serial.println(F("25x (Medium)"));
      break;
    case TSL2591_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL2591_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
  Serial.print(F("Timing:       "));
  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
}

// Function to play the melody
void playMelody() {
  // change this to make the song slower or faster
  int tempo = 114;

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER_PIN);
  }
}

// Function to get current time (Mock function, replace with actual time-fetching code)
String getCurrentTime() {
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  // Convert formatted time to "HHMM" format
  int hours = formattedTime.substring(0, 2).toInt();
  int minutes = formattedTime.substring(3, 5).toInt();
  int currentTime = hours * 100 + minutes;
  return String(currentTime);
}

// Setup function
void setup(void) {
  Serial.begin(115200);
  Serial.println(F("Starting Adafruit TSL2591 Test!"));

  if (tsl.begin()) {
    Serial.println(F("Found a TSL2591 sensor"));
  } else {
    Serial.println(F("No sensor found ... check your wiring?"));
    while (1);
  }

  displaySensorDetails();
  configureSensor();

  // Set up the buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, WiFiPassword);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
}


void loop(void) {
  // Check if a client has connected
  WiFiClient client = server.accept();
  if (!client) {
    // Read and process sensor data every 5 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      // Print current time and light intensity
      uint32_t lum = tsl.getFullLuminosity();
      uint16_t ir, full;
      ir = lum >> 16;
      full = lum & 0xFFFF;
      float lux = tsl.calculateLux(full, ir);
      
      Serial.print(F("Current time: "));
      String currentTime = getCurrentTime();
      Serial.print(currentTime);
      Serial.print(F(" + Offset: "));
      Serial.print(timezoneOffset);
      Serial.print(F(" = Adjusted time: "));
      int adjustedTime = (currentTime.toInt() + timezoneOffset * 100) % 2400;
      Serial.println(adjustedTime);
      
      Serial.print(F("Light intensity (Lux): "));
      Serial.println(lux);
      
      // Print open and close times
      Serial.print("Open Time: ");
      Serial.print(openHour);
      Serial.print(":");
      Serial.println(openMinute);
      
      Serial.print("Close Time: ");
      Serial.print(closeHour);
      Serial.print(":");
      Serial.println(closeMinute);

      Serial.print("Morning: ");
      Serial.println(morningEnabled);
      Serial.print("Alarm: ");
      Serial.println(alarmEnabled);

      // Check open time and alarm conditions
      if (alarmEnabled && (adjustedTime / 100 == openHour && adjustedTime % 100 == openMinute)) {
        playMelody();
        controlMotor(true);
      } else if ((morningEnabled == 1) && (lux >= LIGHT_THRESHOLD)) {
        playMelody();
        controlMotor(true);
      } else if (adjustedTime / 100 == closeHour && adjustedTime % 100 == closeMinute) {
        playMelody();
        controlOppositeMotor(true);
      } else {
        Serial.print("Conditions for melody are not met.");
        controlMotor(false); // Turn off the motor
        controlOppositeMotor(false);
      }
    }
    return;
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

  // Handle web requests
  if (request.indexOf("SETTIMEZONE") > 0) {
    int pos = request.indexOf("offset=");
    if (pos > 0) {
      timezoneOffset = request.substring(pos + 7).toInt();
      if (timezoneOffset < -12 || timezoneOffset > 12) {
        client.print("HTTP/1.1 400 Bad Request\r\n\r\nInvalid Timezone Offset");
      } else {
        Serial.print("Timezone Offset Set to: "); Serial.println(timezoneOffset);
      }
    }
  } else if (request.indexOf("SETOPENTIME") > 0) {
    int posHour = request.indexOf("openhour=");
    int posMinute = request.indexOf("openmin=");
    if (posHour > 0 && posMinute > 0) {
      openHour = request.substring(posHour + 9, posHour + 11).toInt();
      openMinute = request.substring(posMinute + 8, posMinute + 10).toInt();
      Serial.print("Open Time Set to: "); Serial.print(openHour); Serial.print(":"); Serial.println(openMinute);
    }
  } else if (request.indexOf("SETCLOSETIME") > 0) {
    int posHour = request.indexOf("closehour=");
    int posMinute = request.indexOf("closemin=");
    if (posHour > 0 && posMinute > 0) {
      closeHour = request.substring(posHour + 10, posHour + 12).toInt();
      closeMinute = request.substring(posMinute + 9, posMinute + 11).toInt();
      Serial.print("Close Time Set to: "); Serial.print(closeHour); Serial.print(":"); Serial.println(closeMinute);
    }
  } else if (request.indexOf("SETALARM") > 0) {
    alarmEnabled = true;
    morningEnabled = false;
    Serial.println("Alarm Enabled");
  } else if (request.indexOf("SETMORNING") > 0) {
    morningEnabled = true;
    alarmEnabled = false;
    Serial.println("Morning Mode Enabled");
  }

  // Serve the HTML page
  client.print(header);
  client.print(html_1);
  client.print(html_2);
  client.print(html_3);
  client.print(html_4);
  client.print(html_5);
  client.print(html_6);
  client.print(html_7);

  delay(5);
}