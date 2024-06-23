
if [[ -z $1 ]]; then
    dir='.'
else
    dir=$1
fi

declare -A files
i=0

for file in $(find -L "$dir" -type f); do
    output=$(stat -c %i $file)
    if [[ -z ${files["$output"]} ]]; then
        files["$output"]=""
    fi
    files["$output"]+="$file "
done

for file in ${!files[@]}; do
    echo -n "File con inode $file: "
    echo ${files["$file"]}
done
