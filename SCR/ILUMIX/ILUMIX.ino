/* 
  Project: ILUMIX (A lighting system for 8 channel relays, 60 patterns)

  Description:
  This project implements a dynamic lighting system using an Arduino Uno and a relay module with 60 channels.
  The system controls multiple relays to create visually appealing lighting patterns, with options for speed and mode adjustments.
  It allows switching between random and sequential pattern modes through the serial monitor by sending the command "r",
  and the speed of the patterns can be adjusted by entering a number between 1 and 50.

  Author: T.G Damika Akalanka
  Date Created: 2025/03/29
  GitHub Repository: [https://github.com/Damika3002](https://github.com/Damika3002)

  Features:
  - Control 60 relays to create a wide range of dynamic lighting effects.
  - Adjust speed of the lighting patterns (1 = fastest, 50 = slowest).
  - Toggle between random and sequential pattern modes using the serial monitor command 'r'.
  - User-friendly interface via serial monitor for real-time adjustments.
  - Secure settings modification with access control.

  License:
  This project is open-source and licensed under the MIT. Feel free to explore, modify, and contribute.
  Remember to give appropriate credit and share improvements with the community.

  Disclaimer:
  This project is for educational purposes and experimentation. The author is not responsible for any damage or misuse of the system.

  Special Thanks:
  - Arduino community for continuous support and inspiration.


  Support:
  For more projects and contributions, please visit my GitHub: [https://github.com/Damika3002](https://github.com/Damika3002).
  Your support is appreciated to help me continue developing more projects!

  Let's keep building, learning, and sharing knowledge together! 🚀✨
*/



/*                                                                                                                                                                                                                                                                             
BBBBBBBBBBBBBBBBB                                                AAA               KKKKKKKKK    KKKKKKK               AAA               LLLLLLLLLLL                            AAA               NNNNNNNN        NNNNNNNNKKKKKKKKK    KKKKKKK               AAA               
B::::::::::::::::B                                              A:::A              K:::::::K    K:::::K              A:::A              L:::::::::L                           A:::A              N:::::::N       N::::::NK:::::::K    K:::::K              A:::A              
B::::::BBBBBB:::::B                                            A:::::A             K:::::::K    K:::::K             A:::::A             L:::::::::L                          A:::::A             N::::::::N      N::::::NK:::::::K    K:::::K             A:::::A             
BB:::::B     B:::::B                                          A:::::::A            K:::::::K   K::::::K            A:::::::A            LL:::::::LL                         A:::::::A            N:::::::::N     N::::::NK:::::::K   K::::::K            A:::::::A            
  B::::B     B:::::Byyyyyyy           yyyyyyy                A:::::::::A           KK::::::K  K:::::KKK           A:::::::::A             L:::::L                          A:::::::::A           N::::::::::N    N::::::NKK::::::K  K:::::KKK           A:::::::::A           
  B::::B     B:::::B y:::::y         y:::::y                A:::::A:::::A            K:::::K K:::::K             A:::::A:::::A            L:::::L                         A:::::A:::::A          N:::::::::::N   N::::::N  K:::::K K:::::K             A:::::A:::::A          
  B::::BBBBBB:::::B   y:::::y       y:::::y                A:::::A A:::::A           K::::::K:::::K             A:::::A A:::::A           L:::::L                        A:::::A A:::::A         N:::::::N::::N  N::::::N  K::::::K:::::K             A:::::A A:::::A         
  B:::::::::::::BB     y:::::y     y:::::y                A:::::A   A:::::A          K:::::::::::K             A:::::A   A:::::A          L:::::L                       A:::::A   A:::::A        N::::::N N::::N N::::::N  K:::::::::::K             A:::::A   A:::::A        
  B::::BBBBBB:::::B     y:::::y   y:::::y                A:::::A     A:::::A         K:::::::::::K            A:::::A     A:::::A         L:::::L                      A:::::A     A:::::A       N::::::N  N::::N:::::::N  K:::::::::::K            A:::::A     A:::::A       
  B::::B     B:::::B     y:::::y y:::::y                A:::::AAAAAAAAA:::::A        K::::::K:::::K          A:::::AAAAAAAAA:::::A        L:::::L                     A:::::AAAAAAAAA:::::A      N::::::N   N:::::::::::N  K::::::K:::::K          A:::::AAAAAAAAA:::::A      
  B::::B     B:::::B      y:::::y:::::y                A:::::::::::::::::::::A       K:::::K K:::::K        A:::::::::::::::::::::A       L:::::L                    A:::::::::::::::::::::A     N::::::N    N::::::::::N  K:::::K K:::::K        A:::::::::::::::::::::A     
  B::::B     B:::::B       y:::::::::y                A:::::AAAAAAAAAAAAA:::::A    KK::::::K  K:::::KKK    A:::::AAAAAAAAAAAAA:::::A      L:::::L         LLLLLL    A:::::AAAAAAAAAAAAA:::::A    N::::::N     N:::::::::NKK::::::K  K:::::KKK    A:::::AAAAAAAAAAAAA:::::A    
BB:::::BBBBBB::::::B        y:::::::y                A:::::A             A:::::A   K:::::::K   K::::::K   A:::::A             A:::::A   LL:::::::LLLLLLLLL:::::L   A:::::A             A:::::A   N::::::N      N::::::::NK:::::::K   K::::::K   A:::::A             A:::::A   
B:::::::::::::::::B          y:::::y                A:::::A               A:::::A  K:::::::K    K:::::K  A:::::A               A:::::A  L::::::::::::::::::::::L  A:::::A               A:::::A  N::::::N       N:::::::NK:::::::K    K:::::K  A:::::A               A:::::A  
B::::::::::::::::B          y:::::y                A:::::A                 A:::::A K:::::::K    K:::::K A:::::A                 A:::::A L::::::::::::::::::::::L A:::::A                 A:::::A N::::::N        N::::::NK:::::::K    K:::::K A:::::A                 A:::::A 
BBBBBBBBBBBBBBBBB          y:::::y                AAAAAAA                   AAAAAAAKKKKKKKKK    KKKKKKKAAAAAAA                   AAAAAAALLLLLLLLLLLLLLLLLLLLLLLLAAAAAAA                   AAAAAAANNNNNNNN         NNNNNNNKKKKKKKKK    KKKKKKKAAAAAAA                   AAAAAAA
                          y:::::y                                                                                                                                                                                                                                             
                         y:::::y                                                                                                                                                                                                                                              
                        y:::::y                                                                                                                                                                                                                                               
                       y:::::y                                                                                                                                                                                                                                                
                      yyyyyyy                                                                                                                                                                                                                                                 
*/ 

