
if [[ -z $1 ]]; then
    echo "Usage: $0 <dir>"
    exit 1
fi

if [[ ! -d $1 ]]; then
    echo "$1 is not a directory"
    exit 2
fi

declare -A links # Declare associative array

for file in $(find "$1" -type l); do
    realpath=$(readlink -f "$file")
    inode=$(stat -c "%i" "$realpath") # Get inode of the target file
    links["$inode"]=$(( ${links["$inode"]} + 1 )) # Increment count for this inode
done

# Optional: To display the count for each inode
for inode in "${!links[@]}"; do
    if [[ ${links[$inode]} -gt 1 ]]; then
        echo "Inode: $inode, Count: ${links[$inode]}"
    fi
done