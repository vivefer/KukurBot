#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>  // Adafruit PCA9685 library

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

enum State {
  STOPPED, STARTED, ALIGNING, MANUAL, WALKING, SITTING, BOOT
};

State currentState = STOPPED;

// Servo channels
// Leg 1 (Front Right)
const int side1 = 0;  // Side hip servo
const int hip1 = 1;   // Front hip servo
const int knee1 = 3;  // Knee servo

// Leg 2 (Front Left)
const int side2 = 4;
const int hip2 = 5;
const int knee2 = 7;

// Leg 3 (Rear Right)
const int side3 = 8;
const int hip3 = 9;
const int knee3 = 11;

// Leg 4 (Rear Left)
const int side4 = 12;
const int hip4 = 13;
const int knee4 = 15;

// Servo pulse range
#define SERVO_MIN 125  // Min pulse length for 0°
#define SERVO_MAX 650  // Max pulse length for 180°

// Walking parameters from pseudocode
int walkAngle = 15;         // Walk angle (5-15)°
int elevationAngle = 25;    // Elevation angle (5-25)°
int toleranceAngle = 5;     // Tolerance angle for ground touch
int hipSideAngle = 10;      // Hip side servo angle
int baseAngle = 90;         // Base angle for neutral position

// Command processing
String inputString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(115200);
  
  pwm.begin();
  pwm.setPWMFreq(65);  // Set PWM frequency to 65Hz

  // Initialize all servos to neutral position
  setAllServos(baseAngle);
  Serial.println("Quadruped Robot Initialized.");
  Serial.println("Commands: 'boot' | 'sit' | 'walk' | 'stop' | 'align'");
  currentState = BOOT;
}

void loop() {
  // Process serial commands
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    processCommand(command);
  }

  // State machine
  switch (currentState) {
    case BOOT:
      bootSequence();
      break;
    case SITTING:
      sit();
      break;
    case WALKING:
      walk();
      break;
    case ALIGNING:
      alignServos();
      break;
    case STOPPED:
      // Do nothing, servos stay in last position
      break;
    default:
      break;
  }
}


void processCommand(String command) {
  if (command.equals("boot")) {
    currentState = BOOT;
    Serial.println("Executing boot sequence...");
  } else if (command.equals("sit")) {
    currentState = SITTING;
    Serial.println("Sitting down...");
  } else if (command.equals("walk")) {
    currentState = WALKING;
    Serial.println("Starting to walk...");
  } else if (command.equals("stop")) {
    currentState = STOPPED;
    Serial.println("Stopping all movement.");
  } else if (command.equals("align")) {
    currentState = ALIGNING;
    Serial.println("Aligning servos...");
  } else if (command.startsWith("set")) {
    // Format: set <servo> <angle>
    // Example: set knee1 90
    processManualCommand(command);
  }
    // Command processing for hip servos
  else if (command.startsWith("set_hips")) {
    int angle = command.substring(command.indexOf(' ') + 1).toInt();
    if (angle >= 0 && angle <= 180) {
      setAllHips(angle);
      Serial.println("All hip servos set to " + String(angle) + " degrees.");
    } else {
      Serial.println("Invalid angle! Use 0-180 degrees.");
    }
  }

  // Command processing for knee servos
  else if (command.startsWith("set_knees")) {
    int angle = command.substring(command.indexOf(' ') + 1).toInt();
    if (angle >= 0 && angle <= 180) {
      setAllKnees(angle);
      Serial.println("All knee servos set to " + String(angle) + " degrees.");
    } else {
      Serial.println("Invalid angle! Use 0-180 degrees.");
    }
  }

  // Command processing for side servos
  else if (command.startsWith("set_sides")) {
    int angle = command.substring(command.indexOf(' ') + 1).toInt();
    if (angle >= 0 && angle <= 180) {
      setAllSides(angle);
      Serial.println("All side servos set to " + String(angle) + " degrees.");
    } else {
      Serial.println("Invalid angle! Use 0-180 degrees.");
    }
  }
  }

