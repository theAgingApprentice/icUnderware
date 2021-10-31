![Underware logo](https://github.com/theAgingApprentice/icUnderwear/blob/main/img/underwareBanner.png)
[![LICENSE](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/mmistakes/minimal-mistakes/master/LICENSE)
[![Doxygen Action](https://github.com/theAgingApprentice/aaChip/actions/workflows/main.yml/badge.svg?event=push)](https://github.com/theAgingApprentice/aaChip/actions/workflows/main.yml)

# icUnderware - Robot projects start here!

## Table of contents
* [Overview](#Overview)
* [Features](#Features)
* [Compatability](#Compatability)
* [Development environment](#Development-environment)
* [Code documentation](#Code-documentation)
* [Downloading](#Downloading)
* [Testing](#Testing)
* [Releases](#Releases)
* [Acknowledgements](#Acknowledgements)

## Overview
This repository contains Arduino code that will get you off to a flying start 
when you begin your next robot project. Simply clone this template repository 
and use the source code to boot strap the development of your robot's 
integrated circuit firmware. 

## Features

* Modular code for easy maintenance
* Hardware aware for easy configuration
* Supports typical subsystems found in robot projects   
* Repo auto generates online documentation
* MIT License

## Compatability 

* This code has only been tested on the 
[Adafruit Huzzah32](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather) 
development board containing the 
[Espressif ESP WROOM32 SOC](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) 
featuring a pair of [Cadence/Xtensa®32-bit LX6 microprocessors](https://mirrobo.ru/wp-content/uploads/2016/11/Cadence_Tensillica_Xtensa_LX6_ds.pdf). 

## Development environment
This library was written using the following tools:
* [<img src="/img/vscLogo.png" width="15" height="15">](https://code.visualstudio.com/docs) 
Microsoft's Visual Studio Code source code editor. 
* [<img src="/img/pioLogo.png" width="20" height="15">](https://platformio.org/) 
PlatformIO plugin 
[embedded software](https://en.wikipedia.org/wiki/Embedded_software) application 
[IDE](https://en.wikipedia.org/wiki/Integrated_development_environment). 

## Code documentation
This repository automatcally generates 
[online documentation](https://theagingapprentice.github.io/icUnderware/html/index.html) 
each time code is merged into the main branch.

## Downloading
Detailed instructions on how to use this template repository can bew viewed [here](./aaAdmin/newRepoTodo.md).

## Testing
At this time we do not have a way to test this embedded code.

## Releases
* We use the [SemVer](http://semver.org/) numbering scheme for our releases. 
* The latest stable release is [v1.0.0](https://github.com/theAgingApprentice/underwear/releases/tag/v1.0.0).

## Acknowledgements
* The many folks involved in porting the Arduino libraries over to the ESP32 SOC.
* Adafruit for their excellent freely available tutorials.
