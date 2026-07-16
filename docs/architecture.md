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

## Card identity, catalog and ownership

Physical-card definition and mutable card location are separate concerns.

### Immutable card data

One immutable card catalog defines the complete physical deck:

```text
CardId → CardValue
```

A `CardId` is unique inside one match deck. Its numeric value has no game meaning and must not be
used to infer the card value or current location.

### Mutable ownership zones

Mutable round state stores only card identifiers.

Stable card-owning zones are:

- draw pile;
- discard pile;
- fixed player tableau slots;
- optional private pending-card zone.

The card catalog is not an ownership zone.

At every stable observable state, every canonical identifier must appear in exactly one mutable
zone.

### Tableau state

Visibility belongs to a tableau position rather than to the physical card.

A position is conceptually:

```text
Empty
Hidden(CardId)
Revealed(CardId)
```

Removed columns leave three empty fixed positions.

### Pending-card state

Drawing from the hidden pile creates an explicit pending-card state owned by the active turn.

This state persists until the player either:

- swaps the pending card into the tableau;
- or discards it and reveals a hidden tableau position.

### Atomic transitions

Card movement is atomic at command boundaries.

A failed command leaves the previously observable state unchanged. A successful command publishes
a complete new valid state.

### Information security

Stable internal card identifiers must not be exposed for hidden cards in player or spectator
projections.

The authoritative engine may know a hidden `CardId`, while a recipient projection exposes only a
hidden-card marker.

The complete decision is recorded in
[`ADR-0001`](adr/0001-card-storage-and-movement.md).
