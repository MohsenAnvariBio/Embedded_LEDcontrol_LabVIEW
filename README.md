# LED Brightness Control with USART and LabVIEW
LabVIEW | LED Brightness Control | UART | PWM

This project demonstrates how to control the brightness of an LED connected to the NUCLEO STM32F446RE development board using LabVIEW and USART communication.

---

## Overview

This project allows the user to configure the USART settings and send brightness levels to the STM32F446RE microcontroller using a LabVIEW `.vi` file. The microcontroller receives the data via USART and adjusts the brightness of the LED connected to pin `PA0` using PWM.

---

## Features

- **LabVIEW Integration**: Includes a LabVIEW `.vi` file located in the `LabVIEW_files` folder for easy configuration and control.
- **USART Communication**: Implements UART communication to receive brightness levels.
- **PWM Control**: Adjusts the LED brightness dynamically using a hardware timer (TIM2) and PWM.
- **STM32F446RE**: Compatible with the NUCLEO STM32F446RE development board.

---

## How It Works

1. **LabVIEW Configuration**:
   - The user configures the USART settings and sends the brightness level (0–100%) to the STM32 board using the `.vi` file.

2. **STM32 Board**:
   - The board receives the data via USART2 and processes it.
   - The received brightness value is mapped to the PWM duty cycle for controlling the LED brightness.

3. **PWM Output**:
   - The TIM2 timer generates PWM signals, and the LED brightness is updated based on the received duty cycle.

---

## Folder Structure

- **LabVIEW_files**: Contains the LabVIEW `.vi` file for user interaction.
- **src**: Contains the main application code, including:
  - `main_app.c`
  - `main_app.h`
  - Other related files.

---

## Hardware Requirements

- NUCLEO STM32F446RE development board
- LED connected to pin `PA0`
- USB connection for USART communication
- LabVIEW software installed on the user's PC

---

## Software Requirements

- **Toolchains**:
  - STM32CubeIDE or Keil uVision for code compilation and debugging
- **LabVIEW**:
  - For running the provided `.vi` file
- **USART Drivers**:
  - Ensure proper USB-to-serial drivers are installed for PC communication.

---

## Setup and Usage

1. **Hardware Setup**:
   - Connect an LED to pin `PA0` of the STM32 board.
   - Power the STM32 board using a USB cable.

2. **Software Setup**:
   - Open the LabVIEW `.vi` file from the `LabVIEW_files` folder.
   - Configure the USART settings to match the STM32 configuration (Baud rate: 115200, 8N1 format).

3. **Run the Application**:
   - Flash the compiled code to the STM32 board.
   - Use LabVIEW to send brightness values to the board.
   - Observe the LED brightness changing based on the input.

---

## USART Configuration

- **Baud Rate**: 115200
- **Word Length**: 8 Bits
- **Stop Bits**: 1
- **Parity**: None
- **Flow Control**: None

---

## LabVIEW Instructions

1. Open the `.vi` file in LabVIEW.
2. Set the desired brightness level (0-100%) using the provided slider or numeric input.
3. Click "SET" to transmit the brightness value to the STM32 board.

![image](https://github.com/user-attachments/assets/43549544-32fe-4390-b5f1-fb3a8eb5d7e5)


---

## Code Highlights

- **PWM Initialization**:
  - TIM2 is configured to generate PWM signals with a frequency based on the system clock.
  - The duty cycle is dynamically updated using `HAL_TIM_PWM_Start_IT`.

- **USART Handling**:
  - Uses `HAL_UART_Receive_IT` to receive brightness values in interrupt mode.
  - The callback function `HAL_UART_RxCpltCallback` processes the received data.

---

## Contributing

Contributions to enhance the project are welcome. Please follow the standard GitHub workflow:

1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Submit a pull request.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

For further assistance or inquiries, please contact: [your email here].