#include <avr/pgmspace.h>
#define NUM_RELAYS 8
#define PATTERN_COUNT 60
#define MAX_HISTORY 4  // Maximum recent patterns to track

const int relays[NUM_RELAYS] = {2, 3, 4, 5, 6, 7, 8, 9};
int recentPatterns[MAX_HISTORY] = {-1, -1, -1, -1};  // To track recent patterns
int lastPattern = -1;

float speedFactor = 1;  // Speed factor

bool useRandomOrder = true;  // Flag to toggle between random or sequential pattern selection

unsigned long previousMillis = 0; // Variable to store the last time the relay was updated
float interval = 1000; // Interval for relays (in milliseconds)

void activateRelay(int relayIndex, int delayTime);
const char ascii_art[] PROGMEM = 
  "  ██╗██╗     ██╗     ██╗   ██╗███╗   ███╗██╗██╗  ██╗\n"
  "  ██║██║     ██║     ██║   ██║████╗ ████║██║╚██╗██╔╝\n"
  "  ██║██║     ██║     ██║   ██║██╔████╔██║██║ ╚███╔╝ \n"
  "  ██║██║     ██║     ██║   ██║██║╚██╔╝██║██║ ██╔██╗ \n"
  "  ██║███████╗███████╗╚██████╔╝██║ ╚═╝ ██║██║██╔╝ ██╗\n"
  "  ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═╝\n";

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < NUM_RELAYS; i++) {
        pinMode(relays[i], OUTPUT);
        digitalWrite(relays[i], HIGH); 
    }
    Serial.println("\nLighting system initialized.");
    
    
    Serial.println("\n📅 Date Created: 2025/03/29 🗓️");
    Serial.println("🌍 Greetings, Arduino Community! 👋");
    Serial.println("Every project is a step towards something greater. Let's keep pushing the boundaries of what's possible! 💪\n\n");

    
    for (int i = 0; i < strlen_P(ascii_art); i++) {
        char c = pgm_read_byte_near(ascii_art + i);
        Serial.print(c);
    }

    // Attribution
    Serial.println("\nBy Damika Akalanka 😊");
    Serial.println("\nFeel free to explore, modify, and share your improvements!");
    Serial.println("Use Serial input to change speed (e.g., 1 = faster, 50 = slower).");
    Serial.println("Use 'r' to toggle between random and sequential pattern mode.");
}


void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n'); 
        input.trim(); 

        if (input == "r") {
            useRandomOrder = !useRandomOrder;  
            Serial.print("Random mode: ");
            Serial.println(useRandomOrder ? "ON" : "OFF");
        } else {
            float newSpeed = input.toFloat(); 
            if (newSpeed >= 1 && newSpeed <= 50) {  
                speedFactor = newSpeed / 10;
                Serial.print("Speed factor updated: ");
                Serial.println(speedFactor);
            } else {
                Serial.println("Invalid speed. Enter a value between 1 and 50.");
            }
        }
    }

    int selectedPattern;
    if (useRandomOrder) {
        
        int attempts = 0;
        do {
            selectedPattern = random(1, PATTERN_COUNT + 1);
            attempts++;
        } while (isPatternRecent(selectedPattern) && attempts < 10); 
    } else {
        
        selectedPattern = (lastPattern % PATTERN_COUNT) + 1;
    }

    Serial.print("Ilumix: ");
    Serial.println(selectedPattern);
    

    
    updateRecentPatterns(selectedPattern);
    lastPattern = selectedPattern;  

    // Run the selected pattern
    switch (selectedPattern) {
        case 1: pattern_01(); break;
        case 2: pattern_02(); break;
        case 3: pattern_03(); break;
        case 4: pattern_04(); break;
        case 5: pattern_05(); break;
        case 6: pattern_06(); break;
        case 7: pattern_07(); break;
        case 8: pattern_08(); break;
        case 9: pattern_09(); break;
        case 10: pattern_10(); break;
        case 11: pattern_11(); break;
        case 12: pattern_12(); break;
        case 13: pattern_13(); break;
        case 14: pattern_14(); break;
        case 15: pattern_15(); break;
        case 16: pattern_16(); break;
        case 17: pattern_17(); break;
        case 18: pattern_18(); break;
        case 19: pattern_19(); break;
        case 20: pattern_20(); break;
        case 21: pattern_21(); break;
        case 22: pattern_22(); break;
        case 23: pattern_23(); break;
        case 24: pattern_24(); break;
        case 25: pattern_25(); break;
        case 26: pattern_26(); break;
        case 27: pattern_27(); break;
        case 28: pattern_28(); break;
        case 29: pattern_29(); break;
        case 30: pattern_30(); break;
        case 31: pattern_31(); break;
        case 32: pattern_32(); break;
        case 33: pattern_33(); break;
        case 34: pattern_34(); break;
        case 35: pattern_35(); break;
        case 36: pattern_36(); break;
        case 37: pattern_37(); break;
        case 38: pattern_38(); break;
        case 39: pattern_39(); break;
        case 40: pattern_40(); break;
        case 41: pattern_41(); break;
        case 42: pattern_42(); break;
        case 43: pattern_43(); break;
        case 44: pattern_44(); break;
        case 45: pattern_45(); break;
        case 46: pattern_46(); break;
        case 47: pattern_47(); break;
        case 48: pattern_48(); break;
        case 49: pattern_49(); break;
        case 50: pattern_50(); break;
        case 51: pattern_51(); break;
        case 52: pattern_52(); break;
        case 53: pattern_53(); break;
        case 54: pattern_54(); break;
        case 55: pattern_55(); break;
        case 56: pattern_56(); break;
        case 57: pattern_57(); break;
        case 58: pattern_58(); break;
        case 59: pattern_59(); break;
        case 60: pattern_60(); break;

    }
    
}

bool isPatternRecent(int pattern) {
    
    for (int i = 0; i < MAX_HISTORY; i++) {
        if (recentPatterns[i] == pattern) {
            return true;
        }
    }
    return false;
}

