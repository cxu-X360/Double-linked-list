#this file compiles all dot_files from appropriate dir to series of png_graphs 
#for using in future

DIR="./dot-files"
PNG_FILE_NAME="./pictures/graph_pict"
i=1

for file in "$DIR"/*; do
    if [ -f "$file" ]; then
        echo "Dot file: $file"
        dot -Tpng "$file" -o "$PNG_FILE_NAME"_"$i".png
        echo PNG file: "$PNG_FILE_NAME"_"$i".png
        echo
        ((i++))
    fi
done