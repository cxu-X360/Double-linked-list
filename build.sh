pause()
{
	read -n 1 -s -r -p "${1:-Press any key to continue...}"
	echo
}

clear
gcc main.c src/List_manager.c src/debug_manager.c src/graph_manager.c -o main.out -lm
pause
time ./main.out

echo
echo "Create png starts"
	DIR="logs/dot-files/"
	PNG_FILE_NAME="logs/pictures/graph_pict"
	num_files=0

	for file in $(ls "$DIR" -tr); do
		file="$DIR$file"
		if [ -f "$file" ]; then
			((num_files++))
			echo "Dot file: $file"
			dot -Tpng "$file" -o "$PNG_FILE_NAME"_"$num_files".png
			echo PNG file: "$PNG_FILE_NAME"_"$num_files".png
			echo
		fi
	done
echo "Create png ends"

echo
echo "Create html starts, num_files = $num_files"
	gcc src/create_html.c -o create_html.out
	./create_html.out "$num_files" ./pictures/ logs/LOG.html
echo "Create html end"