void updateRecentPatterns(int pattern) {
    
    for (int i = MAX_HISTORY - 1; i > 0; i--) {
        recentPatterns[i] = recentPatterns[i - 1];
    }
    recentPatterns[0] = pattern;  
}



// Helper function to turn relays on/off
void setRelays(bool relaysState[], int numRelays) {
  for (int i = 0; i < numRelays; i++) {
    digitalWrite(relays[i], relaysState[i] ? LOW : HIGH); 
  }
}

// Function for a simple blink pattern
void pattern_blink(int numRelays, int repeatCount, int delayTime) {
  bool relaysState[NUM_RELAYS] = {false}; 
  for (int repeat = 0; repeat < repeatCount; repeat++) {
    for (int i = 0; i < numRelays; i++) {
      relaysState[i] = !relaysState[i];  
    }
    setRelays(relaysState, numRelays);  
    delay(delayTime); 
  }
}

void toggleRelay(int relayIndex, int state) {
    digitalWrite(relays[relayIndex], state);  
}

void turnAllRelaysOff() {
    for (int i = 0; i < NUM_RELAYS; i++) {
        digitalWrite(relays[i], HIGH);  
    }
}

void turnAllRelaysOn() {
    for (int i = 0; i < NUM_RELAYS; i++) {
        digitalWrite(relays[i], LOW);  
    }
}


// Function to randomly toggle two relays
void randomPairToggle(int delayTime) {
    
    int relay1 = random(0, NUM_RELAYS);
    int relay2 = random(0, NUM_RELAYS);

    
    while (relay1 == relay2) {
        relay2 = random(0, NUM_RELAYS);
    }

    // Toggle the selected relays
    toggleRelay(relay1, LOW);  
    toggleRelay(relay2, LOW);  
    delay(delayTime);          
    toggleRelay(relay1, HIGH); 
    toggleRelay(relay2, HIGH); 
}

// Function to randomly toggle a single relay
void randomRelayToggle(int delayTime) {
    
    int relay = random(0, NUM_RELAYS);

    
    toggleRelay(relay, LOW);  
    delay(delayTime);         
    toggleRelay(relay, HIGH); 
}

// Function to blink a relay
void blinkRelay(int index) {
    toggleRelay(index, LOW);  
    delay(100 * speedFactor);  
    toggleRelay(index, HIGH);  
    delay(100 * speedFactor);  
}

void randomActivateRelay(int relayIndex) {
    digitalWrite(relays[relayIndex], LOW);  
    delay(random(50, 200) * speedFactor);   
    digitalWrite(relays[relayIndex], HIGH); 
}

void turnOnAllRelays() {
    for (int i = 0; i < NUM_RELAYS; i++) {
        digitalWrite(relays[i], LOW);  
    }
}

void turnOffAllRelays() {
    for (int i = 0; i < NUM_RELAYS; i++) {
        digitalWrite(relays[i], HIGH); 
    }
}

void blinkRelay(int relayIndex, int blinkTimes) {
    for (int blink = 0; blink < blinkTimes; blink++) {
        digitalWrite(relays[relayIndex], LOW); 
        delay(100 * speedFactor); 
        digitalWrite(relays[relayIndex], HIGH); 
        delay(100 * speedFactor); 
    }
}


// ----------------- PATTERNS ------------------


// Pattern 01: 2 by 2 Chase Forward and Reverse
void pattern_01() {
  for (int repeat = 0; repeat < 5; repeat++) {
    // Chase forward
    for (int i = 0; i < NUM_RELAYS; i += 2) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;  
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
    
    // Chase reverse
    for (int i = NUM_RELAYS - 2; i >= 0; i -= 2) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;  
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}

// Pattern 02: 2 by 2 Chase Inward and Outward
void pattern_02() {
  for (int repeat = 0; repeat < 5; repeat++) {
    // Inward chase
    for (int i = 0; i < NUM_RELAYS / 2; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      relaysState[NUM_RELAYS - 1 - i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }

    // Outward chase
    for (int i = NUM_RELAYS / 2 - 1; i >= 0; i--) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      relaysState[NUM_RELAYS - 1 - i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}

// Pattern 03: 4 by 4 Forward and Backward
void pattern_03() {
  for (int repeat = 0; repeat < 5; repeat++) {
    // Forward 4 by 4
    for (int i = 0; i < NUM_RELAYS / 2; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      relaysState[NUM_RELAYS / 2 + i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
    }

    // Backward 4 by 4
    for (int i = NUM_RELAYS / 2 - 1; i >= 0; i--) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      relaysState[NUM_RELAYS / 2 + i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
    }
  }
}

// Pattern 04: Odd and Even Relay Patterns
void pattern_04() {
  for (int repeat = 0; repeat < 5; repeat++) {
    // First pattern: Even relays on, Odd relays off
    bool relaysState[NUM_RELAYS] = {false};
    for (int i = 0; i < NUM_RELAYS; i++) {
      if (i % 2 == 0) {
        relaysState[i] = true;  // Even relays on
      }
    }
    setRelays(relaysState, NUM_RELAYS);
    delay(200 * speedFactor);

    // Second pattern: Even relays off, Odd relays on
    for (int i = 0; i < NUM_RELAYS; i++) {
      if (i % 2 != 0) {
        relaysState[i] = true;  // Odd relays on
      } else {
        relaysState[i] = false; // Even relays off
      }
    }
    setRelays(relaysState, NUM_RELAYS);
    delay(200 * speedFactor);
  }

  // After the pattern ends, turn off all relays
  for (int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relays[i], HIGH);  // Turn off all relays
  }
}

// Pattern 05: 2 Pins Blink and Move Forward
void pattern_05() {
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < NUM_RELAYS - 1; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      relaysState[i + 1] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      relaysState[i] = false;
      relaysState[i + 1] = false;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}

// Pattern 06: Opposite of the above, with 3 Blinks
void pattern_06() {
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = NUM_RELAYS - 1; i > 0; i--) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      relaysState[i - 1] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      relaysState[i] = false;
      relaysState[i - 1] = false;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}

// Pattern 07: Alternating blink starting with odd relays
void pattern_07() {
  for (int repeat = 0; repeat < 5; repeat++) {
    // Blink odd relays
    for (int blink = 0; blink < 4; blink++) {
      bool relaysState[NUM_RELAYS] = {false};
      for (int i = 0; i < NUM_RELAYS; i++) {
        if (i % 2 != 0) {
          relaysState[i] = true;
        }
      }
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      for (int i = 0; i < NUM_RELAYS; i++) {
        relaysState[i] = false;
      }
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }

    // Blink even relays
    for (int blink = 0; blink < 4; blink++) {
      bool relaysState[NUM_RELAYS] = {false};
      for (int i = 0; i < NUM_RELAYS; i++) {
        if (i % 2 == 0) {
          relaysState[i] = true;
        }
      }
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      for (int i = 0; i < NUM_RELAYS; i++) {
        relaysState[i] = false;
      }
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}

// Pattern 08: Blink specific pairs of relays
void pattern_08() {
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int pair = 0; pair < NUM_RELAYS; pair += 2) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[pair] = true;
      relaysState[pair + 1] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      relaysState[pair] = false;
      relaysState[pair + 1] = false;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}

// Pattern 09: Blink in a wave from left to right (then right to left)
void pattern_09() {
  for (int repeat = 0; repeat < 5; repeat++) {
    // Left to right wave blink
    for (int i = 0; i < NUM_RELAYS; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      relaysState[i] = false;
      setRelays(relaysState, NUM_RELAYS);
    }
    delay(300 * speedFactor); // Pause

    // Right to left wave blink
    for (int i = NUM_RELAYS - 1; i >= 0; i--) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      relaysState[i] = false;
      setRelays(relaysState, NUM_RELAYS);
    }
  }
}



// Pattern 10: Double Blink (4 on, 4 off)
void pattern_10() {
  for (int repeat = 0; repeat < 5; repeat++) {
    bool relaysState[NUM_RELAYS] = {false}; 
    setRelays(relaysState, NUM_RELAYS); 
    delay(200 * speedFactor);  
    for (int i = 0; i < NUM_RELAYS; i++) {
      relaysState[i] = true;  // Turn on all relays
    }
    setRelays(relaysState, NUM_RELAYS);
    delay(200 * speedFactor);  
  }
}

// Pattern 11: Custom sequence blink
void pattern_11() {
  int sequence[] = {0, 2, 1, 3, 2, 4, 3, 5, 4, 6, 5, 7};
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[sequence[i]] = true;  
      setRelays(relaysState, NUM_RELAYS);
      delay(150 * speedFactor);
      relaysState[sequence[i]] = false; 
      setRelays(relaysState, NUM_RELAYS);
    }
  }
}

// Pattern 12: Custom activation order
void pattern_12() {
  int sequence[] = {0, 3, 1, 5, 2, 7, 4, 6};
  for (int repeat = 0; repeat < 6; repeat++) {
    for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[sequence[i]] = true;  
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
      relaysState[sequence[i]] = false; 
      setRelays(relaysState, NUM_RELAYS);
    }
  }
}

