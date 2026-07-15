# Rules baseline

The Magilano rules booklet is the normative source for physical game rules. This document is a
project-owned summary and must not reproduce the booklet verbatim.

## Canonical deck

The deck contains 150 cards:

| Value         | Quantity          |
|---------------|-------------------|
| -2            | 5                 |
| -1            | 10                |
| 0             | 15                |
| 1 through 12  | 10 of each value  |

## Baseline round behavior

- Two to eight players receive twelve hidden cards each.
- Each tableau contains four vertical columns of three fixed positions.
- Each player reveals two cards before the first turn.
- During the first round, the greatest sum of the two revealed cards determines the starter.
- During later rounds, the player who ended the previous round starts.
- A player takes either the visible discard or a hidden draw-pile card.
- Taking the discard requires an immediate swap with one tableau card.
- A drawn card may be swapped into the tableau or discarded; discarding it requires revealing one
  hidden tableau card.
- Three visible equal values in one vertical column are removed to the discard pile.
- When one player has no hidden occupied position remaining, subsequent players complete the
  current rotation once.
- Remaining hidden cards are revealed, removable columns are processed, and scores are computed.
- The round finisher's positive round score is doubled when another player has an equal or lower
  round score.
- The match ends after a round when at least one cumulative score reaches 100 or more. The lowest
  cumulative score wins.

Project-specific tie breakers and network policies are defined separately in
[`rules-decisions.md`](rules-decisions.md).
