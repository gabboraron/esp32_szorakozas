# led villogtatása ESP32-WROVER-B által serial inputon kapott érték alapján
ötlet: https://github.com/Rad-hi

**Megvalósítás:**

kód:

```C
// Communication buffers lengths
#define MAX_BUFF_LEN        255 
#define CMD_BUFF_LEN        6

// LED configs
#define LED_PIN             5

// Globals
char c; // IN char
char str[CMD_BUFF_LEN];
uint8_t idx = 0; // Reading index

int started = 0;
char current_state = 'f';

void setup() {
  Serial.begin(115200); // Config serial port
  pinMode(LED_PIN, OUTPUT); // Config LED
}

void loop() {
  // Parse incoming command
  if(Serial.available() > 0){ // There's a command  
    c = Serial.read(); // Read one byte
    if(c != '\n'){ // Still reading
      str[idx++] = c; // Parse the string byte (char) by byte
    }
    else{ // Done reading
      str[idx] = '\0'; // Convert it to a string
      current_state =  str[0];
      idx = 0; // Reset reading index 
    }
    started = 1;
  }
  else{ // No input from commander
    current_state = 'b';
  }

 
  if (started == 1)
  {
    switch(str[0]){
    case 'b': // This is the default blinking state
      Serial.print("INITIAL ON");
      Serial.println(current_state);
      digitalWrite(LED_PIN, HIGH);
      break;
    case 'o': // ON for delay state
      Serial.print("ON");
      Serial.println(current_state);
      digitalWrite(LED_PIN, HIGH);
      break;
    
    case 'f': // OFF for dealy state
      Serial.print("OFF");
      Serial.println(current_state);
      digitalWrite(LED_PIN, LOW);
      break;
    
    case 'h': // do nothing
      Serial.print("HALT");
      Serial.println(current_state);
      while(1);
      break;
    
    default: 
        Serial.print("UNKNOWN");
        Serial.println(current_state);
        break;
    }
  }
  
}
```

másik oldalon
```Python
#! /usr/bin/env python3

import serial
import time


MAX_BUFF_LEN = 255
SETUP        = False
port         = None

prev = time.time()
while(not SETUP):
    try:
        #                    Serial port(windows-->COM), baud rate, timeout msg
        #port = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)
        port = serial.Serial("COM3", 115200, timeout=1)

    except: # Bad way of writing excepts (always know your errors)
        if(time.time() - prev > 2): # Don't spam with msg
            print("No serial detected, please plug your uController")
            prev = time.time()

    if(port is not None): # We're connected
        SETUP = True


# read one char (default)
def read_ser(num_char = 1):
    string = port.read(num_char)
    return string.decode()

# Write whole strings
def write_ser(cmd):
    cmd = cmd + '\n'
    port.write(cmd.encode())

# Super loop
while(1):
    string = read_ser(MAX_BUFF_LEN)
    if(len(string)):
        print(string)

    cmd = input() # Blocking, there're solutions for this ;)
    if(cmd):
        write_ser(cmd)
```