# Architecture Decision Records

This directory contains Architecture Decision Records for ft_skyjo.

## Purpose

An ADR records one architecturally significant decision, its context, considered
alternatives and consequences.

## Numbering

ADR files use a four-digit sequential prefix:

```text
NNNN-short-decision-title.md
```

## Status lifecycle

```text
Proposed → Accepted
Proposed → Rejected
Accepted → Deprecated
Accepted → Superseded by another ADR
```

## Maintenance

Accepted ADRs are historical records.

Do not rewrite an accepted decision to change its meaning. When a decision changes,
create a new ADR and mark the previous one as superseded.

Minor corrections, link fixes and implementation references may be added without
changing the recorded decision.

## Relationship with implementation

ADRs explain why an architectural choice exists.

Production code, tests and architecture documentation implement and enforce the accepted
decision.
