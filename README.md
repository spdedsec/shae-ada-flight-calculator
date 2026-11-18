# shae-ada-flight-calculator

A CLI flight trajectory calculator conforming to the SHAE Field Manual design system.

## Installation

```bash
make
make install
```

This copies `~/.local/bin/shae-ada-flight-calculator`.

CLI usage:

```
shae-ada-flight-calculator <velocity> <angle_deg> <gravity>
```

Example:

```bash
shae-ada-flight-calculator 50 45 9.81
```

Inputs:
- velocity: initial speed in m/s (positive number)
- angle_deg: launch angle in degrees (0 < angle < 90)
- gravity: acceleration due to gravity in m/s^2 (positive number)

Outputs:
- Time of flight
- Max height
- Horizontal range
- Impact velocity
- Position table at 10 ms intervals

## Design

- No gradients, glass, shadows, or pills
- Terminal output uses plain tabular text
- Error messages routed to stderr in oxide-red console styling
- All numeric output is precise; tabular data alignment via fixed formatting
- Focus rings and motion guidelines apply only to the reference web UI

## Release workflow

Run `make release` to build the binary and publish a GitHub release with the asset.