#!/bin/bash
cd "$(dirname -- "$(readlink -fn -- "${0}")")"

function clangs { clang -Werror=implicit-function-declaration -Werror=unreachable-code -Werror=sequence-point -Werror=uninitialized -Werror=unused-result -Werror=return-type -Werror=covered-switch-default -Werror=switch-default -Werror=switch-enum -Werror=switch -Wno-incompatible-pointer-types-discards-qualifiers $@; }

clangs main.c -lX11 -lXrender -lXi -lGL -lm ${@}