// Pattern 13: Sequential blink with delay
void pattern_13() {
  int seq[] = {0, 7, 1, 6, 2, 5, 3, 4};
  for (int repeat = 0; repeat < 2; repeat++) {
    for (int i = 0; i < NUM_RELAYS; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[seq[i]] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(150 * speedFactor);
      relaysState[seq[i]] = false;
      setRelays(relaysState, NUM_RELAYS);
      delay(150 * speedFactor);
    }
  }
}

// Pattern 14: Turn on groups of 4 relays
void pattern_14() {
  int sequence[][4] = {{0, 1, 2, 3}, {2, 3, 4, 5}, {4, 5, 6, 7}};
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
      bool relaysState[NUM_RELAYS] = {false};
      for (int j = 0; j < 4; j++) {
        relaysState[sequence[i][j]] = true;  
      }
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
      for (int j = 0; j < 4; j++) {
        relaysState[sequence[i][j]] = false; 
      }
      setRelays(relaysState, NUM_RELAYS);
    }
  }
}

// Pattern 15: Complex sequence blink
void pattern_15() {
  int sequence[] = {0, 1, 2, 3, 2, 1, 2, 3, 4, 5, 6, 5, 4, 5, 6, 7};
  int seqLength = sizeof(sequence) / sizeof(sequence[0]);
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < seqLength; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[sequence[i]] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
      relaysState[sequence[i]] = false;
      setRelays(relaysState, NUM_RELAYS);
    }
  }
}

// Pattern 16: Sequential blink in a custom order
void pattern_16() {
  int order[] = {3, 4, 2, 5, 1, 6, 0, 7};
  int seqLength = sizeof(order) / sizeof(order[0]);
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < seqLength; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[order[i]] = true;  
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
      relaysState[order[i]] = false; // Turn off the relay
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
    }
  }
}

// Pattern 17: Pairwise relay blink
void pattern_17() {
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int shift = 0; shift < 4; shift++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[shift] = true;
      relaysState[shift + 4] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
      relaysState[shift] = false;
      relaysState[shift + 4] = false;
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
    }
  }
}

// Pattern 18: Zigzag effect
void pattern_18() {
  for (int repeat = 0; repeat < 10; repeat++) {
    bool relaysState[NUM_RELAYS] = {false};
    for (int i = 0; i < NUM_RELAYS; i++) {
      if (i % 2 == 0) {
        relaysState[i] = true;
      }
    }
    setRelays(relaysState, NUM_RELAYS);
    delay(200 * speedFactor);
    for (int i = 0; i < NUM_RELAYS; i++) {
      if (i % 2 != 0) {
        relaysState[i] = true;
      }
    }
    setRelays(relaysState, NUM_RELAYS);
    delay(200 * speedFactor);
    for (int i = 0; i < NUM_RELAYS; i++) {
      relaysState[i] = false;
    }
    setRelays(relaysState, NUM_RELAYS);
  }
}

// Pattern 19: Random blink
void pattern_19() {
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < 8; i++) {
      int randomRelay = random(0, NUM_RELAYS);
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[randomRelay] = true; 
      setRelays(relaysState, NUM_RELAYS);
      delay(200 * speedFactor);
      relaysState[randomRelay] = false; // Turn off the random relay
      setRelays(relaysState, NUM_RELAYS);
    }
  }
}

