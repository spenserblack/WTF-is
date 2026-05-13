# `wtf is`

## Example

```console
$ wtf is IIRC
iirc:
	general:	If I remember correctly
```

## Description

`wtf is` is a utility to get the definition of an acronym. You type `wtf is` in your
console, followed by the acronym you want defined.

### Adding or modifying your acronym definitions

Acronym definitions are read from data files. They can exist in either
`/usr/share/wtf-is/` or `~/.local/share/wtf-is/`. The files should be named
`CATEGORY.txt`, where `CATEGORY` is the category of the acronym definition. Here are
some example filenames:

- `general.txt` for standard definitions
- `comp.txt` for acronyms related to the field of computer science
- `vulgar.txt` for acronyms that have offensive definitions

Definitions are in the format `ABCD: definition 1|definition 2|definition 3|...`.
`ABCD` is the acronym itself, followed by a colon and a space. Each definition for that
acronym within that category is separated by `|`.
