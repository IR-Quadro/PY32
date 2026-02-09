# Session 01: LED Blink (Register-Based)
This project demonstrates the complete process of blinking an LED on the PY32F002A using bare-metal register access. It combines the SysTick timer for precise delays and GPIO configuration for hardware control.

## 📝 Overview
To blink an LED without using high-level libraries (HAL/LL), we must manually communicate with the ARM® Cortex®-M0+ core and the MCU's peripheral bus. This example targets PA2 (Port A, Pin 2).


### The Three-Step Hardware Process:
1. **Clock Gating:** Enable the power for GPIO Port A via the **RCC** (Reset and Clock Control).
2. **Pin Configuration:** Set the pin mode, output type, and speed via **GPIO Registers**.
3. **Data Control:** Manipulate the pin state using the **BSRR** (Bit Set/Reset Register).


## 🛠️ Register Breakdown
**1. Enabling the Clock** (```RCC->IOPENR```)

In ARM microcontrollers, peripherals are disabled by default to save power. We must enable the clock for Port A:
``` C
RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
```

**2. GPIO Configuration**
We configure **PA2** by modifying the following registers:

- **MODER (Mode Register):** Set to ```01``` for General Purpose Output.

- **OTYPER (Output Type):** Set to ```0``` for Push-Pull (standard for LEDs).

- **OSPEEDR (Speed Register):** Set to ```01``` for Low Speed to reduce EMI/noise.


**3. Bit Manipulation (```GPIOA->BSRR```)**

Instead of using the ```ODR``` (Output Data Register), we use the BSRR (Bit Set/Reset Register).

- **Atomic Access:** BSRR allows you to set or reset a pin in a single instruction without affecting other pins on the same port, making it faster and safer than read-modify-write operations.

```C
GPIOA->BSRR = GPIO_BSRR_BS2; // Set PA2 High
GPIOA->BSRR = GPIO_BSRR_BR2; // Reset PA2 Low
```


## 🚀 Final Logic
The ```while(1)``` loop now performs the following:

1. Set PA2 High (LED ON).
2. Wait 500ms using the SysTick-based ```delay_ms```.
3. Set PA2 Low (LED OFF).
4. Wait 500ms.

