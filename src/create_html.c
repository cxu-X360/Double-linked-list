#include<stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Wrong input format. Try \"create_html num_files directory html_file_path\"\n");
        return -1;
    }

    int num_files = atoi(argv[1]);
    char* directory = argv[2];
    FILE* log_file = fopen(argv[3], "w");
    if (log_file == NULL)
    {
        fprintf(stderr, "Wrong log_file path, try another time...\n");
        return -1;
    }

    printf("dir = <%s>, num_file = [%d], str = <<img src=\"%sgraph_pict_%d.png\" alt=\"List_%d can\'t display\">>\n", directory, num_files, directory, 1, 1);

    fprintf(log_file, "<!DOCTYPE html>\n"
                                     "<html lang=\"en\">\n"
                                     "\t<head> <title> LIST DUMP </title> </head>\n"
                                     "\t<body>\n");

    for (int i = 1; i <= num_files; i++)
    {
        fprintf(log_file, "\t\t<img src=\"%sgraph_pict_%d.png\" alt=\"List_%d can\'t display\">\n", directory, i, i);
    }
    

    fprintf(log_file, "\t</body>\n</html>\n");

    fclose(log_file);
    return 0;

}