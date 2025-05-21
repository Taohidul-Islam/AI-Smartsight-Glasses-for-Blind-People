# Ai-Smartsight-Glasses-for-Blind-People
It is a project on making a DIY glass for visually impaired people. With it's instant obstacle warning and AI based object detection with audio feedback makes it a unique yet useful innovation.
<br>
<h2>Things I used for this project</h2>
<ul>
  <li>ESP 32</li>
  <li>ESP 32 CAM</li>
  <li>Ultrasonic Sensor (HC-SR04)</li>
  <li>Buzzer (Small)</li>
  <li>Blurtooth Audio Reciver Module</li>
  <li>Mini Speaker</li>
  <li>18650 Li-ion batteries 2x</li>
  <li>Switch and button</li>
  <li>Jumpers and wires</li>
  <li>A PC (or a raspberry pi)</li>
  <li>Wi-Fi Router</li>
</ul>
<h2>Functional Division:</h2>
<p>Functions in this project is devided into two parts</p>
<ol>
  <li>Obstacle Alerting System</li>
  <li>AI Object Detection and Audio Feedback</li>
</ol>
<h3>Obstacle Alerting System</h3>
<p>Logic in obstacle alerting system is pretty simple. Two pins of the ESP-32, the buzzer, the ultrasonic sensor and batteries as powersource are used. AHere's a flowchart of it's workflow:</p>
<img src="https://github-production-user-asset-6210df.s3.amazonaws.com/117294890/446006880-4961cf42-1eec-42d2-9fa8-32d5e9654484.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAVCODYLSA53PQK4ZA%2F20250521%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20250521T102107Z&X-Amz-Expires=300&X-Amz-Signature=192bfcd8968d32f683b86cc031b32b8b3af719e1bff47039fc5e9048441c7182&X-Amz-SignedHeaders=host">
![image](https://github.com/user-attachments/assets/4961cf42-1eec-42d2-9fa8-32d5e9654484)
<h3>AI Object Detectioon and audio Feedback.</h3>
<p>Before using this logic you have to download yolov3.weights, yolov3.cfg, coco.names using this command promt inside bracket in your cmd <br>{curl -o yolov3.weights https://pjreddie.com/media/files/yolov3.weights <br>
curl -o yolov3.cfg https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3.cfg<br>
curl -o coco.names https://raw.githubusercontent.com/pjreddie/darknet/master/data/coco.names} <br>After that assign them yo following locations: <br> 
   weights_path = "C:/yolo/yolov3.weights"<br>
    config_path = "C:/yolo/yolov3.cfg"<br>
    coco_names = "C:/yolo/coco.names". <br>
  
Install all following libraries in you Python<br>
cv2<br>
pyttsx3<br>
numpy as np<br>
requests<br>
<p>This is a pretty complex logic. Here data flows through different mediums. The ESP-32 CAM has to be connected with the same Wi-Fi as the computer through putting SSID and Password in the ESP-32 CAM's code. The ESP-32 Devkit has to be connected with the PC Via bluetooth. And PC should be running the proper code on screen while these are operating.</p>
<p>When the button on ESP-32 pin 18 gets high, it gives a bluetooth keyboard signal(Ctrl + Alt + N) to the connected PC which then rund the code in screen. The code requests a image from the ESP-32 CAM which is streaming it's footage via Wi-Fi. Then it the PC gets image then it processes the image with YoloV3 AI model and detects if there is any identifiable object then oyttsx3 library converts the names of the identified objects into audio which is locally played by the PC. If a bluetooth audio reciver with a speaker is attached with the glasses and that is connected to that PC then the audio feedback is played to that glass. </p>


