# ADR-0001: Store immutable card data in a catalog and card identities in mutable zones

- **Status:** Accepted
- **Date:** 2026-07-16
- **Decision owners:** ft_skyjo maintainers
- **Related issues:** #3, #5, #6
- **Implementation follow-up:** [#19 — Implement immutable card catalog and canonical card-id sequence](https://github.com/Matisse-Krn/ft_skyjo/issues/19)

## Context

The ft_skyjo engine models one physical deck containing 150 cards.

Several physical cards may share the same value, but every physical card has one unique
identity inside a match.

During a round, cards move between:

- the draw pile;
- the discard pile;
- player tableaus;
- a private pending-card zone.

Cards belonging to a withdrawn player remain in that player's tableau until round cleanup.

The architecture must guarantee that cards cannot be silently duplicated, lost or owned by
several zones at the same time.

The design must also support:

- deterministic tests;
- replayable matches;
- snapshots;
- player-specific projections;
- future network serialization;
- global card-conservation checks.

## Decision drivers

The selected design must prioritize:

1. physical-card identity;
2. global card conservation;
3. hidden-information safety;
4. deterministic replay;
5. atomic command application;
6. simple serialization;
7. testability;
8. understandable value semantics.

## Considered options

### Option A: Store complete `Card` values in every mutable zone

Piles and tableaus would directly contain complete `Card` objects.

This provides convenient value access, but copying a `Card` may accidentally model a second
physical card. Global ownership and conservation are also harder to verify.

### Option B: Store immutable card data in one catalog and `CardId` values in mutable zones

One immutable catalog contains the authoritative mapping from `CardId` to `CardValue`.

All mutable zones contain only card identifiers.

This clearly separates:

- what a physical card is;
- where that card currently is;
- whether the current location exposes its value.

### Option C: Store pointers or shared pointers to cards

This would couple physical-card identity to memory identity, complicate serialization and
snapshots, and introduce unnecessary lifetime and ownership concerns.

### Option D: Move unique pointers between zones

This expresses unique ownership but requires pointer-based state, complicates copies,
transactions, snapshots and deterministic replay, and offers no benefit for small immutable
domain values.

## Decision

Option B is accepted.

### Immutable card catalog

A match owns one immutable card catalog.

The catalog contains exactly one definition for every physical card:

```text
CardId → CardValue
```

The catalog is not a card-ownership zone.

It defines card identity and value but does not record current location, visibility or owner.

### Card identifier scope

`CardId` is unique within one match deck.

Canonical identifiers may be dense and currently range from `0` to `149`.

Dense numbering is an internal implementation detail. Public code must not infer card value,
location or game meaning from numeric identifier arithmetic.

Identifiers may be reused in another match.

A globally meaningful physical-card reference therefore requires:

```text
MatchId + CardId
```

### Mutable card zones

Stable mutable state may contain card identifiers in these zones:

1. draw pile;
2. discard pile;
3. player tableau slots;
4. optional private pending-card zone.

A withdrawn player's cards remain in that player's tableau until round cleanup.

No dedicated withdrawn-card collection is required for the base model.

### Tableau visibility

Visibility belongs to the tableau slot, not to the card.

A tableau slot is conceptually one of:

```text
Empty
Hidden(CardId)
Revealed(CardId)
```

The `Card` type contains no visibility, owner, location or selected-state field.

### Pending card

A card drawn from the hidden draw pile moves into an explicit pending-card zone.

The pending zone is persistent domain state because a turn may span several commands,
timeouts, snapshots or reconnections.

Only the active player's projection may expose the pending card value.

### Stable-state ownership invariant

At every stable observable match state:

- every expected `CardId` exists in exactly one mutable card zone;
- no `CardId` exists in two zones;
- no unknown `CardId` exists;
- no expected `CardId` is missing.

The immutable catalog does not count as ownership.

A command implementation may temporarily hold a `CardId` in a local variable while mutating an
unpublished working state.

The ownership invariant is required again before a successful state is published.

### Atomic movement

High-level card movement is atomic at the command boundary.

```text
successful command
→ all intended card movements are published

failed command
→ the previously observable state remains unchanged
```

Low-level removal from one zone and insertion into another must occur only inside a working
state that can be discarded on failure.

### Draw-pile movement

Drawing removes the top `CardId` from the draw pile.

A hidden draw moves that identifier into the pending-card zone.

### Discard-pile movement

Taking the visible discard removes the top identifier from the discard pile and requires an
immediate tableau replacement.

The replaced tableau identifier is then pushed onto the discard pile.

### Tableau replacement

Replacing a tableau card:

1. removes the previous `CardId` from the selected occupied slot;
2. inserts the incoming `CardId`;
3. leaves the incoming slot revealed;
4. returns the previous identifier to the command layer.

The tableau does not directly decide the outgoing card's destination.

### Completed-column removal

Removing a completed equal-value column:

1. removes three identifiers from fixed tableau positions;
2. leaves those positions empty;
3. returns the identifiers in top-to-bottom row order;
4. lets the command layer push them onto the discard pile.

When a column is completed by an exchange, the exchanged card reaches the discard pile before
the three removed-column cards.

### Discard recycling

When the draw pile is empty:

1. the top discard identifier remains in the discard pile;
2. every lower discard identifier moves into a temporary working sequence;
3. that sequence is shuffled through the injected random source;
4. the resulting sequence becomes the new draw pile.

The temporary sequence is not a durable externally observable card zone.

### Round cleanup

Round cleanup gathers all card identifiers from:

- draw pile;
- discard pile;
- every player tableau;
- any pending-card zone.

The complete identifier set is validated before the next round is initialized.

The immutable card catalog remains unchanged.

### Hidden-information boundary

Stable internal `CardId` values are server-side implementation details.

Player and spectator projections must not expose the stable identifier of a hidden card.

Otherwise, a client could recognize a previously revealed physical card and infer a hidden value.

Public projections expose only information authorized for their recipient.

## Consequences

### Positive consequences

- Every physical card has one stable identity.
- Mutable state remains lightweight.
- Card values cannot change during a match.
- Global conservation checks become straightforward.
- Snapshots and event logs can refer to exact physical cards.
- Hidden-information filtering is explicit.
- Pointer ownership and lifetime management are avoided.
- Mutable game state remains easy to copy for transactional command application.

### Negative consequences

- Value lookup requires access to the card catalog.
- Functions comparing card values must receive or otherwise access the catalog explicitly.
- Invalid identifiers require a typed lookup failure.
- Internal and projected card representations must remain distinct.

### Accepted complexity

This additional indirection is accepted because identity, replay, conservation and privacy are
core correctness requirements for the authoritative game engine.

## Rejected designs

### Complete `Card` copies in mutable zones

Rejected because value copying does not express unique physical ownership and increases the risk
of duplicated cards.

### Shared ownership through `std::shared_ptr`

Rejected because cards do not have shared mutable ownership and memory identity is unsuitable for
serialization and replay.

### Unique ownership through `std::unique_ptr`

Rejected because pointer-based movement complicates transactional state copies, snapshots and
tests without providing a necessary benefit.

### Store location and visibility directly in `Card`

Rejected because location and visibility are mutable state-zone properties, not immutable
physical-card properties.

## Follow-up implementation

A dedicated implementation issue must add:

- an immutable `CardCatalog`;
- canonical lookup by `CardId`;
- a canonical identifier sequence;
- validation of invalid identifiers;
- unit tests for catalog completeness and lookup behavior.

Piles, tableaus and pending-card state will then store only `CardId` values.

## Validation of this decision

The implementation is considered compliant when tests can verify that:

- the catalog contains exactly 150 card definitions;
- every mutable stable state owns every canonical identifier exactly once;
- movement preserves the complete identifier set;
- hidden projections contain no stable hidden-card identifier;
- replay can identify every moved physical card deterministically.
