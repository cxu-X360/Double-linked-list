pause()
{
	read -n 1 -s -r -p "${1:-Press any key to continue...}"
	echo
}

clear
gcc main.c src/List_manager.c src/debug_manager.c src/graph_manager.c -o main.out
pause
time ./main.out


cd logs/

echo
echo "Create png starts"
./create_png.sh
echo "Create png ends"

echo
echo "Create html starts"
./create_html.py
echo "Creare html ends"
