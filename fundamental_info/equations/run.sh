#!/usr/bin/env bash
set -euo pipefail

cd -- "$(dirname -- "$0")"
tmp=$(mktemp -d)
exe="$tmp/solve.exe"
trap 'rm -f -- "$exe"; rmdir -- "$tmp"' EXIT

for n in 21 22 23; do
    case "$n" in
        21) equation='tan(x) − tan³(x)/3 + tan⁵(x)/5 − 1/3 = 0' ;;
        22) equation='arccos(x) − √(1 − 0,3x³) = 0' ;;
        23) equation='3x − 4 ln(x) − 5 = 0' ;;
    esac

    gcc "laba4-$n.c" -o "$exe" -lm
    printf '\nУравнение №%s. %s\n' "$n" "$equation"
    output=$("$exe" | tail -n 3)
    mapfile -t results <<< "$output"
    printf 'Дихотомия: %s\nПростые итерации: %s\nНьютон: %s\n' "${results[@]}"
done
