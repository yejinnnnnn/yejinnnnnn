 # 2022-1학기 임베디드시스템응용 최종 과제⚡
 Arduino RP2040와 MQTT를 이용해서 Node-red 꾸미기 
---------------------------------------------------------------------------------------------------------------------


### **👪팀원**  

 - 김민수
 - 이소현
 - 김예진
---
### **✔개발 환경**  
- Jetson Nano Developer Kit(jetpack 4.5 ver)
- USB Camera
- Arduino RP2040
- IDE : Arduino, Visual Code, Thonny
---
### **1. 📃블럭도 설명**
<center>
     <img src="https://user-images.githubusercontent.com/107833113/174710577-5b7bce31-ea7e-4969-aea3-dcaf322b8637.JPG">
</center>

---
### **2. 📃코드 설명**
- MQTT를 이용해 아두이노 rp2040에서 얻은 값을 node-red로 전달
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


- 주소를 저장해 MQTT로 전달할 topic 저장
```
const char broker[] = "192.168.35.152";
int port = 1883;
const char topic_temp[]  = "temperature";
const char topic_accel[]  = "accelerometer";
const char topic_xpoint[]  = "xpoint";
const char topic_ypoint[]  = "ypoint";
const char topic_zpoint[]  = "zpoint";
```

- 아두이노 rp2040 센서를 이용해 값 받아오기
```
IMU.readTemperature(temperature_deg);
IMU.readAcceleration(x, y, z);
```


- MQTT를 이용해 node-red로 온도, xyz좌표 topic 전달
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


- MQTT를 이용해 좌표값에 따른 운동 상태 node-red로 전달
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


---
### **3. 📞노드레드 구성**

 > 노드레드 구성도
   
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174597907-ea7428c9-98d4-4d52-bf36-5329722baba2.png">
</center>
   
Link : [NODE-RED UI](http://211.206.178.184:1880/ui/#!/0?socketid=9dEfMAmUUc7OH-74AAAN, "node-red ui link")     

---
### **4. 📟구동 화면**

 > 정지상태 구동 화면
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174605816-80b49fbe-5773-4d0e-bfbb-0700b7f9cb46.PNG">
</center>   
     
 > 걷는상태 구동 화면
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174605684-6ebd7a92-3bc2-4bac-9426-769167f786c5.PNG">
</center>   
   
 > 뛰는상태 구동 화면
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174605860-3158993f-6286-4d8e-80fb-9345ddd12895.PNG">
</center>   
    
 > 손모양 검출 구동 화면
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174605853-3a81fc7b-267a-45ef-8fd8-e3b471692e06.PNG">
</center>   
   
> 아두이노 구동 화면
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174632687-c2a21e6c-4590-4222-9b08-38e493f521a8.jpg">
</center>   


 > 카메라 구동 화면
<center>
     <img src="https://user-images.githubusercontent.com/105187744/174632545-3605ca4d-aa54-48ff-912f-3837c090a8d6.jpg">
</center>  

---
### **🎞5. 🎥구동 영상🎥**



Link : [YOUTUBE 객체 상태 검출 구동영상](https://youtu.be/-M-ynP_fBdc, "youtube link")   

---
