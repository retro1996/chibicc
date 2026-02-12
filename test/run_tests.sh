#!/bin/bash
set -eu

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <exe> [exe...]" >&2
  exit 2
fi

if [ -n "${TEST_JOBS:-}" ]; then
  jobs="$TEST_JOBS"
else
  jobs="$(nproc 2>/dev/null || echo 4)"
fi

tmpdir="$(mktemp -d /tmp/chibicc-run-XXXXXX)"
trap 'rm -rf "$tmpdir"' EXIT INT TERM HUP

failfile="$tmpdir/fails"
touch "$failfile"

run_one() {
  exe="$1"
  log="$tmpdir/$(echo "$exe" | tr '/ ' '__').log"
  echo "$exe"
  if ! "$exe" >"$log" 2>&1; then
    echo "$exe" >> "$failfile"
    return 1
  fi
  return 0
}

export -f run_one
export tmpdir failfile

printf '%s\n' "$@" | xargs -P"$jobs" -I{} bash -c 'run_one "$1"' _ {}

if [ -s "$failfile" ]; then
  while IFS= read -r exe; do
    log="$tmpdir/$(echo "$exe" | tr '/ ' '__').log"
    echo "FAILED: $exe" >&2
    [ -f "$log" ] && cat "$log" >&2
    echo >&2
  done < "$failfile"
  exit 1
fi
