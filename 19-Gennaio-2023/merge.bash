if [[ $# != 2 ]]; then
    echo "Usage: $0 dir1 dir2"
    exit 1
fi

dir1=$1
dir2=$2

#files1=($(find $dir1 | sed "s|^$dir1/||"))
#files2=($(find $dir2 | sed "s|^$dir2/||"))

files1=($(find $dir1 ))
files2=($(find $dir2 ))

echo "Files1: ${files1[@]}"
echo "Files2: ${files2[@]}"

merge="M"

mkdir -p $merge

declare -i bool=0

commonfiles=()
alonefiles=()
commondirs=()
alonedirs=()


for path1 in ${files1[@]}; do
    
    for path2 in ${files2[@]}; do
        if [[ $path1 == $path2 && -d $ ]]; then
            commondirs+=($path1)
        fi
    done
done

for path2 in ${files2[@]}; do
    if [[ $path2 != $dir2 ]]; then
        path2=${path2#$dir2/}
        bool=0
        for path1 in ${files1[@]}; do
            path1=${path1#$dir1/}
            if [[ $path1 == $path2 && $path1 != $dir1 ]]; then
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
    fi
done