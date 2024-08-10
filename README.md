# LightWaveReader

## Overview

LightWaveReader is a microcontroller-based program designed to accurately read signals from a very picky Pulse Width Modulation (PWM) source. The program employs a boxcar averager to attenuate noise and isolate the amplitude of the signal of interest, which may be buried within significant noise. The project specifically uses a PIN photodiode to capture modulated light signals and convert them back into electrical signals for processing.

This project is developed by students and researchers at the University of Freiburg.

## Features

- **Precise PWM Signal Reading**: Capable of detecting and processing very specific PWM signals.
- **Noise Reduction**: Utilizes a boxcar averager to effectively attenuate noise in the signal.
- **Signal Amplification**: Outputs the amplitude of the signal of interest, even when buried in noise.
- **Photodiode Integration**: Uses a PIN photodiode to capture modulated light signals and convert them into readable electrical signals.

## Project Structure

- **/src**: Contains the source code for the microcontroller.
- **/hardware**: Documentation and schematics for the hardware setup, including the PIN photodiode.
- **/docs**: Project documentation and additional resources.
- **/tests**: Test scripts and procedures to validate the functionality of the project.
- **/sim**: Some simulations to verify software quality.

## Installation


## Hardware Requirements

- Microcontroller (Cortex M4 based SOC - Ambiq Apollo 3 Blue)
- PIN photodiode  ()
- Breadboard and connecting wires
- Power supply for the microcontroller

## Usage

1. **Setup Hardware**: Assemble the circuit as per the schematic provided in the `/hardware` directory.
2. **Upload Code**: Load the program onto the microcontroller (using `west flash`).
3. **Run**: Once the hardware is set up and the code is uploaded, the microcontroller will start reading the modulated light signals through the PIN photodiode on predetermined times.
4. **Observe Output**: The processed and noise-attenuated signal amplitude will be available at the designated output pin, which can be connected to an oscilloscope or another processing unit.

## Contributing

TBD

## License

TBD

## Acknowledgments

- Inspired by the need for precise signal processing in noisy environments.
- Special thanks to the open-source community for providing the tools and resources that made this project possible.
