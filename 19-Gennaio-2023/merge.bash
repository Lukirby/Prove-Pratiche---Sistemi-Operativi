if [[ $# != 2 ]]; then
    echo "Usage: $0 dir1 dir2"
    exit 1
fi

dir1=$1
dir2=$2

#files1=($(find $dir1 | sed "s|^$dir1/||"))
#files2=($(find $dir2 | sed "s|^$dir2/||"))

dirlist1=($(find $dir1 -type d))
dirlist2=($(find $dir2 -type d))

echo "dirlist1: ${dirlist1[@]}"
echo "dirlist2: ${dirlist2[@]}"

merge="M"

mkdir -p $merge

declare -i bool=0

files1=($(find $dir1 -type f ))
files2=($(find $dir2 -type f ))

echo "Files1 only Files: ${files1[@]}"
echo "Files2 only Files: ${files2[@]}"

for path1 in "${dirlist1[@]}"; do
    path1=${path1#$dir1/}
    if [[ -d $dir1/$path1 ]]; then
        mkdir -p "$merge/$path1"
    fi    
done

for path2 in "${dirlist2[@]}"; do
    path2=${path2#$dir2/}
    if [[ -d $dir2/$path2 && ! -d "$merge/$path2" ]]; then
        path2=${path2#$dir2/}
        mkdir -p "$merge/$path2"
    fi    
done

for path2 in ${files2[@]}; do
    path2=${path2#$dir2/}
    bool=0
    for path1 in ${files1[@]}; do
            path1=${path1#$dir1/}
            if [[ $path1 == $path2]]; then
                cat $dir1/$path1 $dir2/$path2 > $merge/$path2
                bool=1
                break
            fi
    done
    if [[ $bool == 0 ]]; then
        cp $dir2/$path2 $merge/$path2
    else
        bool=0
    fi
done