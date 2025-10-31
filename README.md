# PY32F002Axx Microcontroller Repository

This repository provides a collection of low-level, register-based programming examples for the **PY32F002Axx** series microcontrollers from Puya Semiconductor. These examples demonstrate core functionality using pure C code, without relying on HAL libraries or code generators like CubeMX. The focus is on educational purposes, enabling direct hardware interaction for embedded systems development.

The PY32F002Axx is a high-performance, 32-bit ARM® Cortex®-M0+ based MCU designed for cost-sensitive applications requiring low power and wide voltage operation. It supports up to 48 MHz operation, integrated Flash and SRAM, and a rich set of peripherals for general-purpose embedded tasks.

---

## 🔍 Microcontroller Overview

### Key Specifications
- **Core**: ARM® Cortex®-M0+ processor, up to 48 MHz maximum frequency (24 MHz standard, scalable with voltage).
- **Operating Voltage**: 1.7 V to 5.5 V (wide range for battery-powered and industrial applications).
- **Temperature Range**: -40°C to +85°C (industrial grade).
- **Package Options**: TSSOP20, SOP16 (compact form factors for space-constrained designs).
- **Power Consumption**: Ultra-low power modes including Sleep, Stop, and Standby, with dynamic voltage scaling for optimized performance vs. efficiency.

### Memory Organization
| Component       | Size          | Details |
|-----------------|---------------|---------|
| **Flash Memory** | Up to 20 KB  | Main program Flash (128-byte pages, 4 KB sectors); supports read/write/erase protection (RDP levels 0/1, WRP at 4 KB granularity); includes 2 KB system memory and 2.7 KB information block (UID, option bytes, factory config). |
| **SRAM**        | Up to 3 KB   | Data RAM with byte/half-word/word access; configurable retention in Stop mode (0.9V/1.0V/1.2V). |
| **Address Space**| 4 GB linear | Little Endian; SRAM/Flash remappable to 0x0000 0000 via MEM_MODE. |

### Main Features
- **Low-Power Management**: Sleep/Stop/Standby modes with interrupt/event wakeups; integrated voltage regulator (main: 1.2V Run, low-power: 1.0V/1.2V Stop); power monitoring (POR/PDR/BOR with configurable thresholds 1.6–3.2V).
- **Debug Support**: SW-DP interface; Breakpoint Unit (4 registers); Data Watchpoint and Trace (2 watchpoints, PC sampling); NVIC with 32 maskable interrupts (4 priority levels).
- **Boot Options**: Hardware (BOOT0 pin) or software boot; Flash read protection and secure key storage.
- **Clock System**: 
  - Sources: HSI (4/8/16/22.12/24 MHz, trimmable), HSE (4–24 MHz), LSI (32/32.768 kHz).
  - SYSCLK up to 48 MHz; prescalers for HCLK (1–512) and PCLK (1–16); Clock Security System (CSS); MCO output for external clocking.
- **Reset Sources**: POR/PDR/BOR, NRST pin (20 µs filter), IWDG, software, option byte launch.

### Peripherals (High-Level)
The PY32F002Axx integrates essential peripherals for compact designs:
- **GPIO**: Up to 3 ports (A, B, F) with alternate functions, interrupts, and events.
- **Analog**: 12-bit SAR ADC (10 external + 2 internal channels, 1.0 µs conversion time); 2 comparators (COMP1/COMP2) with hysteresis and low-power operation.
- **Timers**: Advanced-control TIM1 (16-bit), general-purpose TIM16 (16-bit), low-power LPTIM (for Stop/Standby wakeups).
- **Communication**: USART1 (up to 4.5 Mbit/s), SPI1, I²C (up to 400 kHz).
- **System**: RCC (clock control), PWR (power management), IWDG (watchdog), CRC (data integrity), SYSCFG (configuration), EXTI (external interrupts), DBGMCU (debug).

For detailed peripheral usage, refer to individual project examples in subdirectories.

---

## 🛠️ Requirements

### Software
- **IDE**: Keil µVision 5 or later (recommended for ARM Cortex-M development).
- **Compiler**: ARMClang v6.21 or compatible (supports CMSIS-style register access).

### Hardware
- **Development Board**: PY32F002Axx-based board (e.g., Puya eval kit or custom breakout).
- **Debug/Programming Tool**: ST-Link, J-Link, or equivalent SWD debugger for flashing and debugging.
- **Optional**: USB-to-Serial adapter for communication testing (e.g., CP2102 or FT232R).

Ensure your setup supports 1.7–5.5 V operation and provides stable power (VDD/VSS).

---

## 📚 References
- [PY32F002A Reference Manual (v1.0)](https://download.py32.org/ReferenceManual/en/PY32F002A%20Reference%20manual%20v1.0_EN.pdf) – Detailed architecture, registers, and programming model.
- [PY32F002A Datasheet (v0.2)](https://www.puyasemi.com/download_path/%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C/MCU%20%E5%BE%AE%E5%A4%84%E7%90%86%E5%99%A8/PY32F002A_Datasheet_V0.2.pdf) – Pinout, electrical characteristics, and ordering info.
- Official Product Page: [PY32F002A Series on OpenPuya](https://py32.org/en/mcu/PY32F002Axx)

---

## 🔨 General Build & Flash Instructions
1. Open the project file (`.uvprojx`) in Keil µVision 5.
2. Navigate to **Project → Options for Target…**:
   - In the **Linker** tab, enable **"Use Memory Layout from Target Dialog"** to match the PY32F002Axx memory map.
3. Build the project (F7 or **Project → Build Target**).
4. Flash via debugger: Connect your SWD tool, select the target device, and program the generated `.hex` or `.bin` file.

For CMSIS device headers, include the Puya-provided pack (download from py32.org if needed).

---

## 📥 Cloning the Repository
To get a copy of the project on your computer, follow these steps:

- Open the folder where you want to save the project in **File Explorer**.  
- **Right-click** inside the folder and choose **“Open Git Bash here”** to open Git Bash in that location.

![Open Git Bash](Images/Open-Git-bash-here.png)

> [!NOTE] 
> If you do not see the "Open Git Bash here" option, it means that Git is not installed on your system.  
> You can download and install Git from [this link](https://git-scm.com/downloads).  

-  Once **Git Bash** is open, run the following command to clone the repository:

```bash
git clone https://github.com/IR-Quadro/PY32.git
```
- You can copy the above command by either:
- Clicking on the **Copy** button on the right of the command.
- Or select the command text manually and press **Ctrl + C** to copy.
- To paste the command into your **Git Bash** terminal, use **Shift + Insert**.

![Clone the Repository](Images/Clone-URL.png)

- Then, press Enter to start the cloning operation and wait for the success message to appear.

![Open the Library File](Images/Clone.png)

This will download the entire repository, including all example projects and shared resources.


## 🧑‍💻 Author

**Abolfazl Resalati**
Electronics student and embedded systems enthusiast.
All examples are written in C for educational purposes, emphasizing register-level access to the PY32F002Axx hardware.