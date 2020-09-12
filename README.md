`lackey` - curses calendar program
================================

`lackey` is a lightweight terminal based calendar program.

Installation
------------

Create and edit `config.mk` as desired (see `config.mk.example`)

Build and install `lackey`:

```
make
make install
```

Running `lackey`
--------------

Start `lackey` from from a terminal:

```
lackey
```

Structure
---------

Common source files are in the `src/` directory. Each Curses screen has its own
source file in the `views/` directory and each calendar backend has a source file
in the `cals/` directory. The views and calendar backends are accessed though the
`view.c` and `cal.c` files, respectively.
