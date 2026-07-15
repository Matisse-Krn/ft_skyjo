# Architecture

## Goal

The first deliverable is a deterministic C++20 game-rules engine. It must not depend on a terminal,
a graphical interface, networking, persistence, JSON, or the future web stack.

## Intended dependency direction

```text
CLI / future WebSocket adapter / tests
                |
                v
        application commands
                |
                v
      domain rules and state
                |
                v
 RNG / logging / persistence adapters
```

Dependencies must point toward the domain. The domain must never include CLI, HTTP, WebSocket,
SQL, browser, or presentation concerns.

## Initial CMake targets

- `ft_skyjo_core`: static library containing domain and application logic;
- `ft_skyjo_cli`: temporary hot-seat command-line adapter;
- `ft_skyjo_tests`: test executable;
- `ft_skyjo_project_options`: shared C++ standard and sanitizer settings;
- `ft_skyjo_project_warnings`: project warning policy.

## Planned domain areas

```text
include/ft_skyjo/
├── cards/
├── commands/
├── events/
├── match/
├── players/
├── projections/
├── random/
├── round/
├── rules/
└── tableau/
```

Do not create all directories pre-emptively. Add them when the first real type belonging to that
area exists.

## Core architectural rules

1. The server will eventually be authoritative.
2. Players submit commands; they never submit resulting state.
3. Accepted commands create a new valid state and domain events.
4. Invalid commands leave the state unchanged.
5. Hidden information is filtered through player-specific projections.
6. Randomness is injected and seedable.
7. Every physical card has a unique identifier even when values are equal.
8. A player's tableau has twelve fixed positions; a removed column leaves empty positions.
9. Network timeout and disconnection policy is separated from the physical game rules.
10. Every ambiguous rule or deliberate variant is recorded in `rules-decisions.md`.

## Card model

A physical card is represented by two immutable-from-the-public-API properties:

- `CardId`: the unique identity of the physical card;
- `CardValue`: the validated scoring value, restricted to the range `[-2, 12]`.

Two cards may have the same value but must never share the same identifier.

Visibility, ownership, position and current state zone do not belong to `Card`. These
properties will be represented by round-state structures containing card identifiers.

Canonical deck construction is deterministic. Shuffling and all other random behavior
will be handled by a separate injectable random source.
