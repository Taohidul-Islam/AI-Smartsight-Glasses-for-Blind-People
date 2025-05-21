import cv2
import pyttsx3
import numpy as np
import requests

# Initialize text-to-speech engine
engine = pyttsx3.init()

# ESP32-CAM Configuration
ESP32_CAM_IP = "http://192.168.0.106"  # Replace with your ESP32-CAM's IP

# Load YOLO
def load_yolo():
    weights_path = "C:/yolo/yolov3.weights"
    config_path = "C:/yolo/yolov3.cfg"
    coco_names = "C:/yolo/coco.names"

    net = cv2.dnn.readNet(weights_path, config_path)
    layer_names = net.getLayerNames()
    output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers().flatten()]

    with open(coco_names, "r") as f:
        classes = [line.strip() for line in f.readlines()]

    return net, classes, output_layers

# Capture image from ESP32-CAM
def capture_image_from_esp32():
    try:
        response = requests.get(f"{ESP32_CAM_IP}/capture", timeout=10)
        if response.status_code == 200:
            with open("captured_image.jpg", "wb") as f:
                f.write(response.content)
            print("Image captured from ESP32-CAM!")
            return True
        else:
            print("Failed to capture image")
            return False
    except Exception as e:
        print(f"Error capturing image: {e}")
        return False

# Rest of the functions remain the same as in your original script
def detect_objects(image_path, net, classes, output_layers):
    image = cv2.imread(image_path)
    height, width, channels = image.shape

    blob = cv2.dnn.blobFromImage(image, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
    net.setInput(blob)
    outputs = net.forward(output_layers)

    detected_objects = []

    for out in outputs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.5:
                detected_objects.append(classes[class_id])
    
    return detected_objects

def speak_detected_objects(detected_objects):
    if detected_objects:
        unique_objects = set(detected_objects)
        speech_text = "Detected: " + ", ".join(unique_objects)
        print(speech_text)
        engine.say(speech_text)
        engine.runAndWait()
    else:
        print("No objects detected.")
        engine.say("No objects detected.")
        engine.runAndWait()

def main():
    # Load YOLO
    net, classes, output_layers = load_yolo()

    # Capture an image from ESP32-CAM
    if capture_image_from_esp32():
        # Detect objects in the captured image
        detected_objects = detect_objects("captured_image.jpg", net, classes, output_layers)

        # Speak the detected objects
        speak_detected_objects(detected_objects)

if __name__ == "__main__":
    main()