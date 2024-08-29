/*
R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>

// Wi-Fi and MQTT credentials
const char *ssid = "tedata";
const char *password = "01228938771";
const char *mqttServer = "3685792e82304816bc0095541d47f9d8.s1.eu.hivemq.cloud";
const int mqttPort = 8883;
const char *mqttTopic = "light/control";
const char *mqttUsername = "zm.ziadmohamed";
const char *mqttPassword = "2_y9Y9iTP7nLdLL";
const char *apiUrl = "http://185.192.97.183:3000/checkSecret";
const char *attendanceApiUrl = "http://185.192.97.183:3000/recordAttendance";

// Certificates for secure connection
const char *ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";
// LED pins
const int redLED = 25;
const int greenLED = 26;
const int whiteLED = 27;
const int yellowLED = 14;
const int ldrPin = 32; // LDR pin for auto mode

const int ROW_NUM = 4;
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROW_NUM] = {21, 19, 18, 5};
byte columnPins[COLUMN_NUM] = {22, 4, 15, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW_NUM, COLUMN_NUM);
Servo doorServo;

const int buzzerPin = 12;
const int irSensorPin = 33;
const int MQ2_PIN = 34;

// Predefined brightness levels
const int LOW_BRIGHTNESS = 20;    // ~33% brightness
const int MEDIUM_BRIGHTNESS = 80; // ~66% brightness
const int HIGH_BRIGHTNESS = 255;  // 100% brightness

// PWM settings
const int freq = 5000;
const int ledChannelRed = 7;
const int ledChannelGreen = 1;
const int ledChannelWhite = 2;
const int ledChannelYellow = 3;
const int buzzerChannel = 4;

const int resolution = 8;

// Track current LED modes
enum Mode
{
  OFF_MODE,
  LOW_BRIGHT,
  MEDIUM_BRIGHT,
  HIGH_BRIGHT,
  AUTO_MODE
};
Mode redMode = OFF_MODE;
Mode greenMode = OFF_MODE;
Mode whiteMode = OFF_MODE;
Mode yellowMode = OFF_MODE;

// Track current LED states
int redBrightness = 0;
int greenBrightness = 0;
int whiteBrightness = 0;
int yellowBrightness = 0;

String inputPassword = "";
String validPassword = "";
bool doorOpened = false;
unsigned long doorOpenedTime = 0;

// Function prototypes
void setupWiFi();
void setupPins();
void setLEDState(int ledChannel, int brightness);
void handleAutoMode();
void reconnectMQTT();
int getLEDChannel(String led);

void setup();
void loop();
void callback(char *topic, byte *payload, unsigned int length);
void setLEDState(int ledChannel, int brightness);
void handleAutoMode();
void reconnectMQTT();
void checkPassword();
void handleApiResponse(String response);
void openDoor();
void closeDoor();
void soundBuzzer(int duration);
void monitorPassage();
void checkForAttendance();
void handleKeypad();
void detectGas();

// Create Wi-Fi and MQTT client objects
WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);

  // Setup pins for LEDs and LDR
  setupPins();

  // Connect to Wi-Fi
  setupWiFi();

  // Set up secure MQTT connection
  espClient.setCACert(ca_cert);
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Connect to MQTT server
  reconnectMQTT();
}

void loop()
{
  if (!client.connected())
  {
    reconnectMQTT();
  }
  client.loop();

  // Handle auto mode for LEDs
  handleAutoMode();
  detectGas();
  handleKeypad();
  monitorPassage();
  checkForAttendance();
  delay(100);
}

void setupWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void setupPins()
{
  // Initialize LED pins as PWM outputs
  ledcSetup(ledChannelRed, freq, resolution);
  ledcSetup(ledChannelGreen, freq, resolution);
  ledcSetup(ledChannelWhite, freq, resolution);
  ledcSetup(ledChannelYellow, freq, resolution);
  ledcSetup(buzzerChannel, freq, resolution);

  // Attach the pins to the PWM channels
  ledcAttachPin(redLED, ledChannelRed);
  ledcAttachPin(greenLED, ledChannelGreen);
  ledcAttachPin(whiteLED, ledChannelWhite);
  ledcAttachPin(yellowLED, ledChannelYellow);
  ledcAttachPin(buzzerPin, buzzerChannel);
  // Initialize LDR pin
  pinMode(ldrPin, INPUT);
  pinMode(MQ2_PIN, INPUT);

  doorServo.attach(13);
  closeDoor(); // Ensure the door is closed initially
  pinMode(buzzerPin, OUTPUT);
  pinMode(irSensorPin, INPUT);

  // Set all LEDs initially to off
  setLEDState(ledChannelRed, 0);
  setLEDState(ledChannelGreen, 0);
  setLEDState(ledChannelWhite, 0);
  setLEDState(ledChannelYellow, 0);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload, length);
  String mode = doc["mode"];
  String led = doc["color"];
  int ledChannel;

  Mode newMode;
  if (mode == "Off")
  {
    newMode = OFF_MODE;
    setLEDState(getLEDChannel(led), 0);
  }
  else if (mode == "Low")
  {
    newMode = LOW_BRIGHT;
    setLEDState(getLEDChannel(led), LOW_BRIGHTNESS);
  }
  else if (mode == "Medium")
  {
    newMode = MEDIUM_BRIGHT;
    setLEDState(getLEDChannel(led), MEDIUM_BRIGHTNESS);
  }
  else if (mode == "High")
  {
    newMode = HIGH_BRIGHT;
    setLEDState(getLEDChannel(led), HIGH_BRIGHTNESS);
  }
  else if (mode == "Auto")
  {
    newMode = AUTO_MODE;
  }
  else
  {
    return;
  }

  if (led == "red")
  {
    redMode = newMode;
  }
  else if (led == "green")
  {
    greenMode = newMode;
  }
  else if (led == "white")
  {
    whiteMode = newMode;
  }
  else if (led == "yellow")
  {
    yellowMode = newMode;
  }
}

void setLEDState(int ledChannel, int brightness)
{
  ledcWrite(ledChannel, brightness);
}

void handleAutoMode()
{
  int ldrValue = analogRead(ldrPin);
  int brightness = map(ldrValue, 0, 1600, 255, 0);

  if (redMode == AUTO_MODE)
    setLEDState(ledChannelRed, brightness);
  if (greenMode == AUTO_MODE)
    setLEDState(ledChannelGreen, brightness);
  if (whiteMode == AUTO_MODE)
    setLEDState(ledChannelWhite, brightness);
  if (yellowMode == AUTO_MODE)
    setLEDState(ledChannelYellow, brightness);
}

void reconnectMQTT()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqttUsername, mqttPassword))
    {
      Serial.println("connected");
      client.subscribe(mqttTopic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

int getLEDChannel(String led)
{
  if (led == "red")
    return ledChannelRed;
  if (led == "green")
    return ledChannelGreen;
  if (led == "white")
    return ledChannelWhite;
  if (led == "yellow")
    return ledChannelYellow;
  return -1; // Invalid LED
}

void handleKeypad()
{
  char key = keypad.getKey();

  if (key)
  {
    Serial.print(key);
    inputPassword += key;

    if (key == '#')
    {
      Serial.println();
      checkPassword();
      inputPassword = ""; // Clear the input after checking
    }
  }
}

void checkPassword()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    Serial.println("Beginning HTTP request...");
    http.begin(apiUrl);
    http.addHeader("Content-Type", "application/json");

    String requestBody = "{\"secret\":\"" + inputPassword.substring(0, inputPassword.length() - 1) + "\"}";
    Serial.println("Sending POST request with body: " + requestBody);
    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0)
    {
      String response = http.getString();
      Serial.println("Response: " + response);
      handleApiResponse(response);
    }
    else
    {
      Serial.print("Error in HTTP request: ");
      Serial.println(http.errorToString(httpResponseCode));
    }
    http.end();
  }
  else
  {
    Serial.println("WiFi not connected");
  }
}

void handleApiResponse(String response)
{
  if (response.indexOf("\"msg\":\"correct\"") > 0)
  {
    Serial.println("Password correct");
    validPassword = inputPassword.substring(0, inputPassword.length() - 1); // Store valid password
    openDoor();
  }
  else
  {
    Serial.println("Incorrect password");
    soundBuzzer(1000);
  }
}

void openDoor()
{
  doorServo.write(90);
  Serial.println("Door opened");
  doorOpened = true;
  doorOpenedTime = millis(); // Store the time the door was opened
}

void closeDoor()
{
  doorServo.write(0);
  Serial.println("Door closed");
  doorOpened = false;
}

void monitorPassage()
{
  if (doorOpened && digitalRead(irSensorPin) == LOW)
  {
    Serial.println("Person detected passing through");

    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;
      Serial.println("Sending attendance record...");
      http.begin(attendanceApiUrl);
      http.addHeader("Content-Type", "application/json");

      String requestBody = "{\"secret\":\"" + validPassword + "\"}";
      Serial.println("Sending POST request with body: " + requestBody);
      int httpResponseCode = http.POST(requestBody);

      if (httpResponseCode > 0)
      {
        String response = http.getString();
        Serial.println("Attendance Response: " + response);
      }
      else
      {
        Serial.print("Error in HTTP request: ");
        Serial.println(http.errorToString(httpResponseCode));
      }
      http.end();
    }
    else
    {
      Serial.println("WiFi not connected");
    }

    delay(2000);        // Wait for 2 seconds after the person passes
    closeDoor();        // Close the door
    doorOpened = false; // Reset the flag
    doorOpenedTime = 0; // Reset the timer
  }
}

void checkForAttendance()
{
  // Check if 5 seconds have passed since the door was opened without any person detected
  if (doorOpened && millis() - doorOpenedTime > 5000)
  {
    soundBuzzer(1000);
    closeDoor();
    Serial.println("Not attended");
    doorOpened = false; // Reset the flag
    doorOpenedTime = 0; // Reset the timer
  }
}

void soundBuzzer(int duration)
{
  digitalWrite(buzzerPin, HIGH); // Turn buzzer on
  delay(duration);
  digitalWrite(buzzerPin, LOW); // Turn buzzer off
  delay(100);
}

void detectGas()
{
  int gasDetected = analogRead(MQ2_PIN);
  if (gasDetected > 2500)
  {
    digitalWrite(buzzerPin, HIGH); // Turn buzzer on
  }
  else
  {
    digitalWrite(buzzerPin, LOW); // Turn buzzer off
  }
}