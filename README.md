# ILUMIX ✨ - A Dynamic Lighting System for Arduino 💡

## 🚀 **Project Overview**

**ILUMIX** is a dynamic lighting system designed to control an **8-channel relay module** connected to an **Arduino Uno** or compatible boards (such as ESP), offering a wide variety of lighting patterns! 🎇 It allows users to control up to **60 unique lighting patterns**, adjust **speed**, and switch between **random** and **sequential modes** via the **Serial Monitor**.


## Switch between patterns like a DJ 🎶 or customize the speed for the perfect vibe!

### 🔥 Features:
- **60 Dynamic Lighting Patterns** for endless creativity!
- **Speed Control**: Adjust speed from **1 (fastest) to 50 (slowest)** 🏃️🌼.
- **Mode Selection**: Choose between **random** or **sequential** execution 🔀➡️.
- **Real-time control** via **Serial Monitor** 🖥️.
- **Plug-and-Play** setup with Arduino & relays 🛠️.

### 🙋‍♂️ Author:
- **T.G Damika Akalanka** (Connect on [GitHub](https://github.com/Damika3002))

---

## 🛠️ Requirements

### 🔧 Hardware:
- **Arduino Uno** or Higher board 🔩 
- **8-channel relay module** 🛠️
- Jumper wires, **breadboard** (optional)
- External power supply for relays (if needed) ⚡

### 💻 Software:
- **Arduino IDE** (latest version)
- USB cable for programming the Arduino 🌐

---

## 💽 Installation

### 1. **Hardware Setup**:
1. Connect the **8-channel relay module** to **Arduino Uno**. Use the following pin mapping:
   - **Relay pins**: D2 to D9 on Arduino.
2. Power the relay module (use an external power supply if needed).
3. Upload the ILUMIX code via Arduino IDE.

### 2. **Upload the Code**:
1. Open the **ILUMIX** sketch in **Arduino IDE**.
2. Select the correct **board** and **port** from the **Tools** menu.
3. Click **Upload**. 🌟

---

## 🖥️ Using ILUMIX

### 🔍 Serial Monitor Interface

1. **Speed Adjustment**:
   - Enter a number between **1 and 50** to set the speed. For example:
     - **1** = fastest 🚀
     - **50** = slowest 🐢
2. **Pattern Mode Toggle**:
   - Enter **`r`** in the Serial Monitor to switch between **random** and **sequential** pattern modes.

### 💁 How to Use the Serial Monitor:
1. Open the **Serial Monitor** in the Arduino IDE.
2. Set the baud rate to **9600**.
3. Type:
   - **`r`** to toggle between **random** and **sequential** patterns.
   - Any **number (1-50)** to adjust speed.

#### Example Serial Monitor Output:
```

Lighting system initialized.
    
Date Created: 2025/03/29 🗓️
🌍 Greetings, Arduino Community! 👋
Every project is a step towards something greater. Let's keep pushing the boundaries of what's possible! 💪


    ██╗██╗     ██╗     ██╗   ██╗███╗   ███╗██╗██╗  ██╗
    ██║██║     ██║     ██║   ██║████╗ ████║██║╚██╗██╔╝
    ██║██║     ██║     ██║   ██║██╔████╔██║██║ ╚███╔╝ 
    ██║██║     ██║     ██║   ██║██║╚██╔╝██║██║ ██╔██╗ 
    ██║███████╗███████╗╚██████╔╝██║ ╚═╝ ██║██║██╔╝ ██╗
    ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═╝

 By Damika Akalanka 😊
Feel free to explore, modify, and share your improvements!
```
![Preview](https://github.com/Damika3002/ILUMIX/blob/main/images/Screenshot%202025-03-30%20013539.png?raw=true)


---

### 💡 Customizing the Code
#### ✍️ Defining Pins:
To define the pins for each relay, simply modify the relays[] array at the top of your code:

```cpp
Copy

int relays[] = {2, 3, 4, 5, 6, 7, 8, 9}; 
// Customize pin numbers as needed
```  
<br>
    


#### 🔄 Choose Your Patterns:
To enable or disable a specific pattern, you can comment/uncomment the corresponding switch case in the code. For example, to enable Pattern 01, you would uncomment it in the switch statement like this:

```cpp
Copy

    switch (selectedPattern) {
             case 1: pattern_01(); break;
            // case 2: pattern_02(); break;
            // case 3: pattern_03(); break;
            // ...
}
```

---
<br>

## 🌟 Lighting Patterns

There are **60 unique lighting patterns** 🎉, ranging from simple blinks to complex effects! The system selects a pattern based on the **mode**:

- **Random Mode**: Selects a pattern randomly 🎲.
- **Sequential Mode**: Runs patterns in order (1 → 2 → 3 ...).

### 🛡️ Example Pattern: **Chase Forward**
```cpp
void pattern_01() {
  for (int repeat = 0; repeat < 5; repeat++) {
    for (int i = 0; i < NUM_RELAYS; i++) {
      bool relaysState[NUM_RELAYS] = {false};
      relaysState[i] = true;
      setRelays(relaysState, NUM_RELAYS);
      delay(100 * speedFactor);
    }
  }
}
```

---

## 🧶 Helper Functions

### 1. **SetRelays()** - Set relay states dynamically
```cpp
void setRelays(bool relaysState[], int numRelays) {
  for (int i = 0; i < numRelays; i++) {
    digitalWrite(relays[i], relaysState[i] ? LOW : HIGH);
  }
}
```

#### 📌 Function Purpose:
The **setRelays()** function allows dynamic control over multiple relays by setting their **ON/OFF** states based on an input array. It simplifies relay management and helps in creating complex lighting patterns.

#### ⚙️ How It Works:
Iterate Through Each Relay: The function loops through all available relays.

Check Relay State: The relaysState[] array stores the desired ON/OFF state for each relay.

Set Relay Output:
LOW (ON) → Activates the relay (because the relays are active LOW).

HIGH (OFF) → Deactivates the relay.

---



### 2. **Pattern_blink()** - Blinking effect
```cpp
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
```
#### 📌 Function Purpose:
This function creates a blinking effect by toggling the state of multiple relays simultaneously.

#### ⚙️ How It Works:
Initialize Relay States: The relaysState[] array stores the ON/OFF state of all relays.

Repeat the Blink Effect: The loop runs for the specified repeatCount.

Toggle Relays: Each relay switches between ON and OFF.
Apply the New States: Calls setRelays() to update the relay outputs.

Pause Before Next Toggle: Uses delay(delayTime) to control the blink speed.

---
### 3. **ToggleRelay()** - Toggle a specific relay

<br>

```cpp
void toggleRelay(int relayIndex, int state) {
  digitalWrite(relays[relayIndex], state);
}
```

#### 📌 Function Purpose:
Allows direct control of an individual relay, setting it to either ON (LOW) or OFF (HIGH).

#### ⚙️ How It Works:
Accepts relayIndex (which relay to toggle) and state (ON/OFF).

Uses digitalWrite() to update the relay’s state.


---
### 4. **turnAllRelaysOn() & turnAllRelaysOff()**
```cpp
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
```
#### 📌 Function Purpose:
Quickly turn all relays ON or OFF at once.

#### ⚙️ How It Works:
turnAllRelaysOff(): Iterates through all relays and sets them to HIGH (OFF).

turnAllRelaysOn(): Iterates through all relays and sets them to LOW (ON).

---
### 5. **randomPairToggle()** - Random relay pair toggle
```cpp
void randomPairToggle(int delayTime) {
  int relay1 = random(0, NUM_RELAYS);
  int relay2 = random(0, NUM_RELAYS);

  while (relay1 == relay2) {
    relay2 = random(0, NUM_RELAYS);
  }

  toggleRelay(relay1, LOW);
  toggleRelay(relay2, LOW);
  delay(delayTime);
  toggleRelay(relay1, HIGH);
  toggleRelay(relay2, HIGH);
}
```
#### 📌 Function Purpose:
Randomly selects two different relays, turns them ON, waits, then turns them OFF.

#### ⚙️ How It Works:
Select Two Random Relays: Generates relay1 and relay2.

Ensure They Are Different: If both relays are the same, picks another.

Activate the Relays: Turns both ON (LOW).

Wait for Delay: Keeps them ON for delayTime milliseconds.

Deactivate the Relays: Turns both OFF (HIGH).

---

## 🎥 Troubleshooting
- **Unknown symbols in Serial Monitor?** Set baud rate to **9600**.
- **Relays flickering?** Check power connections and external supply.
- **Patterns not changing?** Ensure Serial Monitor input is correct.

---
## 🤗 Example Images


### Image 1
![First Example Image](https://github.com/Damika3002/ILUMIX/blob/main/images/Screenshot%202025-03-30%20013722.png?raw=true)

### GIF Example
![Project Animation GIF](https://github.com/Damika3002/ILUMIX/blob/main/images/playback01%20(1).gif?raw=true)

### Image 2
![Second Example Image](https://github.com/Damika3002/ILUMIX/blob/main/images/Screenshot%202025-03-30%20013635.png?raw=true)

### GIF Example
![Project Animation GIF](https://github.com/Damika3002/ILUMIX/blob/main/images/playback01%20(3).gif)


---

## 👋 Attribution
If you use or share this list, please include proper attribution by linking back to this repository and crediting the original author:

> Created by [T.G Damika Akalanka](https://github.com/Damika3002)  
> Original source: [ILUMIX](https://github.com/Damika3002/ILUMIX/tree/main)

For more details, see the [LICENSE](https://github.com/Damika3002/ILUMIX/blob/main/LICENSE) file.

---

## 👋 About Me
You can find more of my projects and contributions on my GitHub profile:  
👉 [Damika3002 on GitHub](https://github.com/Damika3002)

---

## ☕ Support My Work
If you found this list useful and would like to support my efforts, you can buy me a coffee! Every contribution helps me maintain and improve resources like this one.  
👉 [Buy Me a Coffee](https://buymeacoffee.com/akalanka3002)  

Thank you for visiting, and happy coding! 🌟  

---
## 💌 Contact
For support, reach out via **GitHub @Damika3002** or open an **Issue**.

Happy building and experimenting! ✨💡
