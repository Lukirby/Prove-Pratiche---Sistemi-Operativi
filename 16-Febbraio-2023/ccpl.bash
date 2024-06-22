if [[ -z $1 ]]; then
    echo "Usage: $0 <file>"
    exit 1
fi

if [[ ! -d $1 ]]; then
    echo "Dir $1 not found"
    exit 2
fi

declare -a row_count

for file in $(find "$1" -type f); do
    f=$(cat "$file")
    i=0
    while IFS= read -r line; do
        line_count=$(wc --chars <<< "${line}")
        row_count[$i]=$((row_count[$i] + line_count - 1))
        i=$((i + 1))
    done <<< "$f"
done

for i in "${!row_count[@]}"; do
    echo "Row $i Count: ${row_count[$i]}"
done
