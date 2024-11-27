# Peer-to-Peer-Traffic-Light-and-Pedestrian-Light

This project demonstrates a two-Arduino traffic light control system using the I2C protocol. It simulates a scenario where a pedestrian button press can influence the traffic light states, enabling pedestrians to cross safely.

## Overview

The project consists of two Arduinos:
1. **Master Arduino**: Manages the pedestrian button and sends signals to the slave Arduino when the button is pressed.
2. **Slave Arduino**: Controls the traffic lights for vehicles and pedestrians based on signals received from the master.

### Master Responsibilities:
- Monitors a pedestrian button.
- Sends a signal to the slave when the button is pressed.
- Controls pedestrian traffic lights (red and green).

### Slave Responsibilities:
- Manages vehicle traffic lights (green, yellow, red).
- Transitions between traffic states upon receiving signals from the master.

---

## Hardware Requirements

- 2 Arduino boards
- 1 push button
- 5 LEDs:
  - 2 for pedestrian lights (red and green)
  - 3 for vehicle lights (red, yellow, green)
- 5 resistors (220Ω or similar for LEDs)
- Connecting wires
- Breadboard(s)

---

## Circuit Diagram

### Master Arduino:
- **Button**: Connected to pin 8 (with pull-down resistor).
- **Pedestrian Red LED**: Connected to pin 9.
- **Pedestrian Green LED**: Connected to pin 6.

### Slave Arduino:
- **Vehicle Green LED**: Connected to pin 7.
- **Vehicle Yellow LED**: Connected to pin 4.
- **Vehicle Red LED**: Connected to pin 2.

Both Arduinos are connected via the I2C interface:
- **SDA**: Connect SDA pins of both Arduinos.
- **SCL**: Connect SCL pins of both Arduinos.
- **GND**: Ensure the ground is shared between the Arduinos.

---

## Code Explanation

### Master Code
- **Setup**:
  - Initializes I2C in master mode.
  - Configures the pedestrian button and LEDs as inputs/outputs.
  - Sets the initial state with the pedestrian red LED ON.
- **Loop**:
  - Monitors the pedestrian button.
  - When pressed, it:
    - Activates the pedestrian red light.
    - Sends a signal ('B') to the slave Arduino.
    - Waits for the pedestrian crossing period.
    - Resets the pedestrian light to its initial state.

### Slave Code
- **Setup**:
  - Initializes I2C in slave mode with address `8`.
  - Registers an interrupt handler (`Receive`) for incoming I2C signals.
  - Configures the vehicle LEDs as outputs and starts with the green LED ON.
- **Loop**:
  - Implements a state machine (`TrafficState`) to manage traffic light transitions:
    1. **GREEN**: Vehicles move freely.
    2. **YELLOW**: Warns vehicles to stop.
    3. **RED_WITH_PEDESTRIAN_GREEN**: Vehicles stop, and pedestrians can cross.
    4. **YELLOW_AFTER_RED**: Prepares vehicles to resume movement.
- **Receive Function**:
  - Listens for signals from the master Arduino.
  - Transitions to the `YELLOW` state upon receiving a button press signal (`'B'`).

---

## Timing

- **Pedestrian Button Response**:
  - Red light ON: 2 seconds.
  - Green light ON: 6 seconds.
  - Reset state: Instantaneous after the delay.

- **Traffic Light Timing**:
  - Yellow light duration: 2 seconds.
  - Red light duration (with pedestrian crossing): 6 seconds.

---

## How to Use

1. Connect the hardware as described.
2. Upload the **Master** code to the master Arduino.
3. Upload the **Slave** code to the slave Arduino.
4. Press the pedestrian button to trigger the traffic light cycle.
5. Observe how the lights transition between states on both Arduinos.

---

## Notes

- Ensure both Arduinos share a common ground.
- You can modify timing values in the code to suit your requirements.
- The I2C address of the slave Arduino is set to `8`. Change this if using multiple I2C devices.

---

## Future Improvements

- Add more sophisticated traffic light patterns.
- Introduce sensors to detect vehicle and pedestrian presence.
- Expand the system to handle multiple intersections.

---

## License

This project is open-source and available under the MIT License.
