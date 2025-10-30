# PY32F0xx UART Communication Example

This project demonstrates how to configure and use **USART1** on the **PY32F0xx** microcontroller family (STM32-compatible) using **pure register-level programming**, without relying on HAL or CubeMX.

---

## 🔧 Features
- UART1 initialization using CMSIS-style register access  
- Interrupt-based UART RX handling  
- LED toggling via SysTick timer  
- Simple delay function using SysTick  
- Callback mechanism for received data processing

---


## ⚙️ Build Information
- **IDE:** Keil µVision 5  
- **Compiler:** ARMClang (V6.21)  
- **Clock:** 8 MHz (HSI)  
- **Baud Rate:** 9600 bps  
- **UART Pins:**  
  - PA2 → TX  
  - PA3 → RX

---

## 🧩 How It Works
1. The UART is initialized and configured for 9600 baud, 8N1.  
2. Incoming characters trigger the USART1 interrupt.  
3. When a full line (`\r`) is received, the callback is executed.  
4. The received string is echoed back over UART.  
5. Meanwhile, the onboard LED on **PA13** toggles every 1 second.


---

## 📬 Example Serial Output
- Core Clock: 8000000
- You sent: hello


---

## 🧰 Requirements
- Keil µVision 5 or later  
- PY32F0xx development board  
- USB-to-UART converter (for serial communication)

---

## 🧑‍💻 Author
**Abolfazl Resalati**  
Electronics student and embedded systems enthusiast.  
All code written in C, using low-level register access for educational purposes.