void processManualCommand(String command) {
  // Parse manual servo commands
  // Format: set <servo> <angle>
  String parts[3];
  int partIndex = 0;
  int lastIndex = 0;
  
  for (int i = 0; i < command.length(); i++) {
    if (command.charAt(i) == ' ') {
      parts[partIndex] = command.substring(lastIndex, i);
      lastIndex = i + 1;
      partIndex++;
    }
  }
  parts[partIndex] = command.substring(lastIndex);
  
  if (partIndex == 2) {
    String servoName = parts[1];
    int angle = parts[2].toInt();
    
    if (angle >= 0 && angle <= 180) {
      setServoByName(servoName, angle);
    } else {
      Serial.println("Invalid angle! Enter a value between 0 and 180.");
    }
  }
}

void setServoByName(String name, int angle) {
  int servoPin = -1;
  
  if (name.equals("side1")) servoPin = side1;
  else if (name.equals("hip1")) servoPin = hip1;
  else if (name.equals("knee1")) servoPin = knee1;
  else if (name.equals("side2")) servoPin = side2;
  else if (name.equals("hip2")) servoPin = hip2;
  else if (name.equals("knee2")) servoPin = knee2;
  else if (name.equals("side3")) servoPin = side3;
  else if (name.equals("hip3")) servoPin = hip3;
  else if (name.equals("knee3")) servoPin = knee3;
  else if (name.equals("side4")) servoPin = side4;
  else if (name.equals("hip4")) servoPin = hip4;
  else if (name.equals("knee4")) servoPin = knee4;
  
  if (servoPin != -1) {
    pwm.setPWM(servoPin, 0, angleToPulse(angle));
    Serial.print(name);
    Serial.print(" set to ");
    Serial.print(angle);
    Serial.println(" degrees.");
  } else {
    Serial.println("Invalid servo name!");
  }
}

// Convert angle to PCA9685 pulse length
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

// Function to set all servos to a specific angle
void setAllServos(int angle) {
  setAllSides(angle);
  setAllHips(angle);
  setAllKnees(angle);
}

void setAllSides(int angle) {
  pwm.setPWM(side1, 0, angleToPulse(angle));
  pwm.setPWM(side2, 0, angleToPulse(angle));
  pwm.setPWM(side3, 0, angleToPulse(angle));
  pwm.setPWM(side4, 0, angleToPulse(angle));
}

void setAllHips(int angle) {
  pwm.setPWM(hip1, 0, angleToPulse(angle));
  pwm.setPWM(hip2, 0, angleToPulse(angle));
  pwm.setPWM(hip3, 0, angleToPulse(angle));
  pwm.setPWM(hip4, 0, angleToPulse(angle));
}

void setAllKnees(int angle) {
  pwm.setPWM(knee1, 0, angleToPulse(angle));
  pwm.setPWM(knee2, 0, angleToPulse(angle));
  pwm.setPWM(knee3, 0, angleToPulse(angle));
  pwm.setPWM(knee4, 0, angleToPulse(angle));
}

// Boot sequence - initialize the robot
void bootSequence() {
  Serial.println("Boot sequence initiated");
  
  // Set all servos to neutral position
  setAllServos(baseAngle);
  delay(1000);
  
  // Move knees and hips to standing position
  setAllKnees(baseAngle - 20);
  delay(500);
  setAllHips(baseAngle - 10);
  
  Serial.println("Boot sequence completed");
  currentState = STOPPED;
}

