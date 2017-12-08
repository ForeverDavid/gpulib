#!/bin/bash
cd "$(dirname -- "$(readlink -fn -- "${0}")")"

./build_main.sh ${@} && \
./build_libapp.sh ${@}
