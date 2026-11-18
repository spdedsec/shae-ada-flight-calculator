#!/usr/bin/env bash
set -euo pipefail
BIN="./bin/shae-ada-flight-calculator"
PASS=0
FAIL=0
for f in tests/test_trajectory/inputs/*.txt; do
    name="$(basename "$f")"
    read -r v a g < "$f"
    out="$("$BIN" "$v" "$a" "$g" 2>/dev/null)"
    tfl=$(echo "$out" | grep 'Time of flight' | awk '{print $NF}')
    mh=$(echo "$out" | grep 'Max height' | awk '{print $NF}')
    rg=$(echo "$out" | grep 'Horizontal range' | awk '{print $NF}')
    iv=$(echo "$out" | grep 'Impact velocity' | awk '{print $NF}')
    echo "$name: t=$tfl h=$mh r=$rg iv=$iv"
done
echo "Tests complete."