
if [[ -z $1 ]]; then
    dir='.'
else
    dir=$1
fi

declare -A file_types
declare -A files
i=0

for file in $(ls $dir); do
    output=$(file $dir/$file | cut -d ',' -f 1 | cut -d ':' -f 2)
    if [[ -z ${file_types["$output"]} ]]; then
        file_types["$output"]=$i
        i=$(($i+1))
    fi
    files[${file_types["$output"]}]+="$file "
done

for key in "${!file_types[@]}"; do
    echo "Files of type $key are:"
    for file in ${files[${file_types["$key"]}]} ; do
        echo $'\t'$file
    done
    echo ""
done
