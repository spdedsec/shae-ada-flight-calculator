# shae-ada-flight-calculator — Design

This project adheres to the [SHAE Field Manual Design System](https://github.com/spdedsec/shae-site).

## Core principles applied

- **Precise over decorative.** Aligned numeric tables, monospaced metadata, no ornamental noise.
- **Confident restraint.** Single signal colour (oxide #B3341B) for error output; warm paper ground (#F2EEE5) in terminal context: clean terminal output with minimal ANSI escape codes.
- **Type does the work.** Labels in uppercase-only short form; data values in monospace tabular numerals.
- **Motion is typesetting, state, and orientation — never spectacle.** Position-table updates are instant.
- **Accessibility is part of the aesthetic.** WCAG AA contrast for coloured error output, complete keyboard paths, 44px conceptual touch target.

## Anti-patterns avoided

No gradients, glows, pills, glassmorphism, rounded floating panels, decorative confetti, centered mobile heroes, or animation libraries.

## Colour palette

- **Warm Paper:** #F2EEE5 (terminal default, not emitted unless explicitly themed)
- **Ink:** #191712 (equivalent to default terminal black/white)
- **Oxide Signal:** #B3341B (used for error messages to stderr)