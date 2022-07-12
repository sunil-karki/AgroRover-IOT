# AGRO ROVER: An automatic farming gadget using IOT (with NodeMCU)

A farming gadget (robot), which can be controlled remotely by the user using the concept of IOT (Internet of Things), particularly
by the use of a Wi-Fi module and an Arduino Mega Board. The user can interact with the system through the user interface, that is, the website.

The user or the farmer can be able to give command to the rover such as sowing the seeds, irrigating the fields and even monitoring the current weather conditions, which
all takes place remotely using the ESP-8266 Wi-Fi module connected to the Arduino Mega Board. In addition to that, the rover itself can be able to send the feedback information to
the user through the same Wi-Fi module to a website that can help the user to make more proper decisions in the future just by looking at the weather patterns, graphs and other data.

### Prerequisites

#### Hardware Requirements (Specific)
- 1 x Arduino Mega 2560
- 1 x Monster Driver Moto Shield
- 1 x NodeMCU
- 2 x High Torque Motor
- 4 x Motor
- 2 x Servo Motor
- 1 x Ultrasonic Sensor
- 1 x DHT 11 Sensor
- 1 x Relay
- 1 x Diode
- 1 x Resistor (100K)

#### Software Requirements

- Arduino Software (IDE)

### Block Diagram

![image](https://user-images.githubusercontent.com/23634853/178107229-eb15a6ec-af8a-48a1-bd8e-1d59bb7e3816.png)

### Work Flow

For Automatic Mode:

![Automatic Mode](https://user-images.githubusercontent.com/23634853/178107769-c4561cd1-9b51-4679-a89e-80f2214b12b0.png)

For Manual Mode:

![Manual Mode](https://user-images.githubusercontent.com/23634853/178107796-051f55d0-d7ea-4be3-83f6-32e260b63be8.png)


### Design View

Left Side View:

![Left Side View](https://user-images.githubusercontent.com/23634853/178107485-e27893c8-9948-412c-9bcf-06225195405f.png)

Right Side View:

![Right Side View](https://user-images.githubusercontent.com/23634853/178107534-10d3138f-50dd-47bb-90a0-303251f79cce.png)

Drilling, Sowing and Irrigating Section:

![Drilling, Sowing and Irrigating Section](https://user-images.githubusercontent.com/23634853/178107585-0ef1b0d7-ee03-4e7d-856c-203b3c0196e9.png)

### Screenshots

Webpage showing the User Interface:

![Webpage showing the Robot](https://user-images.githubusercontent.com/23634853/178103998-497f732c-83aa-4c60-ac02-36508961f8a8.png)

Webpage showing the collected Data:

![Webpage showing the collected Data](https://user-images.githubusercontent.com/23634853/178104111-66c1b9a8-a7e1-4d89-8f90-6419bacbe6bf.png)

Webpage showing Temperature Data Graph:

![Webpage showing Temperature Data Graph](https://user-images.githubusercontent.com/23634853/178104118-50b46479-a566-43e3-b896-6fd0abe81fca.png)

Webpage showing Humidity Data Graph:

![Webpage showing Humidity Data Graph](https://user-images.githubusercontent.com/23634853/178104174-119a3c5f-8ba2-4367-abc4-dd1dcb87006f.png)

Webpage showing the Controls:

![Webpage showing the Controls](https://user-images.githubusercontent.com/23634853/178104186-0aa9d278-c6da-49b6-b096-6a333eb5fa12.png)


## Authors

* **Bishnu Subedi** - *Initial work*
* **Sanjay Dangol** - *Initial work* 
* **Sunil Karki** - *Initial work* 

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

* Our teachers and mentors.
* The internet
