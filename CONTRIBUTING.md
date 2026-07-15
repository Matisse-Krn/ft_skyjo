# Contributing

## Branch model

`main` contains stable milestones. `dev` is the integration branch. Development occurs in
short-lived branches created from an up-to-date `dev`.

```bash
git switch dev
git pull --ff-only origin dev
git switch -c chore/first-architecture
```

Recommended prefixes:

- `feat/`: new behavior;
- `fix/`: bug correction;
- `chore/`: tooling or maintenance;
- `docs/`: documentation only;
- `refactor/`: internal change without intentional behavior change;
- `test/`: test-only work.

## Local verification

Before pushing:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug

cmake --preset asan-ubsan
cmake --build --preset asan-ubsan
ctest --preset asan-ubsan
```

Format C++ files:

```bash
find apps include src tests \
  -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) \
  -exec clang-format -i {} +
```

## Pull requests

Ordinary changes target `dev`. A stable milestone is promoted through a pull request from `dev`
to `main`.

A pull request must:

- have a narrow purpose;
- link or describe the corresponding task;
- state acceptance criteria;
- include tests for changed behavior;
- update rule documentation when game behavior changes;
- pass all required CI checks;
- declare remaining limitations and risks.

While the repository has a single contributor, required approving reviews must remain disabled.
The author cannot approve their own pull request. Enable at least one required approval only after
another active contributor can review changes.

## Commit messages

Use short imperative messages with an optional scope:

```text
chore(cmake): add sanitizer presets
feat(deck): create the canonical 150-card distribution
fix(scoring): double the finisher score on equality
test(round): cover multiple final column removals
docs(rules): define draw-pile recycling
```
