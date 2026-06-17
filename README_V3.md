# AstraPulse

## Dashboard Architecture

AstraPulse is organized into three dedicated dashboard layers, each designed to answer a different engineering question:

- What is happening right now? → Monitoring Dashboard
- What happened over time? → Telemetry Dashboard
- What is likely to happen next? → Future Trends Dashboard

This layered approach transforms AstraPulse from a simple sensor display into a real-time monitoring and predictive analytics platform.

---

# Dashboard 1 – Real-Time Monitoring Center

![Monitoring Dashboard](screenshots/dashboard1.png)

The Real-Time Monitoring Dashboard serves as the operational command center of AstraPulse. Its primary purpose is to provide an immediate overview of the current state of the system without requiring users to analyze historical charts or raw sensor data.

Three critical subsystems are continuously monitored:

## Thermal Module

The Thermal gauge displays live temperature measurements collected from the onboard temperature sensing system connected to the ESP32.

This panel enables operators to:
- Observe current thermal conditions
- Detect abnormal temperature rise
- Identify overheating scenarios
- Monitor environmental stability

The gauge design was intentionally selected because temperature is most useful as an instantaneous metric. Users can immediately determine whether the system is operating inside its safe thermal envelope.

## Motion Module

The Motion gauge displays real-time acceleration values derived from the MPU6050 sensor.

Acceleration monitoring provides insight into:
- Device movement
- Sudden shocks
- Vibrations
- Dynamic motion events
- Stability conditions

By continuously updating acceleration values through MQTT, the dashboard allows users to identify motion disturbances as soon as they occur.

This module can be extended for applications such as:
- Industrial equipment monitoring
- Portable device tracking
- Vibration analysis
- Impact detection

## Attitude Module

The Attitude section displays gyroscope-derived angular velocity measurements.

This component provides information about rotational movement and orientation changes.

The gyroscope subsystem is useful for:
- Rotation detection
- Orientation monitoring
- Stability verification
- Dynamic attitude tracking

Because rotational instability often appears before complete system disturbance, this gauge acts as an early indicator of changing operating conditions.

## System Status Engine

The status banner consolidates information from all monitored subsystems into a single human-readable system state.

Examples include:
- Thermal Nominal
- Motion Stable
- Attitude Locked

Rather than forcing users to interpret multiple sensor values manually, AstraPulse generates a summarized operational status that can be understood at a glance.

---

# Dashboard 2 – Telemetry & Historical Analytics

![Telemetry Dashboard](screenshots/dashboard2.png)

While Dashboard 1 focuses on current conditions, Dashboard 2 focuses on historical behavior.

This dashboard transforms live sensor readings into time-series telemetry, allowing users to study trends and observe how system conditions evolve.

## Temperature Trend Analysis

The temperature graph plots thermal readings over time.

Unlike a gauge that only shows the current value, the trend graph reveals:
- Heating patterns
- Cooling patterns
- Thermal spikes
- Long-term drift
- System warm-up behavior

For engineering applications, trend visibility is often more valuable than a single temperature reading.

## Acceleration Trend Analysis

The acceleration chart continuously records motion activity.

The graph provides insight into:
- Motion intensity
- Sudden acceleration events
- Repeated vibration cycles
- Disturbance duration
- Dynamic behavior patterns

Because acceleration data is highly time-dependent, visualizing it as a trend allows operators to identify recurring movement signatures that would otherwise be hidden.

## Gyroscope Trend Analysis

The gyroscope chart visualizes rotational activity over time.

This module helps identify:
- Rotation events
- Oscillation behavior
- Orientation changes
- Stability degradation
- Angular disturbances

## Why Telemetry Matters

Real-time values only answer the question:

"What is happening right now?"

Telemetry answers:

"What has been happening for the last several minutes?"

This distinction is critical for diagnostics, troubleshooting, and predictive analysis.

---

# Dashboard 3 – Future Trends & Predictive Intelligence

![Future Trends Dashboard](screenshots/dashboard3.png)

The Future Trends Dashboard represents the analytical layer of AstraPulse.

Rather than displaying only current or historical values, this dashboard attempts to estimate future system behavior and identify developing risks.

This transforms AstraPulse from a monitoring system into a predictive monitoring platform.

## Temperature Prediction Engine

The temperature prediction module evaluates recent thermal behavior and generates future-state assessments.

Examples include:
- Temperature Stable
- Rising Temperature
- Thermal Risk Detected

This provides early warning capability before a critical condition occurs.

## Motion Prediction Engine

The acceleration prediction module analyzes motion patterns and identifies upcoming turbulence or instability.

The system can detect:
- Emerging vibrations
- Movement disturbances
- Instability trends
- Motion anomalies

Instead of reacting after turbulence occurs, operators gain advance awareness of changing conditions.

## Gyroscope Prediction Engine

The gyroscope prediction system evaluates rotational stability.

By analyzing recent angular velocity behavior, AstraPulse can highlight potential instability before it becomes visible on the monitoring dashboard.

## Risk Assessment Module

The Risk Gauge acts as a unified health indicator for the entire platform.

The score is derived from the combined behavior of:
- Temperature subsystem
- Motion subsystem
- Attitude subsystem
- Predictive analytics engine

Higher values indicate increasing operational uncertainty or instability.

## Engineering Significance

AstraPulse was designed around a progressive decision-making pipeline:

Observe → Analyze → Predict

1. Observe real-time conditions.
2. Analyze historical behavior.
3. Predict future system states.

This architecture mirrors the workflow used in modern industrial monitoring systems, predictive maintenance platforms, aerospace telemetry systems, and intelligent IoT deployments.
