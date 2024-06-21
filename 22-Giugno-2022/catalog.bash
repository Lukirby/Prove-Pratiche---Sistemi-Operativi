if [ $# -eq 0 ]; then
    dir="."
else
    dir="$1"
fi

echo "Scanning $dir"

declare -A file_types
declare -A files

i=0

for file in "$dir"/*
do
    #echo "File: $file"
    if [ -f "$file" ]; then
        output=$(file "$file" | awk -F: '{print $2}' | awk -F, '{print $1}')
        #echo "Output: $output"
        if [ -z "${file_types["$output"]}" ]; then
            file_types["$output"]=$i
            i=$(($i+1))
        fi
        files[$ { file_types["$output"] }]+="$file "
    fi
done

for key in "${!file_types[@]}"
do
    echo "Files of type $key are: ${files[${file_types["$key"]}]} "
done

#for key in "${!file_types[@]}"
#do
#    types+=("$key")
#done
#
#echo "File types in $1 are: ${types[@]}"