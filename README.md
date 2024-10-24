# Smart Calculator with OLED Display and Keypad

## Overview
This project implements a **smart calculator** using an OLED display and a 4x4 keypad. The calculator allows users to perform basic arithmetic operations: addition, subtraction, multiplication, and division. The results are displayed on the OLED screen, and a buzzer provides audio feedback for key presses. It also incorporates additional hardware connections for future expansions, such as sensors, but these are not utilized in the current version of the code.

## Features
- **Basic Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **User Input**: Utilizes a 4x4 matrix keypad for easy input of numbers and operations.
- **Real-time Display**: Displays the current input, operator, and result on an OLED screen in real-time.
- **Error Handling**: Gracefully handles errors such as division by zero by displaying an error message on the OLED.
- **Audio Feedback**: Provides a beep sound using a buzzer for every key press, enhancing user interaction.
- **Target Temperature Control**: Offers additional logic for controlling devices like a fan and buzzer based on temperature readings (expandable feature).

## Keypad Functions
The 4x4 keypad offers the following functionality for number input and basic arithmetic operations:
- **Numeric Input**: The digits **0-9** are used for entering numbers.
- **A**: Represents the addition (`+`) operation.
- **B**: Represents the subtraction (`-`) operation.
- **C**: Represents the multiplication (`*`) operation.
- **D**: Represents the division (`/`) operation.
- **#**: Triggers the calculation and displays the result of the arithmetic operation.
- **\***: Clears the current input and result, allowing the user to start over.

### Keypad Usage Example
- **Input a number**: Simply press the corresponding number key (e.g., `1`, `2`, etc.).
- **Perform an operation**: After entering the first number, press one of the operators:
  - Press `A` for addition (`+`)
  - Press `B` for subtraction (`-`)
  - Press `C` for multiplication (`*`)
  - Press `D` for division (`/`)
- **Complete the operation**: After entering the second number, press `#` to perform the calculation and display the result.
- **Clear the screen**: Press `*` to clear both the input and result for a fresh start.

## Hardware Requirements
- **Microcontroller**: Compatible with Arduino (e.g., Arduino Uno, ESP32)
- **OLED Display**: 128x64 pixels, SSD1306 compatible
- **Keypad**: 4x4 matrix keypad
- **Buzzer**: For audio feedback
- **Push Button**: Optional (for additional functionalities)
- **Various Sensors**: Such as DHT, LDR, and water level sensors (connected but not utilized in this code)
- **Wires**: For connecting components

## Pin Connections
| Component         | Pin       | Description                        |
|-------------------|-----------|------------------------------------|
| I2C SDA           | 42        | I2C Data line for OLED             |
| I2C SCL           | 2         | I2C Clock line for OLED            |
| Keypad Rows       | 1, 10, 9, 11 | Connect to the row pins of the keypad |
| Keypad Columns    | 12, 14, 21, 34 | Connect to the column pins of the keypad |
| Buzzer            | 19        | Output pin for the buzzer          |
| Onboard LED       | 9         | Not used in this code              |
| Water Level Sensor| 5         | Not used in this code              |
| LDR               | 6         | Not used in this code              |
| DHT Sensor        | 7         | Not used in this code              |
| Fan A             | 35        | Not used in this code              |
| Fan B             | 38        | Not used in this code              |
| MQ2 Gas Sensor    | 34        | Not used in this code              |

## Installation

### Hardware Setup:
1. Connect the OLED display and keypad to the specified GPIO pins on your microcontroller.
2. Connect the buzzer to the specified pin for audio feedback.
3. Ensure that all other components, such as the optional sensors, are wired correctly for future expansions.

### Software Setup:
1. Ensure you have the necessary libraries installed in your Arduino IDE:
    - **Adafruit GFX Library**
    - **Adafruit SSD1306**
    - **Keypad Library**
2. Create a new sketch in Arduino IDE and paste the provided code below.
3. Compile and upload the sketch to your microcontroller.

## Usage
1. **Power On**: Upload the code to your microcontroller and power it on.
2. **Input Numbers**: Use the keypad to enter numbers. Press the corresponding keys for the digits (`0-9`) and the following operations:
   - **A**: Addition (`+`)
   - **B**: Subtraction (`-`)
   - **C**: Multiplication (`*`)
   - **D**: Division (`/`)
   - **#**: Calculate and display the result
   - **\***: Clear the input and result
3. **View Output**: The OLED display shows the current input and the result after a calculation is performed.
4. **Audio Feedback**: The buzzer emits a beep sound on each key press.

## Code Explanation

### Initialization
- **I2C Communication**: The code initializes I2C communication for the OLED display using the defined SDA and SCL pins.
- **Keypad Setup**: Configures the 4x4 matrix keypad layout, mapping each key to specific row and column pins.
- **OLED Display Initialization**: Attempts to initialize the OLED display and outputs a success or failure message to the Serial Monitor.

### Main Loop
- **Key Detection**: Continuously checks for key presses using the `keypad.getKey()` function.
- **Input Handling**:
  - On key press, it emits a sound and displays which key was pressed.
  - If `*` is pressed, it clears the current input and result.
  - If `#` is pressed, it triggers the calculation.
  - If any operator (`A`, `B`, `C`, `D`) is pressed, it stores the operator and prepares for the next number input.
  - Appends number inputs to the input string for processing.
- **Display Update**: Calls the `updateDisplay()` function to refresh the OLED display with the latest input and result.

### Functions
- `updateDisplay()`: Clears the OLED display and prints the current input and result.
- `performCalculation()`:
  - Converts the current input string to a float number.
  - Executes the arithmetic operation based on the last operator pressed.
  - Handles division by zero with an error message.
- `displayError(String errorMessage)`: Displays error messages on the OLED screen and waits for 2 seconds before clearing.

## Additional Notes
- The code includes functionality for additional components (like sensors and fans) that are currently not implemented in the logic. These can be integrated as needed.
- Ensure proper power supply and connection stability to avoid unexpected behavior.
- Some of the hardware components listed are not actively used in this version of the project but are reserved for future expansion.

## Conclusion
This project is a simple yet effective implementation of a smart calculator that demonstrates how to interface an OLED display, keypad, and audio output with a microcontroller. It can serve as a foundation for more complex projects that require user input and real-time feedback. The additional hardware connections provide opportunities for future expansions, such as integrating sensor data or controlling other devices like fans or LEDs based on real-time conditions.
