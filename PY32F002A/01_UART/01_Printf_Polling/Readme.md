# Session 02: UART | 01_Printf_Polling

This project is part of the **UART series** and demonstrates how to set up the **Universal Synchronous Asynchronous Receiver Transmitter (USART)** on the **PY32F002A** specifically for data transmission. It focuses on redirecting the standard C `printf` function to UART for real-time system monitoring.

---

## 📝 Overview

In our project hierarchy, this module falls under `UART/01_Printf_Polling`. It serves as the foundation for serial communication, enabling the MCU to "speak" to the outside world using polling-based transmission.

* **Peripheral:** USART1
* **Sub-Module:** 01_Printf_Polling (Transmit Only)
* **TX Pin:** PA2 (Configured as Alternate Function AF1)
* **Mode:** Polled Hardware Flags
* **Feature:** `printf` redirection using `fputc`

### The Hardware Workflow
1.  **Clock Enabling:** Activate clocks for `GPIOA` (for the pins) and `USART1` (for the logic).
2.  **Pin Multiplexing:** Change PA2 from a standard GPIO to its **Alternate Function** (UART_TX).
3.  **Baud Rate Calculation:** Configure the timing based on the `SystemCoreClock`.
4.  **Transmission:** Enable the Transmitter (TE) and the UART peripheral (UE).

---

## 🛠️ Register Breakdown

### 1. Clock Gating (`RCC->IOPENR` & `RCC->APBENR2`)
Unlike GPIOs which sit on the IO bus, UART1 is a high-speed peripheral on the APB bus. We must enable `USART1EN` in the `APBENR2` register to power the module.

### 2. Alternate Function Configuration (`MODER` & `AFR`)
Since a single pin can have multiple roles (GPIO, UART, PWM), we must:
* Set **MODER** to `10` (Alternate Function Mode).
* Set **AFR[0]** (Alternate Function Low Register) to `AF1`. This "routes" the internal UART_TX signal to physical pin PA2.

### 3. Baud Rate Register (`USART1->BRR`)
The baud rate determines the communication speed. For the PY32, the formula is:

$$BRR = \frac{f_{CK}}{\text{BaudRate}}$$

In the code, `USART1->BRR = (SystemCoreClock / 115200)` handles this calculation automatically for standard high-speed communication.

### 4. Control & Status (`CR1` & `SR`)
* **CR1 (Control Register 1):** We set the **TE** (Transmitter Enable) and **UE** (USART Enable) bits to start the engine.
* **SR (Status Register):** We poll the **TXE** (Transmit Data Register Empty) flag. This flag tells us the hardware is ready to accept the next character.

---

## 🚀 The Printf Redirection Logic

The most powerful part of this project is the `fputc` function. In the standard C library (`stdio.h`), `printf` eventually calls a low-level function named `fputc` to print individual characters.

**By defining our own `fputc` in the code:**
1.  We **intercept** every character sent by `printf`.
2.  We pass that character to our `UART1_SendChar` function.
3.  The character is sent over the wire to the PC.

> This transforms the MCU from a "silent" chip into one that can report its status, such as:
> `printf("System Uptime: %u ms\r\n", msTick);`