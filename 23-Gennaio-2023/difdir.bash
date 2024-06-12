if [[ $# != 4 ]]; then
    echo "Usage: $0 dir1 dir2 dir3 dir4"
    exit 1
fi

dir1=$1
dir2=$2
dir3=$3
dir4=$4

echo "Dir1: $dir1"
echo "Dir2: $dir2"
echo "Dir3: $dir3"
echo "Dir4: $dir4"

mkdir -p $dir3
mkdir -p $dir4

files1=($(find $dir1))
files2=($(find $dir2))

for i in "${!files1[@]}"; do
    files1[$i]=$(basename ${files1[$i]})
done

for i in "${!files2[@]}"; do
    files2[$i]=$(basename ${files2[$i]})
done

echo "Files1: ${files1[@]}"
echo "Files2: ${files2[@]}"

for i in "${files1[@]}"; do
    for j in "${files2[@]}"; do
        if [[ "$i" == "$j" ]]; then
            cp $dir1/$i $dir3
            echo copied $dir1/$i to /$dir3
            cp $dir2/$j $dir4
            echo copied $dir2/$j to /$dir4
        fi
    done
done