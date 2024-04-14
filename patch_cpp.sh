#!/usr/bin/env bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path_to_cpp_file>"
    exit 1
fi

file_path="$1"

if [ ! -f "$file_path" ]; then
    echo "Error: File does not exist."
    exit 1
fi

sed "$(grep -n "^#include" ${file_path} | cut -d ':' -f 1 | tail -n 1) a\\
\\
namespace CIRCUIT_NAME {\\

; /^#include <assert\\.h>\$/ d; s/^assert(/check(/; $ a\\
}\\
" ${file_path}
