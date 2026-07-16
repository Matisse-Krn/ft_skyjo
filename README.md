# ft_skyjo

`ft_skyjo` is a public C++20 proof of concept for a deterministic, testable,
and server-authoritative implementation of a Skyjo-like card game.

It is preparatory work for a possible game component in the 42
`ft_transcendence` project.

The current repository contains only the engineering foundation:

- target-based CMake configuration;
- reproducible CMake presets;
- a core static library and a separate CLI executable;
- Catch2 unit-test integration;
- GitHub Actions continuous integration;
- formatting, warning, and sanitizer policies;
- rules and architecture decision documentation.

No complete game logic is implemented yet.

## Prerequisites

- CMake 3.25 or later;
- a C++20 compiler;
- Ninja;
- Git;
- internet access during the first test configuration so CMake can fetch the pinned Catch2
  release.

Debian example:

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build clang clang-format clang-tidy git
```

## Configure, build, and test

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Sanitizer build:

```bash
cmake --preset asan-ubsan
cmake --build --preset asan-ubsan
ctest --preset asan-ubsan
```

Release build:

```bash
cmake --preset release
cmake --build --preset release
ctest --preset release
```

Run the current CLI smoke executable:

```bash
./build/debug/apps/cli/ft_skyjo_cli
```

## Repository workflow

- `main`: stable milestones only;
- `dev`: integration branch;
- short-lived branches: `feat/*`, `fix/*`, `chore/*`, `docs/*`, `refactor/*`, `test/*`;
- ordinary pull requests target `dev`;
- only `dev` may open a pull request into `main`;
- direct pushes to `main` and `dev` should be blocked by repository rules.

See [`CONTRIBUTING.md`](CONTRIBUTING.md).

## Documentation

- [`docs/architecture.md`](docs/architecture.md)
- [`docs/invariants.md`](docs/invariants.md)
- [`docs/rules.md`](docs/rules.md)
- [`docs/rules-decisions.md`](docs/rules-decisions.md)
- [`docs/testing.md`](docs/testing.md)
- [`docs/adr/README.md`](docs/adr/README.md)
- [`ADR-0001: Card storage and movement`](docs/adr/0001-card-storage-and-movement.md)

## External dependency

Tests use Catch2 v3.15.2. CMake first searches for a compatible local installation, then fetches
the official repository at the immutable release commit
`191fa38c9b1596cd2576ab531d4ab4d5e8e05190`.

## License and branding

This repository is publicly visible but currently has no open-source license.

Unless a license is added, default copyright rules apply: public visibility does
not grant general permission to use, modify or redistribute the source code beyond
the rights provided by GitHub's Terms of Service.

The project name, branding and final licensing policy must be reviewed before a
stable release or integration into the final `ft_transcendence` project.
