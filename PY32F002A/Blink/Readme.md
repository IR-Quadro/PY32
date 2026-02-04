# Session 01: System Time Base (SysTick)
In this session, we implement a precise Time Base using the ARM® Cortex®-M0+ SysTick timer. This is the first step toward creating a "Blink" project, as it provides the necessary timing for periodic tasks.



## 📝 Overview
Instead of using inaccurate software loops, we utilize the internal 24-bit SysTick counter. This allows the MCU to increment a global counter every 1 millisecond, providing a reliable reference for the ```delay_ms()``` function.



## 🛠️ Implementation Details

**1. SysTick Configuration**

The ```SysTick_Config()``` function (from the CMSIS header) sets up the timer's reload value and enables the interrupt.

- **Formula:** ```SystemCoreClock / 1000```
- **Result:** The ```SysTick_Handler``` is triggered exactly every 1ms (at 1kHz).
 
<br>

**2. The Tick Counter**

We use a ```volatile``` variable to ensure the compiler doesn't optimize out the memory access, as this variable is modified inside an Interrupt Service Routine (ISR).

```C
volatile uint32_t msTick = 0;
```

<br>

**3. The Delay Logic**

The ```delay_ms``` function implements a blocking delay. It captures the current state of ```msTick``` and loops until the target duration has elapsed.


## 🔍 Code Structure
- ```main.c```: Contains the system initialization and the main loop.

- ```SysTick_Handler()```: The interrupt routine that keeps track of time.

- ```delay_ms()```: The user-facing function for timing control.



## 🎯 Next Step
In the next session, we will initialize the **RCC (Reset and Clock Control)** for GPIO peripherals and configure a pin as an **Output** to finally see the LED blink using the delay function we built today.