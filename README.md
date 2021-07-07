# Electron gun power supply and monitoring controller

This is firmware for a simple electron gun controller that is controlling

* Up to four FUG HCP 14-6500 high voltage power supplies (acceleration
  voltage, Wehnelt cylinder, focus voltage and a single deflection voltage
  power supply)
* The voltage and current measured by FUG HCP 14-6500 can also be used for
  general monitoring and beam loss measurement

## External communication ports

* UART0 provides main communication interface (and is also used by avrdude
  during flashing - there is an Arduino bootloader flashed on the board so
  flash method ```ẁiring``` can be used via USB

* Other UARTs may be used for RS485 or other components later on

## Pin assignment

| Pin | Assignment                          | Mode                      | ATEMGA2560 Port / Pin |
| --- | ----------------------------------- | ------------------------- | --------------------- |
| 22  | PSU1: Output enable                 | Digital out (optocoupled) | PA0                   |
| 23  | PSU1: Polarity set                  | Digital out (optocoupled) | PA1                   |
| 24  | PSU1: Current control mode          | Digital in                | PA2                   |
| 25  | PSU1: Voltage control mode          | Digital in                | PA3                   |
| 42  | PSU1: Voltage set                   | Analog out                | PL7                   |
| 43  | PSU1: Current limit set             | Analog out                | PL6                   |
| A0  | PSU1: Voltage sense                 | Analog in                 | PF0                   |
| A1  | PSU1: Current sense                 | Analog in                 | PF1                   |
| 26  | PSU2: Output enable                 | Digital out (optocoupled) | PA4                   |
| 27  | PSU2: Polarity set                  | Digital out (optocoupled) | PA5                   |
| 28  | PSU2: Current control mode          | Digital in                | PA6                   |
| 29  | PSU2: Voltage control mode          | Digital in                | PA7                   |
| 44  | PSU2: Voltage set                   | Analog out                | PL5                   |
| 45  | PSU2: Current limit set             | Analog out                | PL4                   |
| A2  | PSU2: Voltage sense                 | Analog in                 | PF2                   |
| A3  | PSU2: Current sense                 | Analog in                 | PF3                   |
| 30  | PSU3: Output enable                 | Digital out (optocoupled) | PC7                   |
| 31  | PSU3: Polarity set                  | Digital out (optocoupled) | PC6                   |
| 32  | PSU3: Current control mode          | Digital in                | PC5                   |
| 33  | PSU3: Voltage control mode          | Digital in                | PC4                   |
| 46  | PSU3: Voltage set                   | Analog out                | PL3                   |
| 47  | PSU3: Current limit set             | Analog out                | PL2                   |
| A4  | PSU3: Voltage sense                 | Analog in                 | PF4                   |
| A5  | PSU3: Current sense                 | Analog in                 | PF5                   |
| 34  | PSU4: Output enable                 | Digital out (optocoupled) | PC3                   |
| 35  | PSU4: Polarity set                  | Digital out (optocoupled) | PC2                   |
| 36  | PSU4: Current control mode          | Digital in                | PC1                   |
| 37  | PSU4: Voltage control mode          | Digital in                | PC0                   |
| 48  | PSU4: Voltage set                   | Analog out                | PL1                   |
| 49  | PSU4: Current limit set             | Analog out                | PL0                   |
| A6  | PSU4: Voltage sense                 | Analog in                 | PF6                   |
| A7  | PSU4: Current sense                 | Analog in                 | PF7                   |
| 38  | Filament power supply (230V side)   | Digital out               | PD7                   |

## Protocol

In contrast to other implementations this board supports an ASCII based
communication protocol. For synchronization all messages start with a
fixed synchronization pattern consisting of three dollar signs. Each command
is terminated via a CR LF or only LF (CR is simply ignored by the serial
parser). Numbers are transmitted as ASCII decimal numbers.

| Command | Sequence     | Response                                                                                             |
| ID      | $$$ID<CR,LF> | Sends a simple ID response that identifies the firmware (ex. ```$$$electronctrl_20210707_001<LF>```) |


* Per PSU (use PSU index):
    * Output enable on/off + status
    * PSU polarity (?expose?) + status
    * Set Voltage
    * Set Current Limit
    * Get Mode (Status: CV or CC)
    * Get current voltage
    * Get current current
* External switch for filament:
    * Filament power on/off (bypassing external switch)
    * Filament voltage
    * Filament current
* High level:
    * Beam HV on (enable / disable beam)
        Procedure (doing an insulation test):
            * First sets low current limit (~ 20 uA)
            * Set voltages to 0
            * Wait for ~ 2 secs
            * Set output on
            * Increases voltage slowly (~ 10 V / sec?)
            * Check if not going into current limiting mode
                If current limiting -> error status, turn off everything
            * If reaching target: Set current limit high
    * Beam HV off:
            * All voltages set 0
            * Output off
    * Filament current on
    * Filament current off
    * Get estimated beam current
