![Underware logo](https://github.com/theAgingApprentice/icUnderwear/blob/main/img/underwareBanner.png)
[![LICENSE](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/mmistakes/minimal-mistakes/master/LICENSE)
[![Doxygen Action](https://github.com/theAgingApprentice/aaChip/actions/workflows/main.yml/badge.svg?event=push)](https://github.com/theAgingApprentice/aaChip/actions/workflows/main.yml)

# hexbotCompiler - Bringing legs to life.

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
This repository contains C++ code intended to run on your computer in order to generate workflows
that can be fed into the Hexbot robot via MQTT in order to orchestrate complex movements for the
robot's six legs.

## Features

* Accepts command line arguments.
* Access to system variables.
* Repo auto generates online documentation
* MIT License

## Compatability 

* This code has only been built and tested on an iMac OSX Monterey. 

## Development environment
This library was written using the following tools:
* [<img src="/img/vscLogo.png" width="15" height="15">](https://code.visualstudio.com/docs) 
Microsoft's Visual Studio Code source code editor. 
* C++ plugins.

## Code documentation
This repository automatcally generates 
[online documentation](https://theagingapprentice.github.io/hexbotCompiler/html/index.html) 
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
