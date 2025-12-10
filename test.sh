#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

TEST_DIR="test"

# Ensure directory exists
if [[ ! -d "$TEST_DIR" ]]; then
    echo "Error: directory '$TEST_DIR' not found." >&2
    exit 1
fi

for exe in "$TEST_DIR"/*.exe; do
    # Skip when no .exe files exist
    [[ -e "$exe" ]] || { echo "No .exe files found."; exit 0; }

    echo "Running: $exe"
    if ! "$exe"; then
        echo "Execution failed for $exe" >&2
        exit 1
    fi
done

echo "All executables completed successfully."