// Pattern 20: Wave Effect
void pattern_20() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, LOW);
            delay(150 * speedFactor);
            toggleRelay(i, HIGH);
        }
        delay(300 * speedFactor);
    }
}
// Pattern 21: Heartbeat Effect
void pattern_21() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        turnAllRelaysOff();
        delay(100 * speedFactor);
        turnAllRelaysOn();
        delay(100 * speedFactor);
    }
}
// Pattern 22: Alternate Blink
void pattern_22() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, (i % 2 == 0) ? LOW : HIGH);
        }
        delay(250 * speedFactor);
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, (i % 2 == 0) ? HIGH : LOW);
        }
        delay(250 * speedFactor);
    }
    turnAllRelaysOff();
}
// Pattern 23: 
void pattern_23() { 
    
    for (int repeat = 0; repeat < 4; repeat++) {
        for (int i = 1; i <= NUM_RELAYS; i++) {
            for (int j = 0; j < i; j++) toggleRelay(j, LOW);
            for (int j = i; j < NUM_RELAYS; j++) toggleRelay(j, HIGH);
            delay(100 * speedFactor);
            turnAllRelaysOff();
            delay(100 * speedFactor);
        }
        turnAllRelaysOff();
        delay(100 * speedFactor);
    }
}
// Pattern 24: 
void pattern_24() { 
    
    for (int repeat = 0; repeat < 4; repeat++) {
        for (int i = NUM_RELAYS; i >= 1; i--) {
            for (int j = 0; j < i; j++) toggleRelay(j, LOW);
            for (int j = i; j < NUM_RELAYS; j++) toggleRelay(j, HIGH);
            delay(100 * speedFactor);
            turnAllRelaysOff();
            delay(100 * speedFactor);
        }
        turnAllRelaysOff();
        delay(100 * speedFactor);
    }
}
// Pattern 25: 
void pattern_25() { 
    
    for (int repeat = 0; repeat < 4; repeat++) {
        for (int i = 2; i <= NUM_RELAYS; i += 2) {
            for (int j = 0; j < i; j++) toggleRelay(j, LOW);
            for (int j = i; j < NUM_RELAYS; j++) toggleRelay(j, HIGH);
            delay(150 * speedFactor);
            turnAllRelaysOff();
            delay(150 * speedFactor);
        }
        turnAllRelaysOff();
        delay(150 * speedFactor);
    }
}
// Pattern 26: 
void pattern_26() { 
    
    for (int repeat = 0; repeat < 4; repeat++) {
        for (int i = NUM_RELAYS; i >= 2; i -= 2) {
            for (int j = 0; j < i; j++) toggleRelay(j, LOW);
            for (int j = i; j < NUM_RELAYS; j++) toggleRelay(j, HIGH);
            delay(150 * speedFactor);
            turnAllRelaysOff();
            delay(150 * speedFactor);
        }
        turnAllRelaysOff();
        delay(150 * speedFactor);
    }
}
// Pattern 27: 
void pattern_27() { 
    
    for (int repeat = 0; repeat < 4; repeat++) {
        for (int i = 0; i < NUM_RELAYS / 2; i++) {
            toggleRelay(i, LOW);
            toggleRelay(NUM_RELAYS - 1 - i, LOW);
            delay(200 * speedFactor);
            toggleRelay(i, HIGH);
            toggleRelay(NUM_RELAYS - 1 - i, HIGH);
            delay(200 * speedFactor);
        }
        turnAllRelaysOff();
        delay(200 * speedFactor);
    }
}
// Pattern 28: 
void pattern_28() {
    
    int relayPairs[4][2] = {{3, 4}, {2, 5}, {1, 6}, {0, 7}};
    for (int repeat = 0; repeat < 4; repeat++) {
        for (int i = 0; i < 4; i++) {
            toggleRelay(relayPairs[i][0], LOW);
            toggleRelay(relayPairs[i][1], LOW);
            delay(100);
        }
        turnAllRelaysOff();
        delay(100);
    }
}
// Pattern 29: 
void pattern_29() { 
    
    for (int repeat = 0; repeat < 4; repeat++) {
        turnAllRelaysOff();
        delay(200 * speedFactor);
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, LOW);
            delay(200 * speedFactor);
        }
        for (int i = NUM_RELAYS - 1; i >= 0; i--) {
            toggleRelay(i, LOW);
            delay(200 * speedFactor);
        }
    }
}

// Pattern 30: Random Two Pins Blink
void pattern_30() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < 8; i++) {
            randomPairToggle(200 * speedFactor);  
        }
    }
    turnAllRelaysOff();
}
// Pattern 31: Sequential Random Blink
void pattern_31() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, LOW);  
            delay(random(50, 500) * speedFactor);  
            toggleRelay(i, HIGH);  
            delay(random(100, 500) * speedFactor);  
        }
    }
    turnAllRelaysOff();
}
//pattern_32: Ripple Effect
void pattern_32() {
    
    int delayTime = 200 * speedFactor;
    for (int repeat = 0; repeat < 8; repeat++) {
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, LOW);  
            delay(delayTime);
            toggleRelay(i, HIGH);  
            delayTime = max(50, delayTime - 30);  
        }
        delay(500 * speedFactor);  
    }
    turnAllRelaysOff();
}
//pattern_33: Random Relay Flicker
void pattern_33() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < 8; i++) {
            randomRelayToggle(75 * speedFactor);  
        }
    }
    turnAllRelaysOff();
}
//pattern_34: Simultaneous Relay Flicker
void pattern_34() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < 8; i++) {
            randomPairToggle(100 * speedFactor);  
        }
    }
    turnAllRelaysOff();
}
//pattern_35: Simultaneous Relay Flashing with Alternating Pairs
void pattern_35() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < 4; i++) {
            randomPairToggle(100 * speedFactor);  
        }
    }
    turnAllRelaysOff();
}
//pattern_36: Strobe Light Effect with Random Pairings
void pattern_36() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < 6; i++) {
            randomPairToggle(100 * speedFactor);  
        }
    }
    turnAllRelaysOff();
}
//pattern_37: Shifting Off Relays (1 by 1, Left to Right and Right to Left
void pattern_37() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < NUM_RELAYS; i++) {
            for (int j = 0; j < NUM_RELAYS; j++) {
                toggleRelay(j, (j == i) ? HIGH : LOW);  
            }
            delay(200 * speedFactor);
        }

        for (int i = NUM_RELAYS - 1; i >= 0; i--) {
            for (int j = 0; j < NUM_RELAYS; j++) {
                toggleRelay(j, (j == i) ? HIGH : LOW);  
            }
            delay(200 * speedFactor);
        }
    }
    turnAllRelaysOff();
}
//pattern_38: Dual Chase
void pattern_38() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, LOW);  
            delay(100 * speedFactor);
            toggleRelay(i, HIGH);
        }

        for (int i = NUM_RELAYS - 1; i >= 0; i--) {
            toggleRelay(i, LOW);  
            delay(100 * speedFactor);
            toggleRelay(i, HIGH);
        }
    }
}
//pattern_39: Triple Pulse
void pattern_39() {
    
    int groupSize = 3;
    int numCycles = 5;
    int pulseDuration = 100;
    for (int cycle = 0; cycle < numCycles; cycle++) {
        for (int start = 0; start <= NUM_RELAYS - groupSize; start++) {
            for (int i = start; i < start + groupSize; i++) {
                toggleRelay(i, LOW);  
            }
            delay(pulseDuration);
            for (int i = start; i < start + groupSize; i++) {
                toggleRelay(i, HIGH);  
            }
            delay(pulseDuration);
        }

        for (int start = NUM_RELAYS - groupSize; start >= 0; start--) {
            for (int i = start; i < start + groupSize; i++) {
                toggleRelay(i, LOW);  
            }
            delay(pulseDuration);
            for (int i = start; i < start + groupSize; i++) {
                toggleRelay(i, HIGH);  
            }
            delay(pulseDuration);
        }
    }
    turnAllRelaysOff();
}



