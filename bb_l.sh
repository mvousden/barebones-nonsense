#!/bin/sh
# Call script with $1 as the path to your nonsense, $2 as a lua expression to
# print if you want. Infinitely extensible, slightly tested.
VAR_EXP="[a-zA-Z0-9_]\{1,\}"  # As per Glenn Brookshear
if [ -z "$2" ]; then RETURN=; else RETURN="print($2)"; fi  # Told you so
cat "$1" \
    | xargs -0 printf "%s\n${RETURN}\n" \
    | sed -e "s|clear \(${VAR_EXP}\);|\1 = 0;|g
              s|incr \(${VAR_EXP}\);|\1 = \1 + 1;|g
              s|decr \(${VAR_EXP}\);|if \1 \~= 0 then \1 = \1 - 1 end;|g
              s|copy \(${VAR_EXP}\) to \(${VAR_EXP}\);|\2 = \1;|g
              s|while \(${VAR_EXP}\) not 0 do;|while \1 \~= 0 do|g
              s|init \(${VAR_EXP}\) =|\1 =|g" \
    | lua  # Obviously
