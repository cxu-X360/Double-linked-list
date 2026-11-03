pause()
{
	read -n 1 -s -r -p "${1:-Press any key to continue...}"
	echo
}

clear
gcc main.c List_manager.c debug_manager.c graph_manager.c -o main.out
pause
time ./main.out

subl graph.dot
dot -Tpng graph.dot -o graph.png
gwenview ./graph.png