// 40. Heartbeat Effect
void pattern_40() {
    
    int shortPulse = 100;  
    int longPulse = 300;   
    int pauseDuration = 500;  

    for (int repeat = 0; repeat < 5; repeat++) {
        
        turnAllRelaysOn();
        delay(shortPulse);
        turnAllRelaysOff();
        delay(pauseDuration);

        
        turnAllRelaysOn();
        delay(longPulse);
        turnAllRelaysOff();
        delay(pauseDuration);
    }
}

// 41. Flash & Fade
void pattern_41() {
    
    int flashDuration = 200;  
    int fadeDelay = 100;      

    
    turnAllRelaysOn();
    delay(flashDuration);

    
    for (int i = 0; i < NUM_RELAYS; i++) {
        toggleRelay(i, HIGH);  
        delay(fadeDelay);
    }

    
    turnAllRelaysOff();
}

// 42. Ripple Effect
void pattern_42() {
    
    int rippleSpeed = 150;  
    int center = NUM_RELAYS / 2;  

    for (int repeat = 0; repeat < 5; repeat++) {
        
        for (int i = 0; i <= center; i++) {
            toggleRelay(center - i, LOW);  
            toggleRelay(center + i, LOW);  
            delay(rippleSpeed);
        }
        delay(500);

        // Ripple inwards back towards the center
        for (int i = center; i >= 0; i--) {
            toggleRelay(center - i, HIGH);  
            toggleRelay(center + i, HIGH);  
            delay(rippleSpeed);
        }
        delay(500);
    }
}

// 43. Lightning Strike
void pattern_43() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        
        turnAllRelaysOn();
        delay(50);

        
        turnAllRelaysOff();

        
        for (int i = 0; i < 10; i++) {
            int randomRelay = random(0, NUM_RELAYS);
            toggleRelay(randomRelay, LOW);   
            delay(random(50, 150));
            toggleRelay(randomRelay, HIGH);  
        }

        delay(500);
    }
}

// 44. Pulse & Hold
void pattern_44() {
    
    for (int repeat = 0; repeat < 5; repeat++) {
        
        for (int i = 0; i < 3; i++) {
            turnAllRelaysOn();
            delay(100 * speedFactor);
            turnAllRelaysOff();
            delay(100 * speedFactor);
        }

        
        turnAllRelaysOn();
        delay(800 * speedFactor);

        
        for (int i = 0; i < NUM_RELAYS; i++) {
            toggleRelay(i, HIGH);
            delay(100 * speedFactor);
        }
    }
}

// 45. Chaotic Pulse with Blink Effect
void pattern_45() {
    
    int pulseCount = 40;  

    for (int i = 0; i < pulseCount; i++) {
        int relayIndex = random(0, NUM_RELAYS);
        if (random(0, 2) == 0) {
            toggleRelay(relayIndex, LOW);
        } else {
            toggleRelay(relayIndex, HIGH);
        }

        int delayTime = random(50, 250) * speedFactor;
        delay(delayTime);

        if (random(0, 2) == 0) {
            int jitterDelay = random(100, 200);
            delay(jitterDelay);
        }

        if (random(0, 4) == 0) {
            int blinkRelay = random(0, NUM_RELAYS);
            toggleRelay(blinkRelay, LOW);
            delay(random(50, 100) * speedFactor);
            toggleRelay(blinkRelay, HIGH);
        }
    }

    turnAllRelaysOff();
}

// 46. Rain Effect
void pattern_46() {
    
    int rainCount = 5;

    for (int repeat = 0; repeat < rainCount; repeat++) {
        int relayIndices[NUM_RELAYS];
        for (int i = 0; i < NUM_RELAYS; i++) {
            relayIndices[i] = i;
        }

        
        for (int i = 0; i < NUM_RELAYS; i++) {
            int randIndex = random(i, NUM_RELAYS);
            int temp = relayIndices[i];
            relayIndices[i] = relayIndices[randIndex];
            relayIndices[randIndex] = temp;
        }

        
        for (int i = 0; i < NUM_RELAYS; i++) {
            int relayIndex = relayIndices[i];
            toggleRelay(relayIndex, LOW);
            delay(100 * speedFactor);
            toggleRelay(relayIndex, HIGH);
            delay(100 * speedFactor);

            toggleRelay(relayIndex, LOW);
        }

        delay(500 * speedFactor);

        
        for (int i = NUM_RELAYS - 1; i >= 0; i--) {
            int relayIndex = relayIndices[i];
            for (int blink = 0; blink < 3; blink++) {
                toggleRelay(relayIndex, LOW);
                delay(100 * speedFactor);
                toggleRelay(relayIndex, HIGH);
                delay(100 * speedFactor);
            }

            toggleRelay(relayIndex, HIGH);
        }

        delay(500 * speedFactor);
    }

    turnAllRelaysOff();
}

