

elffiles=()

if [[ -z $1 ]]; then
    elffiles=$(find . -maxdepth 1 -type f -name "*.elf" -exec du -b {} \;)
else 
    for i in $@; do
        echo $i
        elffiles+=$(find $i -maxdepth 1 -type f -name "*.elf" -exec du -b {} \;)
        elffiles+=$'\n'
    done
fi

declare -i sum

for i in ${elffiles[@]}; do
    if [[ $i =~ ^[0-9]+$ ]]; then
        ((sum+=i))
    fi
    
done

echo "File ELF trovati:"
echo "${elffiles[@]}"
echo "Dimensione totale: $sum byte"