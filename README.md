 ## 2022-1학기 임베디드시스템응용 최종 과제⚡
---------------------------------------------------------------------------------------------------------------------


### **- 👪팀원**  

        김민수  
        김예진  
        이소현  

---
### **1. 블럭도 설명**

---
### **📃2. 코드 설명**
```
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
```

- MQTT를 이용해 아두이노 rp2040에서 얻은 값을 node-red로 전달

```
const char broker[] = "192.168.35.152";
int port = 1883;
const char topic_temp[]  = "temperature";
const char topic_accel[]  = "accelerometer";
const char topic_xpoint[]  = "xpoint";
const char topic_ypoint[]  = "ypoint";
const char topic_zpoint[]  = "zpoint";
```

- 주소를 저장해 MQTT로 전달할 topic 저장

```
IMU.readTemperature(temperature_deg);
IMU.readAcceleration(x, y, z);
```

- 아두이노 rp2040 센서를 이용해 값 받아오기

```
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
```

- MQTT를 이용해 node-red로 온도, xyz좌표 topic 전달

```
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
```

- MQTT를 이용해 좌표값에 따른 운동 상태 node-red로 전달
---
### **3. 노드레드 구성**

<center>
     <img src="https://user-images.githubusercontent.com/105187744/174597907-ea7428c9-98d4-4d52-bf36-5329722baba2.png">
 </center>

---
### **file_folder 4. 구동 화면**



---
### **🎞5. 구동 영상**

---
