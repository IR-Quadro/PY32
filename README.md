# PY32F002Axx Microcontroller Examples

A collection of low-level, register-based C projects for the Puya Semiconductor PY32F002Axx series. This repository focuses on pure hardware interaction without the abstraction of HAL or LL libraries, making it an ideal resource for educational purposes and performance-critical applications.


## 🚀 Key Features of PY32F002Axx
The PY32F002A is an ultra-affordable, high-performance 32-bit ARM® Cortex®-M0+ MCU.

- Core: ARM® Cortex®-M0+ up to 48 MHz.

- Memory: 20 KB Flash / 3 KB SRAM.

- Voltage: 1.7V to 5.5V (Wide range).

- **Peripherals:**
    - 12-bit SAR ADC.
    - Timers: 1x Advanced Control (TIM1), 1x General Purpose (TIM16), 1x -   Low-power (LPTIM).
    - Comm: USART, SPI, I2C.
    - Safety: Watchdog (IWDG), CRC engine, Clock Security System (CSS).
   
<br>

## 📁 Repository Structure
Projects are organized by MCU series and peripheral functionality:


```

 Example
   ├── PY32F002A
   │   ├── GPIO_Input_Output        # LED Control via Button
   │   ├── ...                      # Coming soon
   │   ├── ...                      # Coming soon
   │   ├── ...                      # Coming soon
   │   └── ...                      # Coming soon
   │
   └───────────────────────────────────────────────────────
   |             👇 Maybe later / Planned 👇
   └───────────────────────────────────────────────────────
   ├── PY32Fxxx
   └── PY32Fxxx
       
```

## 🛠️ Getting Started
**Prerequisites**
- **IDE:** Keil µVision 5

- **Compiler:** ARMClang (Arm Compiler 6).

- **Hardware:** PY32F002Axx development board + USB-to-TTL converter or SWD Debugger (Daplink).


### How to Build

1. Clone the repository:

    ``` bash
    git clone https://github.com/IR-Quadro/PY32.git
    ```

2. Open the ```.uvprojx``` file in the desired project folder.
3. Press F7 to compile.



### Flashing the Firmware 

1. **SWD:** Use Daplink directly via Keil.

2. **UART Bootloader:** Use the puyaisp Python tool to flash via a USB-to-TTL converter.


    ``` bash
    pip install puyaisp
    
    puyaisp -f your_firmware.bin    
    ```
    
    *Note: Ensure BOOT0 is pulled High to enter bootloader mode.*
    
<br>

## 📚 Resources & Community

For detailed step-by-step tutorials on setting up the environment, advanced flashing techniques, and video demonstrations, visit our Telegram channel

[📢 Join our Telegram Channel](https://t.me/EleQuo)
 
<br>

**Official Documentation**

- [Reference Manual](https://download.py32.org/ReferenceManual/en/PY32F002A%20Reference%20manual%20v1.0_EN.pdf) 
- [Datasheet](https://www.puyasemi.com/download_path/%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C/MCU%20%E5%BE%AE%E5%A4%84%E7%90%86%E5%99%A8/PY32F002A_Datasheet_V0.2.pdf)

## 🧑‍💻 Author
Abolfazl Resalati Electronics student and embedded systems enthusiast focused on bare-metal development.