// 47. Pulse Sync and Reverse
void pattern_47() {
    
    for (int run = 0; run < 3; run++) {
        turnAllRelaysOn();
        delay(500 * speedFactor);

        for (int i = NUM_RELAYS - 1; i >= 0; i--) {
            toggleRelay(i, HIGH);
        }
        delay(500 * speedFactor);

        for (int i = 0; i < NUM_RELAYS; i++) {
            blinkRelay(i);
        }

        delay(500 * speedFactor);
    }
}

// 48. Wave with Flicker
void pattern_48() {
    
    int waveTime = 150; 

    for (int i = 0; i < NUM_RELAYS; i++) {
        toggleRelay(i, LOW);
        delay(waveTime * speedFactor);
        toggleRelay(i, HIGH);
    }
    delay(500);

    
    for (int i = 0; i < 10; i++) {
        int randomRelay = random(0, NUM_RELAYS);
        toggleRelay(randomRelay, LOW);   
        delay(random(50, 150));
        toggleRelay(randomRelay, HIGH);  
    }
}

// 49. Flash and Strobe
void pattern_49() {
    

    int flashCount = 5;
    for (int i = 0; i < flashCount; i++) {
        turnAllRelaysOn();
        delay(100);
        turnAllRelaysOff();
        delay(100);
    }
    
    
    for (int i = 0; i < 10; i++) {
        turnAllRelaysOn();
        delay(50 * speedFactor);
        turnAllRelaysOff();
        delay(50 * speedFactor);
    }
}


//pattern_50: LH to RH, RH to LH, Pair Cross, Reverse Pair Cross
void pattern_50() {
    
    int pairs[4][2] = {
        {0, 7}, {1, 6}, {2, 5}, {3, 4}
    };

    for (int run = 0; run < 5; run++) {
        for (int i = 0; i < NUM_RELAYS; i++) { digitalWrite(relays[i], LOW); delay(100 * speedFactor); }
        turnOffAllRelays();
        delay(200 * speedFactor);
        for (int i = NUM_RELAYS - 1; i >= 0; i--) { digitalWrite(relays[i], LOW); delay(100 * speedFactor); }
        turnOffAllRelays();
        delay(200 * speedFactor);

        for (int i = 0; i < 4; i++) {
            digitalWrite(relays[pairs[i][0]], LOW);
            digitalWrite(relays[pairs[i][1]], LOW);
            delay(100 * speedFactor);
        }
        turnOffAllRelays();
        delay(200 * speedFactor);

        for (int i = 3; i >= 0; i--) {
            digitalWrite(relays[pairs[i][0]], LOW);
            digitalWrite(relays[pairs[i][1]], LOW);
            delay(100 * speedFactor);
        }
        turnOffAllRelays();
        delay(200 * speedFactor);
    }
}

//pattern_51: Random Activation with Dynamic Sequences
void pattern_51() {
    

    for (byte run = 0; run < 3; run++) {
        turnOffAllRelays();
        
        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            byte relayIndex = random(NUM_RELAYS);
            digitalWrite(relays[relayIndex], LOW);  
            delay(random(50, 150) * speedFactor);
        }
        delay(200 * speedFactor);

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            byte relayIndex = random(NUM_RELAYS);
            digitalWrite(relays[relayIndex], HIGH); 
            delay(random(100, 300) * speedFactor);
        }
        delay(200 * speedFactor);

        
        bool relayStatus[NUM_RELAYS];
        for (byte i = 0; i < NUM_RELAYS; i++) relayStatus[i] = false;

        for (byte i = 0; i < NUM_RELAYS; i++) {
            byte relayIndex;
            do {
                relayIndex = random(NUM_RELAYS);
            } while (relayStatus[relayIndex]); 

            relayStatus[relayIndex] = true;
            digitalWrite(relays[relayIndex], HIGH);
            delay(random(70, 100) * speedFactor);
        }
        delay(200 * speedFactor);
    }
}


//pattern_52: Lava Flow
void pattern_52() {
    

    for (byte run = 0; run < 5; run++) {
        
        for (byte i = 0; i < NUM_RELAYS; i++) { 
            digitalWrite(relays[i], LOW); 
            delay(100 * speedFactor); 
        }
        delay(500 * speedFactor);

        
        for (byte i = 0; i < 4; i++) {
            turnOnAllRelays();
            delay(100 * speedFactor);
            turnOffAllRelays();
            delay(100 * speedFactor);
        }

        
        turnOnAllRelays();
        delay(500 * speedFactor);

        
        for (byte i = NUM_RELAYS; i-- > 0;) { 
            digitalWrite(relays[i], HIGH); 
            delay(random(50, 150) * speedFactor); 
        }
        delay(500 * speedFactor);
    }
}

//pattern_53
void pattern_53() {
    

    byte sequence[NUM_RELAYS]; 

    for (byte repeat = 0; repeat < 4; repeat++) {
        
        for (byte i = 0; i < NUM_RELAYS; i++) sequence[i] = i;

        
        for (byte i = NUM_RELAYS - 1; i > 0; i--) {
            byte j = random(i + 1);
            byte temp = sequence[i];
            sequence[i] = sequence[j];
            sequence[j] = temp;
        }

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[sequence[i]], LOW);
            delay(200 * speedFactor);
            digitalWrite(relays[sequence[i]], HIGH);
        }
    }
}

//pattern_54: Starry Night
void pattern_54() {
    

    for (byte run = 0; run < 5; run++) {
        turnOffAllRelays();

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[random(NUM_RELAYS)], LOW);
        }
        delay(500 * speedFactor);

        
        for (byte i = 0; i < 3; i++) {
            turnOnAllRelays();
            delay(100 * speedFactor);
            turnOffAllRelays();
            delay(100 * speedFactor);
        }

        
        for (byte i = NUM_RELAYS; i-- > 0;) {
            digitalWrite(relays[i], LOW);
            delay(100 * speedFactor);
            digitalWrite(relays[i], HIGH);
        }
        delay(500 * speedFactor);
    }
}

