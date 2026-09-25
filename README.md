# -Non-Invasive-Vehicle-Overcrowding-Alert-System
A Vehicle with ultrasonic sensors to restrict over crowding which is connected with Bluetooth module Problem Statement:

            Public and private transport vehicles in India, particularly buses and shared vans, frequently operate beyond their safe passenger capacity due to the absence of real-time, automated occupancy monitoring. This project proposes a non-invasive, low-cost overcrowding alert system that uses dual ultrasonic sensors mounted at the vehicle's entry/exit point to automatically detect and count passengers entering and exiting, without requiring any physical contact with passengers or structural changes to the vehicle. 

Components Required:

Arduino Uno
HC-SR04 Ultrasonic sensors (2)
HC-05 Bluetooth module 
Buzzer 
Breadboard 
 jumper wires


Working methodology:
    
Both ultrasonic sensors continuously measure the distance to detect the presence of a passenger
If sensor 1 detects an object first,followed by sensor 2 within a short time window, the system registers this as an entry and increments the passenger count.
If sensor 2 detects an object first,followed by sensor 1, the system registers this an exit and decrement the count.
A Cooldown period after each detection prevents a single passenger from being counted multiple times.
When the count reaches the maximum capacity, the buzzer sounds a distinct alert pattern, and a “Bus Full” message is sent via bluetooth.
If further entry is attempted while a full capacity, the system denies the increment and re-alerts.


Objectives:

       To accurately detect and count the number of passengers entering and exiting a vehicle in real time.
To trigger an immediate alert once the vehicle reaches its maximum safe capacity.
To provide wireless, remote monitoring of occupancy status via Bluetooth.
To design a low-cost, non-invasive system suitable for retrofitting onto existing public transport vehicle.
Advantages:
Non-invasive — no structural modification to the vehicle needed.
Low-cost compared to CCTV/weight-sensor systems.
Real-time, automated — removes dependency on manual headcounts.
Wireless monitoring via Bluetooth adds convenience for drivers/conductors.
Conclusion:

This project demonstrates a practical, affordable, and non-invasive solution to the widespread problem of vehicle overcrowding using simple ultrasonic sensing and embedded systems. By automating occupancy tracking and providing real-time alerts, the system contributes toward safer and more regulated public transport, particularly relevant to Indian road safety and transport management needs 

