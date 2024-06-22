
if [[ -z "$1" ]]; then
    echo "Usage: $0 <pattern>"
    exit 1
fi

pattern=$1

echo "Pattern: $pattern"

files=()

for file in *; do
    if [[ -f "$file" ]] && grep -q "$pattern" "$file"; then
        files+=("$file")
    fi
done

for file in "${files[@]}"; do
    stat "$file" -c "%y %n"
done | sort -r -n



