# Testing strategy

## Test layers

1. Unit tests for value types and isolated rule functions.
2. Scenario tests for complete command sequences.
3. Invariant tests after every accepted command.
4. Deterministic simulation tests using recorded random seeds.
5. Adapter tests for CLI and later network projections.

## Initial required invariants

- The canonical match owns exactly 150 unique physical card identifiers.
- Each card identifier exists in exactly one state zone.
- No empty tableau position has a face state.
- No command from a non-active player changes the state.
- No accepted command is applied twice.
- An invalid command leaves state and version unchanged.
- A private drawn card is visible only to the active player projection.
- Removed columns are processed before round scoring.
- A later round starts with the preceding round finisher.

## Local commands

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug

cmake --preset asan-ubsan
cmake --build --preset asan-ubsan
ctest --preset asan-ubsan
```

## Future additions

- randomized legal-command simulations;
- property-based tests for card conservation;
- replay files containing seed, initial state, command identifiers, and expected events;
- thread sanitizer tests only after concurrent infrastructure exists;
- coverage reports used as diagnostic information, not as a substitute for scenario quality.

## Card ownership and movement validation

Future invariant and scenario tests must validate the card-storage decision recorded in
`ADR-0001`.

At every stable test state, collect identifiers from:

- draw pile;
- discard pile;
- every player tableau;
- pending-card state, when present.

Compare the resulting multiset with the canonical card-catalog identifiers.

Tests must fail with structured diagnostics when an identifier is:

- missing;
- duplicated;
- unknown;
- present in several zones.

Movement scenario tests must compare the full state before and after rejected operations to verify
that failures produce no observable mutation.

Projection tests must verify that hidden cards expose neither their value nor their stable internal
identifier.
