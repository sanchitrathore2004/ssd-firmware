# SSD Firmware Simulator

A C++ based SSD firmware simulator that models core firmware components involved in managing NAND flash storage.

## Overview

This project simulates how SSD firmware manages host I/O requests, logical-to-physical address mapping, NAND flash pages, garbage collection, and wear leveling.

```text
Host I/O
   |
   v
Request Manager
   |
   v
FTL
   |
   +--------> Wear Leveling
   |
   +--------> Garbage Collection
   |
   v
NAND Flash Simulator
```

## Features

* NAND flash memory simulation
* Flash blocks and pages
* Page program, read, erase and invalidate operations
* Logical Block Address (LBA) to Physical Address mapping
* Flash Translation Layer (FTL)
* Request management for READ and WRITE operations
* Garbage collection
* Invalid page reclamation
* Data relocation during garbage collection
* Basic wear leveling
* Erase count tracking
* Storage utilization metrics

## Project Structure

```text
ssd-firmware-simulator/
├── include/
│   ├── nand_flash.h
│   └── flash_page.h
├── src/
│   ├── nand_flash.cpp
│   └── flash_page.cpp
├── ftl/
│   ├── include/
│   │   └── ftl.h
│   └── src/
│       └── ftl.cpp
├── request_manager.h
├── request_manager.cpp
├── garbage_collector.h
├── garbage_collector.cpp
├── wear_leveling.h
├── wear_leveling.cpp
├── metrics.h
├── metric.cpp
├── main.cpp
├── Makefile
└── README.md
```

## Build

Requirements:

* C++17 compatible compiler
* GNU Make

Build the project:

```bash
make
```

## Run

```bash
make run
```

Or directly:

```bash
./build/simul_ssd
```

## Clean

```bash
make clean
```

## Example Output

```text
Before GC:
Programmed pages: 4
Valid pages: 3
Total erase count: 0
Least worn block: 0
GC: SUCCESS
After GC:
Programmed pages: 3
Valid pages: 3
Total erase count: 1
SSD firmware simulation completed!
```

## Garbage Collection

When an LBA is overwritten, its old physical page becomes invalid.

Garbage collection:

1. Finds a block containing invalid pages.
2. Identifies valid pages in that block.
3. Relocates valid data to free pages in another block.
4. Updates the FTL mapping.
5. Erases the old block.
6. Makes the erased block available for future writes.

## Wear Leveling

The simulator tracks the erase count of every NAND block.

The FTL selects a least-worn block when allocating pages to distribute erase/write activity across the flash device.

## Metrics

The simulator tracks:

* Number of programmed pages
* Number of valid pages
* Total block erase count

## Technologies

* C++
* C++17
* STL
* Linux/WSL
* GNU Make

## Purpose

The project demonstrates fundamental SSD firmware concepts including NAND management, FTL address translation, garbage collection, wear leveling, and storage performance management.
