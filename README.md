# ft_skyjo

`ft_skyjo` is a private C++20 proof of concept for a deterministic, testable, and
server-authoritative implementation of a Skyjo-like card game. It is preparatory work for a
possible game component in the 42 `ft_transcendence` project.

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
- [`docs/rules.md`](docs/rules.md)
- [`docs/rules-decisions.md`](docs/rules-decisions.md)
- [`docs/testing.md`](docs/testing.md)

## External dependency

Tests use Catch2 v3.15.2. CMake first searches for a compatible local installation, then fetches
the official repository at the immutable release commit
`191fa38c9b1596cd2576ab531d4ab4d5e8e05190`.

## License and branding

No public license has been selected. The repository is private. The project name and branding
must be reviewed before any public release.
