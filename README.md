# AstraPulse

## Overview
AstraPulse is an IoT monitoring and prediction project built using ESP32, Wokwi, MQTT and Node-RED.

The system collects sensor data, transmits it through MQTT, processes it in Node-RED and visualizes the results through dashboards and analytics.

## Features
- ESP32 based sensing system
- MQTT communication
- Node-RED dashboard
- Real-time monitoring
- Sensor data processing
- EWMA based prediction/filtering
- CSV/data logging support

## Tech Stack
- ESP32 / Arduino
- Wokwi simulation
- MQTT (HiveMQ)
- Node-RED
- Dashboard UI

## Project Flow
Sensor → ESP32 → MQTT → Node-RED → Dashboard

## Repository Structure
```text
wokwi/
node-red/
screenshots/
docs/
README.md
```

## Setup

### 1. Wokwi
Open the Wokwi project files from the `wokwi` folder.

### 2. Node-RED
Import `node-red/flows.json`.

Install dependencies if required.

### 3. MQTT
Configure MQTT broker and credentials as needed.

## Screenshots
See the `screenshots/` folder.

## License
MIT License
