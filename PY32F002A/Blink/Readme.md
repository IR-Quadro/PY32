# Session 01: GPIO Fundamentals (Blink & Input)

This project demonstrates the complete process of interfacing with GPIOs on the PY32F002A using bare-metal register access. It combines Output (Blinking an LED) and Input (Reading a tactile switch) into a single interactive application.

## 📝 Overview

To interact with hardware without using high-level libraries (HAL/LL), we communicate directly with the MCU's peripheral bus. This example uses:

- **Output:** PA2 (Connected to an LED).
- **Input:** PB0 (Connected to a Button with an internal Pull-up).

**The Hardware Workflow:**

1.  **Clock Gating:** Enable the peripheral clock for Port A and Port B via the RCC (Reset and Clock Control).
2.  **Pin Configuration:** Define modes (Input/Output), output types, and pull-up/pull-down resistors.
3.  **Data Interaction:** Use BSRR for atomic output control and IDR for reading input states.

## 🛠️ Register Breakdown

### 1. Enabling the Clock (`RCC->IOPENR`)
Peripherals are disabled by default to save power. We must enable the clock for both ports before accessing their registers.

### 2. Output Configuration (PA2)
We configure PA2 as a standard output pin:
- **MODER:** Set to `01` (General Purpose Output).
- **OTYPER:** Set to `0` (Push-Pull).
- **OSPEEDR:** Set to `01` (Low Speed) to minimize power consumption and EMI.

### 3. Input Configuration (PB0)
We configure PB0 to detect a button press:
- **MODER:** Set to `00` (Input Mode).
- **PUPDR:** Set to `01` (Pull-up). This ensures the pin reads High when the button is open and Low when the button is pressed (connecting it to GND).

### 4. Reading & Writing Data
- **Writing (`BSRR`):** The Bit Set/Reset Register allows atomic bit manipulation. Writing to the `BSx` bits sets the pin, while `BRx` resets it, without needing a read-modify-write cycle.
- **Reading (`IDR`):** The Input Data Register contains the current logic level of all pins on the port. We use a bitwise `&` to isolate the state of a specific pin.

## 🚀 The Final Logic

The application logic inside the `while(1)` loop follows this sequence:

1.  **Poll the Input:** Check if PB0 is Low (Button Pressed).
2.  **Process/Output:** If pressed, toggle the LED on PA2 using `BSRR` and a 50ms `delay_ms`.
3.  **Idle:** If not pressed, the LED remains in its last state (or can be forced off).
