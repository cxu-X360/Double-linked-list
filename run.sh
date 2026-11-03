pause()
{
	read -n 1 -s -r -p "${1:-Press any key to continue...}"
	echo
}

clear
gcc main.c src/List_manager.c src/debug_manager.c src/graph_manager.c -o main.out
pause
time ./main.out
subl logs/graph.dot

dot -Tpng logs/graph.dot -o logs/graph.png
pause
gwenview logs//graph.png
