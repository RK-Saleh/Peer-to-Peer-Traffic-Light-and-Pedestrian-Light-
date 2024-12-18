//Master

#include <Wire.h>

void setup() { 
    Wire.begin(); // Start I2C as master
    pinMode(8, INPUT);      // Button
    pinMode(6, OUTPUT);     // Green 
    pinMode(9, OUTPUT);     // Red 

    // Start with pedestrian red
    digitalWrite(6, LOW); 
    digitalWrite(9, HIGH); 
}

void loop() { 
    if (digitalRead(8) == HIGH) { 
        // Pedestrian button pressed
        digitalWrite(6, LOW); //Green OFF
        digitalWrite(9, HIGH); //Red ON

        // Send button press signal to Slave
        Wire.beginTransmission(8); // Address of the slave Arduino
        Wire.write('B');           // Send 'B' for button press
        Wire.endTransmission();

        delay(2000); 
        digitalWrite(6, HIGH);    
        digitalWrite(9, LOW);     
        delay(6000); 
      
        // Reset to initial state
        digitalWrite(6, LOW);     
        digitalWrite(9, HIGH);    
    }
}


//Slave

#include <Wire.h>

enum TrafficState { GREEN, YELLOW, RED_WITH_PEDESTRIAN_GREEN, YELLOW_AFTER_RED };

// Initialize the traffic light state
TrafficState currentState = GREEN;

void setup() { 
    Wire.begin(8); // Start I2C as slave with address 8
    Wire.onReceive(Receive); // Register Receive Signal


 
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);

  
  
   // Start green 
    digitalWrite(2, LOW); 
    digitalWrite(4, LOW); 
    digitalWrite(7, HIGH);
 
}

void loop() { 
    switch (currentState) {
        case GREEN:
            // remains Green until a signal is received from The Master
            break;

        case YELLOW:
            digitalWrite(7, LOW);    
            digitalWrite(4, HIGH);   
            delay(2000);              
            currentState = RED_WITH_PEDESTRIAN_GREEN;
            break;

        case RED_WITH_PEDESTRIAN_GREEN:
            digitalWrite(4, LOW);   
            digitalWrite(2, HIGH);   
            delay(6000);              
            currentState = YELLOW_AFTER_RED; 
            break;

        case YELLOW_AFTER_RED:
           
            digitalWrite(2, LOW);    
            digitalWrite(4, HIGH);   
            delay(2000);             
            digitalWrite(4, LOW);    
            digitalWrite(7, HIGH);  
            currentState = GREEN;     
            break;
    }
}
//Buton
void Receive(int bytes) { 
    while (Wire.available()) { 
        char c = Wire.read(); 
        if (c == 'B') { 
            // Button pressed signal
            currentState = YELLOW; // Transition to yellow when button is pressed
        }
    }
}