// Sitting position
void sit() {
  Serial.println("Sitting down");
  
  // Set knee servos to sitting position
  pwm.setPWM(knee1, 0, angleToPulse(baseAngle + 30));
  pwm.setPWM(knee2, 0, angleToPulse(baseAngle + 30));
  pwm.setPWM(knee3, 0, angleToPulse(baseAngle + 30));
  pwm.setPWM(knee4, 0, angleToPulse(baseAngle + 30));
  
  delay(500);
  
  // Set hip servos to sitting position
  pwm.setPWM(hip1, 0, angleToPulse(baseAngle + 20));
  pwm.setPWM(hip2, 0, angleToPulse(baseAngle + 20));
  pwm.setPWM(hip3, 0, angleToPulse(baseAngle + 20));
  pwm.setPWM(hip4, 0, angleToPulse(baseAngle + 20));
  
  Serial.println("Sitting complete");
  currentState = STOPPED;
}

// Align servos for testing
void alignServos() {
  Serial.println("Aligning servos...");
  
  // Test side servos
  for (int angle = baseAngle - 30; angle <= baseAngle + 30; angle += 10) {
    setAllSides(angle);
    Serial.print("Side servos at: ");
    Serial.println(angle);
    delay(300);
  }
  
  // Reset to neutral
  setAllSides(baseAngle);
  delay(500);
  
  // Test hip servos
  for (int angle = baseAngle - 30; angle <= baseAngle + 30; angle += 10) {
    setAllHips(angle);
    Serial.print("Hip servos at: ");
    Serial.println(angle);
    delay(300);
  }
  
  // Reset to neutral
  setAllHips(baseAngle);
  delay(500);
  
  // Test knee servos
  for (int angle = baseAngle - 30; angle <= baseAngle + 30; angle += 10) {
    setAllKnees(angle);
    Serial.print("Knee servos at: ");
    Serial.println(angle);
    delay(300);
  }
  
  // Reset to neutral
  setAllKnees(baseAngle);
  
  Serial.println("Alignment complete");
  currentState = STOPPED;
}

// Walking sequence based on pseudocode
void walk() {
  // Walking sequence: 1→3→4→2 (from pseudocode)
  // Leg 1 (Front Right)
  moveLeg(1);
  delay(200);
  
  // Leg 3 (Rear Right)
  moveLeg(3);
  delay(200);
  
  // Leg 4 (Rear Left)
  moveLeg(4);
  delay(200);
  
  // Leg 2 (Front Left)
  moveLeg(2);
  delay(200);
}



// Move individual leg according to walking pattern
void moveLeg(int legNumber) {
  int sideServo, hipServo, kneeServo;
  
  // Select the appropriate servos based on leg number
  switch (legNumber) {
    case 1: // Front Right
      sideServo = side1;
      hipServo = hip1;
      kneeServo = knee1;
      break;
    case 2: // Front Left
      sideServo = side2;
      hipServo = hip2;
      kneeServo = knee2;
      break;
    case 3: // Rear Right
      sideServo = side3;
      hipServo = hip3;
      kneeServo = knee3;
      break;
    case 4: // Rear Left
      sideServo = side4;
      hipServo = hip4;
      kneeServo = knee4;
      break;
    default:
      return;
  }
  
  // Based on pseudocode: FHS += walkAngle, KS -= (ElevationAngle + ToleranceAngle)
  
  // Step 1: Lift leg by adjusting knee servo
  pwm.setPWM(kneeServo, 0, angleToPulse(baseAngle - elevationAngle - toleranceAngle));
  delay(100);
  
  // Step 2: Move hip forward
  pwm.setPWM(hipServo, 0, angleToPulse(baseAngle + walkAngle));
  delay(100);
  
  // Step 3: Lower leg to ground
  pwm.setPWM(kneeServo, 0, angleToPulse(baseAngle - toleranceAngle));
  delay(100);
  
  // Step 4: Move hip backward
  pwm.setPWM(hipServo, 0, angleToPulse(baseAngle - walkAngle));
  delay(100);

  
  
  // Repeat for other legs as per sequence in pseudocode
  // The sequence "Same sequence for 2 4 3 1 3" from pseudocode is implemented in the walk() function
}
