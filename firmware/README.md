# HP8562A Tracking Generator Firmware

Firmware for the HP8562A Tracking Generator project.

This firmware controls the synthesizer and associated hardware required to generate a tracking signal for use with the Hewlett-Packard HP8562A Spectrum Analyzer. The project is currently based on the Raspberry Pi Pico platform and includes PLL control, frequency management, and supporting hardware interfaces.

## Folder Structure

```
firmware/
├── build/      # Build configuration and generated build files
├── docs/       # Firmware-specific documentation
└── sources/    # Source code
```

## Features

- Raspberry Pi Pico based controller
- PLL frequency synthesizer control
- Tracking generator frequency generation
- Modular firmware structure
- Designed for integration with the HP8562A spectrum analyzer

## Requirements

### Hardware

- Raspberry Pi Pico2 / Pico2 W
- Tracking Generator hardware
- PLL synthesizer circuitry
- HP8562A Spectrum Analyzer

### Software build

Simply use Arduino IDE with Philhower's Raspberry Pi Pico Arduino core (https://github.com/earlephilhower/arduino-pico)
or upload one of the binaries to PICO folder. 

Or use your own preferred Pico SDK workflow.

## Source Code

The `sources` directory contains:

- Hardware abstraction layers
- PLL control code
- Frequency calculation routines
- Device drivers
- Main application logic

## Documentation

Additional design notes, schematics, architecture descriptions, and firmware documentation can be found in the `docs` directory.

## Development Status

Although the firmware is somehow finished, adding new modules will include additional development. 
Watch this space! 

Recent work includes:

- Firmware restructuring and cleanup
- Implementation of a new PLL control architecture
- Raspberry Pi Pico support

## Contributing

Contributions, bug reports, and suggestions are welcome. Please open an issue or submit a pull request.

## License

Refer to the repository license file for licensing information.

## Author

PA3AEF
