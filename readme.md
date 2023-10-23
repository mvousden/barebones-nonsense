What's This?
===

A set of joke tools that interact with files written in the Barebones
programming language, as defined in Glenn Brookshear's Computer Science: An
Overview. Almost completely untested. These tools support statements of the
form:

 - `clear X;`, which sets the value of variable `X` to 0.
 - `incr X;`, which increments the value of variable `X`.
 - `decr X;`, which decrements the value of variable `X` if it is greater
   than 0.
 - `copy X to Y;`, which copies the value of variable `Y` to `X`.
 - `while X not 0 do; S end;`, which, for as long as `X` is nonzero, executes
   all statements `S`.
 - `init X = V;`, which sets the value of variable `X` to `V`.

Variable names consist only of characters in `[a-zA-Z0-9_]`.

The tools are:

 - `bb_l.sh`: Takes a barebones file and "executes" it, with optional printing
   output.
 - `bb_c.sh`: As above, but does not support `init`. Variables must be
   `clear`ed before use.
 - `bb.cpp`: A simple C++20 barebones interpreter. Link to lua libraries during
   compilation.

But Why?
---

As presented at Son's Space Cadets event in 2023, which was great fun.
