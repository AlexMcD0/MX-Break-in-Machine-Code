/*
  Switch Break-In Machine Counter

  Reads a digital input on pin 2, adds value to counter, prints the count to the Serial Monitor.
*/

const int SwitchPin = 2;          // Constant value to assign the pin that the switch is connected to.

int ActuateSwitch = 0;            // State of switch, pressed or not.
int SwitchState = 0;
int ActuationCounter = 0;         // How many times the switch has been actuated.
int Prestate = 0;                 // Used to prevent double-clicking.
int RPS = 0;                      // Number of actuations per second. 
int PreviousActuationCount = 0;   // Holds the number of actuations from 5 seconds ago. 

void setup() {
  // Initialises serial communication at 9600 bits per second.
  Serial.begin(9600);
  // Set switch pin to INPUT mode. 
  pinMode(SwitchPin, INPUT);
}

void loop() {
  // Reads the state of the switch. 
  SwitchState = digitalRead(SwitchPin);

  // Checks if the switch is pressed. If it is, then the SwitchState is HIGH.
  if (SwitchState == HIGH && Prestate == 0) {
    ActuationCounter++;
    Serial.print("Number of actuations: ");
    Serial.println(ActuationCounter);
    Prestate = 1;
    delay(100);                // Delay between reads to stabilise input detection. 10ms as actuation every 150ms. Could make longer if needed.
  }

  else if (SwitchState == LOW) {
    Prestate = 0;
  }

  if (millis()%5000 == 0) {
    RPS = (ActuationCounter - PreviousActuationCount) / 5;
    
    PreviousActuationCount = ActuationCounter;
    
    Serial.print("                                        RPM at Time: ");
    Serial.print(millis()/1000);
    Serial.print("s is: ");
    Serial.println(RPS*60);
    delay(10);
  }
}