//pattern_55: Advanced Snake Pattern
void pattern_55() {
    

    for (byte run = 0; run < 5; run++) {
        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[i], LOW);
            delay((50 + (i * 10)) * speedFactor);
        }
        delay(500 * speedFactor);

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            if (random(2)) {  
                for (byte j = 0; j < random(1, 4); j++) {
                    digitalWrite(relays[i], HIGH);
                    delay(100 * speedFactor);
                    digitalWrite(relays[i], LOW);
                    delay(100 * speedFactor);
                }
            }
        }
        delay(500 * speedFactor);

        
        for (byte i = NUM_RELAYS; i-- > 0;) {
            digitalWrite(relays[i], HIGH);
            delay((50 + ((NUM_RELAYS - i) * 10)) * speedFactor);
            if (!(i & 1) && i > 1) {  
                delay(50 * speedFactor);
                digitalWrite(relays[i - 1], HIGH);
            }
        }
        delay(500 * speedFactor);

        
        turnOffAllRelays();
        delay(500 * speedFactor);
    }
}
//pattern_56: Blinding Flash
void pattern_56() {
    

    for (byte run = 0; run < 5; run++) {
        turnOnAllRelays();
        delay(300 * speedFactor);

        
        for (byte blink = 0; blink < 2; blink++) {
            turnOffAllRelays();
            delay(100 * speedFactor);
            turnOnAllRelays();
            delay(100 * speedFactor);
        }
        delay(500 * speedFactor);

        
        for (byte i = NUM_RELAYS; i-- > 0;) {
            for (byte blink = 0; blink < 2; blink++) {
                digitalWrite(relays[i], LOW);
                delay(50 * speedFactor);
                digitalWrite(relays[i], HIGH);
                delay(50 * speedFactor);
            }
            delay(100 * speedFactor);
        }
        delay(500 * speedFactor);
    }
}

//pattern_57: Exploding Lights
void pattern_57() {
    

    for (byte run = 0; run < 5; run++) {
        byte sequence[NUM_RELAYS];
        
        
        for (byte i = 0; i < NUM_RELAYS; i++) sequence[i] = i;
        for (byte i = NUM_RELAYS - 1; i > 0; i--) {
            byte j = random(0, i + 1);
            byte temp = sequence[i];
            sequence[i] = sequence[j];
            sequence[j] = temp;
        }

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[sequence[i]], LOW);
            delay(random(50, 200) * speedFactor);
            digitalWrite(relays[sequence[i]], HIGH);
        }

        delay(500 * speedFactor);
    }
}

//pattern_58: Glitch Pulse
void pattern_58() {
    

    for (byte run = 0; run < 5; run++) {
        for (byte i = 0; i < NUM_RELAYS; i++) {
            randomActivateRelay(random(0, NUM_RELAYS));  
        }
        delay(500 * speedFactor);
        turnOffAllRelays();
        delay(500 * speedFactor);
    }
}

//pattern_59: Spin Around 2.0
void pattern_59() {
    

    for (byte run = 0; run < 5; run++) {
        byte direction = 1; 

        for (byte cycle = 0; cycle < 3; cycle++) {  
            byte delayTime = 150;  
            
            for (byte i = 0; i < NUM_RELAYS; i++) {
                byte index = (direction == 1) ? i : (NUM_RELAYS - 1 - i);

                
                digitalWrite(relays[index], LOW);
                if (i > 1) digitalWrite(relays[index - direction], LOW); 
                
                delay(delayTime * speedFactor);
                
                
                if (delayTime > 50) delayTime -= 10;

                
                if (random(0, 10) > 7) {  
                    digitalWrite(relays[index], HIGH);
                    delay(50 * speedFactor);
                    digitalWrite(relays[index], LOW);
                }

                
                if (i > 2) digitalWrite(relays[index - 2 * direction], HIGH);
            }

            delay(300 * speedFactor);

            
            if (random(0, 5) > 2) {
                direction *= -1;
            }

            delay(200 * speedFactor);
        }

        
        for (byte blink = 0; blink < 4; blink++) {
            for (byte i = 0; i < NUM_RELAYS; i++) {
                digitalWrite(relays[i], LOW);
            }
            delay(100 * speedFactor);
            for (byte i = 0; i < NUM_RELAYS; i++) {
                digitalWrite(relays[i], HIGH);
            }
            delay(100 * speedFactor);
        }

        delay(500 * speedFactor);
    }
}




//pattern_60: Galactic Rift
void pattern_60() {
    

    for (byte run = 0; run < 3; run++) {  

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[i], LOW);  
            delay((i % 2 == 0) ? 100 : 50 * speedFactor);  
        }

        delay(500 * speedFactor);  

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[i], (random(0, 10) > 3) ? LOW : HIGH);  
            delay(random(50, 150) * speedFactor);
        }

        delay(500 * speedFactor);  

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            if (random(0, 5) == 0) {  
                digitalWrite(relays[i], LOW);  
                delay(random(50, 100) * speedFactor);
                digitalWrite(relays[i], HIGH); 
            }
        }

        delay(500 * speedFactor);  

        
        for (byte i = 0; i < 10; i++) {
            for (byte j = 0; j < NUM_RELAYS; j++) {
                digitalWrite(relays[j], (random(0, 3) == 0) ? LOW : HIGH);  
            }
            delay(random(50, 100) * speedFactor);  
        }

        delay(500 * speedFactor);  

        
        for (byte i = 0; i < NUM_RELAYS / 2; i++) {
            digitalWrite(relays[i], LOW);  
            digitalWrite(relays[NUM_RELAYS - 1 - i], LOW);  
            delay(100 * speedFactor);  
        }

        delay(300 * speedFactor);  

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[i], (random(0, 2) == 0) ? LOW : HIGH);  
            delay(random(100, 300) * speedFactor);
        }

        delay(500 * speedFactor);  

        
        for (byte i = 0; i < NUM_RELAYS; i++) {
            digitalWrite(relays[i], (random(0, 3) == 0) ? HIGH : LOW);  
            delay(random(50, 100) * speedFactor);
        }

        delay(300 * speedFactor);  
    }

    
    for (byte i = 0; i < NUM_RELAYS; i++) {
        digitalWrite(relays[i], HIGH);  
    }
}


void activateRelay(int relayIndex, int delayTime) {
    digitalWrite(relays[relayIndex], LOW);  
    delay(delayTime * speedFactor);          
    digitalWrite(relays[relayIndex], HIGH); 
}

