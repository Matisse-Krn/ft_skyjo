# Domain invariants

This document lists properties that must remain true across the ft_skyjo domain model.

An invariant is stronger than an ordinary expected behavior: any stable state violating an
invariant is considered invalid.

## Card catalog invariants

- The canonical catalog contains exactly 150 physical card definitions.
- Every catalog entry has one unique `CardId`.
- Every catalog entry has one valid `CardValue`.
- A card's identifier never changes.
- A card's value never changes.
- The catalog contains no location, owner or visibility state.

## Card identity scope

- `CardId` is unique within one match deck.
- Numeric card identifiers do not encode card value.
- Numeric card identifiers do not encode current location.
- Cross-match identity requires both `MatchId` and `CardId`.

## Stable ownership invariants

At every stable observable match state:

- every canonical `CardId` appears in exactly one mutable card zone;
- no `CardId` appears in more than one zone;
- no canonical `CardId` is missing;
- no unknown `CardId` appears;
- the total number of owned identifiers is exactly 150.

The immutable catalog is not counted as ownership.

## Card-owning zones

Stable mutable card-owning zones are:

- draw pile;
- discard pile;
- player tableau slots;
- optional pending-card zone.

A withdrawn player's cards remain owned by that player's tableau until round cleanup.

## Draw-pile invariants

- Every draw-pile element is a valid `CardId`.
- Draw-pile order is deterministic for a given initial state and random sequence.
- Only the top identifier may be removed by normal draw behavior.
- Draw-pile order is hidden from player and spectator projections.

## Discard-pile invariants

- Every discard-pile element is a valid `CardId`.
- The top discard identifier is well-defined when the pile is non-empty.
- Only the top discard card is available through normal player actions.
- Recycling preserves the top discard identifier.

## Tableau invariants

Every tableau position is exactly one of:

```text
Empty
Hidden(CardId)
Revealed(CardId)
```

Therefore:

- an empty position contains no identifier;
- a hidden position contains exactly one identifier;
- a revealed position contains exactly one identifier;
- visibility is not stored in `Card`;
- removing a card never changes another position's index.

## Pending-card invariants

- At most one pending card exists for a round turn.
- A pending card is not present in any other zone.
- A pending card belongs to the active turn.
- A pending card value is visible only to the authorized active-player projection.
- A turn cannot finish while a pending card remains unresolved.

## Movement invariants

At a successful command boundary:

- every intended source zone has lost the moved identifier;
- every intended destination zone has gained the moved identifier;
- no unrelated zone has changed ownership;
- the global identifier set is conserved.

At a failed command boundary:

- the observable state is unchanged;
- no identifier remains in a partial transition state.

## Column-removal invariants

A removed column:

- contained three occupied revealed positions;
- contained three cards with equal values;
- leaves three empty fixed positions;
- returns exactly three distinct identifiers;
- moves those identifiers to the discard pile through the command layer.

When removal follows an exchange, the exchanged card reaches the discard pile before the removed
column cards.

## Hidden-information invariants

A player or spectator projection must never expose:

- the value of an unauthorized hidden tableau card;
- the stable identifier of an unauthorized hidden tableau card;
- the complete draw-pile order;
- another player's pending-card identifier or value.

## Round-cleanup invariants

Before a new round begins:

- all 150 canonical identifiers are recoverable;
- no pending card remains;
- no identifier is duplicated;
- all mutable card zones can be rebuilt from the complete identifier set;
- the immutable catalog remains unchanged.
