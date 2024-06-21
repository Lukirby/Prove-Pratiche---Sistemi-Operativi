if [ $# -eq 0 ]; then
    dir="."
else
    dir="$1"
fi

echo "Scanning $dir"

declare -A file_types

for file in "$dir"/*
do
    if [ -f "$file" ]; then
        output=$(file "$file" | awk -F: '{print $2}' | awk -F, '{print $1}')
        file_types["$output"]=1
    fi
done

file_types=(${!file_types[@]})
echo "File types in $1 are: ${file_types[@]}"