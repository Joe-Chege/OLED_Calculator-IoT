#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

// Define I2C pins
#define I2C_SCL 2  // or 22
#define I2C_SDA 42 // or 21

// Define other pin mappings
#define PUSH_BUTTON_PIN 4
#define WATER_LEVEL_PIN 5
#define LDR_PIN 6
#define DHT_PIN 7
#define ONBOARD_LED_PIN 9
#define BUZZER_PIN 19
#define FAN_A_PIN 35
#define FAN_B_PIN 38

#define RED_PIN 16
#define BLUE_PIN 19
#define GREEN_PIN 33

#define LRCL_PIN 17
#define BCLK_PIN 18
#define DOUT_PIN 8
#define MQ2_PIN 34

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Keypad setup
const byte ROW_NUM = 4;    // 4 rows
const byte COLUMN_NUM = 4; // 4 columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};

byte pin_rows[ROW_NUM] = {1, 10, 9, 11}; // GPIO1, GPIO10, GPIO9, GPIO11 connect to the row pins
byte pin_column[COLUMN_NUM] = {12, 14, 21, 34};  // GPIO12, GPIO14, GPIO21, GPIO34 connect to the column pins

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

String input = "";  // Stores user input
float result = 0.0; // Stores result
char lastOperator = '\0'; // Tracks the last operator entered

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  Serial.println("Starting setup...");

  // Initialize I2C communication with specified pins
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C is the default I2C address
    Serial.println("SSD1306 OLED initialization failed. Check wiring!");
    while (true); // Stop the program here if the display initialization fails
  } else {
    Serial.println("OLED initialized successfully.");
  }
  
  // Clear the display and set initial display settings
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    // Produce a beep sound when any key is pressed
    tone(BUZZER_PIN, 1000);  // Frequency of 1000 Hz
    delay(100);  // Short delay for the beep sound
    noTone(BUZZER_PIN);  // Stop the tone after the delay
    
    // Print the pressed key to the Serial Monitor
    Serial.print("Key Pressed: ");
    Serial.println(key);
    
    if (key == '*') {
      // Clear both input and result
      input = "";
      result = 0.0;  // Reset result to 0
      lastOperator = '\0';  // Clear operator
      Serial.println("Input and result cleared.");
    } else if (key == '#') {
      // Perform calculation and display the result
      performCalculation();
    } else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
      // Store the operator and perform the intermediate calculation
      if (input.length() > 0) {
        performCalculation();
        lastOperator = key;
        input = "";  // Clear input for the next number
        Serial.print("Operator selected: ");
        Serial.println(lastOperator);
      }
    } else {
      // Append the pressed number to the input string
      input += key;
      Serial.print("Current input: ");
      Serial.println(input);
    }

    // Update the display
    updateDisplay();
  }
}

// Function to update the OLED display
void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Input: ");
  display.println(input);
  display.print("Result: ");
  display.println(result);
  display.display();
}

// Function to perform calculations based on the operator
void performCalculation() {
  float currentNumber = input.toFloat();
  Serial.print("Current number: ");
  Serial.println(currentNumber);

  if (lastOperator == 'A') {
    result += currentNumber;  // Addition for 'A'
  } else if (lastOperator == 'B') {
    result -= currentNumber;  // Subtraction for 'B'
  } else if (lastOperator == 'C') {
    result *= currentNumber;  // Multiplication for 'C'
  } else if (lastOperator == 'D') {
    if (currentNumber != 0) {
      result /= currentNumber;  // Division for 'D'
    } else {
      // Handle division by zero error
      result = 0;
      Serial.println("Error: Division by zero.");
      displayError("DIV/0!");
    }
  } else {
    // If no operator is stored, set result to the current number
    result = currentNumber;
  }

  Serial.print("Result: ");
  Serial.println(result);
}

// Function to display an error message
void displayError(String errorMessage) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print(errorMessage);
  display.display();
  delay(2000);
  display.clearDisplay();
}
