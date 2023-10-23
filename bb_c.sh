#!/bin/sh
# Call script with $1 as path to your nonsense, $2 as the value to return if
# any. Infinitely extensible, completely untested. POSIX only. Intermediate
# files are for the weak-minded.
set -e
VAR_EXP="[a-zA-Z0-9_]\{1,\}"  # As per Glenn Brookshear
if [ -z "$2" ]; then RETURN=0; else RETURN="$2"; fi  # Told you so
cat "$1" \
    | xargs -0 printf "int main()\n{\n%s\nreturn ${RETURN};\n}\n" \
    | sed -e "s|clear \(${VAR_EXP}\);|unsigned \1 = 0;|g
              s|incr \(${VAR_EXP}\);|\1++;|g
              s|decr \(${VAR_EXP}\);|\1 = \1 == 0 ? 0 : \1 - 1;|g
              s|copy \(${VAR_EXP}\) to \(${VAR_EXP}\);|\2 = \1;|g
              s|while \(${VAR_EXP}\) not 0 do;|while (\1)\n{|g
              s|end;|}|g" \
    | clang -x c -std=c11 - -o bb.out && ./bb.out  # Goes without saying really
rm --force bb.out
