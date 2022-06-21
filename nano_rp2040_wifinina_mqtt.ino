#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DSOX.h>
#include <PDM.h>

char ssid[] = "SK_WiFiGIGA2FAF" ; 
char pass[] = "1704038610" ;

WiFiClient wifiClient_temp;
MqttClient mqttClient_temp(wifiClient_temp);
WiFiClient wifiClient_accel;
MqttClient mqttClient_accel(wifiClient_accel);
WiFiClient wifiClient_xpoint;
MqttClient mqttClient_xpoint(wifiClient_xpoint);
WiFiClient wifiClient_ypoint;
MqttClient mqttClient_ypoint(wifiClient_ypoint);
WiFiClient wifiClient_zpoint;
MqttClient mqttClient_zpoint(wifiClient_zpoint);

                       
const char broker[] = "192.168.35.152";
int        port     = 1883;
const char topic_temp[]  = "temperature";
const char topic_accel[]  = "accelerometer";
const char topic_xpoint[]  = "xpoint";
const char topic_ypoint[]  = "ypoint";
const char topic_zpoint[]  = "zpoint";

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient_temp.connect(broker, port)|| !mqttClient_accel.connect(broker, port)||!mqttClient_xpoint.connect(broker, port)||!mqttClient_ypoint.connect(broker, port)||!mqttClient_zpoint.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient_temp.connectError()||mqttClient_accel.connectError()||mqttClient_xpoint.connectError()||mqttClient_ypoint.connectError()||mqttClient_zpoint.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  
  if (!IMU.begin())
  
  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  mqttClient_temp.poll();
  mqttClient_accel.poll();
  mqttClient_xpoint.poll();
  mqttClient_ypoint.poll();
  mqttClient_zpoint.poll();

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (IMU.temperatureAvailable() || IMU.accelerationAvailable())
    {
      int temperature_deg = 0;
      float x, y, z;
      IMU.readTemperature(temperature_deg);
      IMU.readAcceleration(x, y, z);
      float xpoint,ypoint,zpoint;
      xpoint=x;
      ypoint=y;
      zpoint=z;
      

      mqttClient_temp.beginMessage(topic_temp);
      mqttClient_temp.print(temperature_deg);
      mqttClient_temp.println(" °C");
      mqttClient_temp.endMessage();

      mqttClient_xpoint.beginMessage(topic_xpoint);
      mqttClient_xpoint.print(xpoint);
      mqttClient_xpoint.println("좌표 ");
      mqttClient_xpoint.endMessage();

      mqttClient_ypoint.beginMessage(topic_ypoint);
      mqttClient_ypoint.print(ypoint);
      mqttClient_ypoint.println("좌표 ");
      mqttClient_ypoint.endMessage();

      mqttClient_zpoint.beginMessage(topic_zpoint);
      mqttClient_zpoint.print(zpoint);
      mqttClient_zpoint.println("좌표 ");
      mqttClient_zpoint.endMessage();

      mqttClient_accel.beginMessage(topic_accel);
      if((x>-0.02 &&x<0.02) || (y>-0.03&&y<0.03) || (z>0.98 && z<1.02)){
        mqttClient_accel.print("정지");
       
      }
      else if((x>-1.0 && x<1.0) || (y>-1.0 && y<1.0) || (z>0.52 &&  z<-1.48)){
        mqttClient_accel.print("걷기");
        
      }
      else{
        mqttClient_accel.print("뛰기");
        
      }
      mqttClient_accel.endMessage();

      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.println(z);
    }
    Serial.println();

    count++;
  }
}
