# CLIPSX11

A CLIPS X11 library

## Usage

Run `make` in order to:

1. Download the CLIPS 6.4.2 source code
2. Untar it to the `clips` dir
3. Copy the `userfunctions.c` file into the `clips` dir
4. Run `make` in the `clips` dir

Now you have an executable `clips/clips` file that has X11-related
functions available in it.

## Examples

### clipsmwm Window Manager

There are two files that provide an example window manager
based on [mwm](https://github.com/lslvr/mwm).
The first file `clipsmwm.multifield.clp` takes the output from
X11 functions and returns them as CLIPS Multifields
and asserts implied Facts.
The second file `clipsmwm.fact.clp` asserts them directly as CLIPS Facts.
The `deftemplates.clp` file is necessary if you use the `clipsmwm.fact.clp` file.

#### Display Managers

If you want to install this to your machine, use `sudo make install`
to install a `CLIPSX11` to your `/usr/local/bin` dir.
This will also attempt to install the `clipsmwm.desktop` file
into your `/usr/share/xsessions` dir
as well as the `.clp` and `.bat` files into your `/usr/local/share/CLIPSX11` dir.

#### Via `startx`

Run `sudo make install` and add this to the end of your `.xinitrc`:

```
exec clipsmwm.sh
```

### Misc examples

There are two other files `program.clp` `program2.clp`
showcasing some of the other functions provided by this library.
