clear_dir()
{
    DIR="$1"
    echo $DIR
    for file in "$DIR"*; do
		if [ -f "$file" ]; then
            rm $file
		fi
	done
}

clear
clear_dir "logs/pictures/"
clear_dir "logs/dot-files/"
rm logs/*.html