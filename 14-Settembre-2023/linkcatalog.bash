if [[ -z $1 ]]; then
    echo "Usage: $0 <file>"
    exit 1
fi

declare -A links
declare -A files

for file in $(find "$1" -type l); do
    path=$(readlink -f $file)
    inode=$(stat -c "%i" "$path")
    links[$inode]+="$file "
    files[$inode]=$(basename "$path")
done

for inode in ${!links[@]}; do
    echo "File: ${files[$inode]}"
    echo "Links: ${links[$inode]}"
done