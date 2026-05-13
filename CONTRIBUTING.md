# Contributing

## Adding a new definition

Definitions for acronyms are stored in [`data/`](./data). Instructions for creating or
modifying an acronym's definition are in the [README](./README.md).

## Using development data

The easiest way to set up the executable to use data from [`data/`](./data) is to make
a symbolic link exists at `~/.local/share/wtf-is` and points to [`data/`](./data).

You can call [`symlink-data.sh`](./symlink-data.sh) to create this symbolic link.
