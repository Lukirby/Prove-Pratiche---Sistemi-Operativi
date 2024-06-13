
if [[ -z $1 ]]; then
    dir="."
else
    dir=$1
fi

scripts=$(find $dir -maxdepth 1 -perm -u=x -type f -name -not "*.elf")


echo "I seguenti script sono eseguibili:"
for script in $scripts; do
    echo $script
done

for script in $scripts; do
    ./$script
done