#!/usr/bin/fish

clear
dot example.dot -Tpng -o example_graph.png
dot test_graph.dot -Tpng -o test_graph.png
open test_graph.png
