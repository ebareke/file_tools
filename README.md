# file_merger
These scripts can be used to merge multiple files by specified columns &amp; separators

# You can use the python version as follow:
python file_merger.py file1.csv file2.csv file3.csv --key-columns 0 1 2 --separators , ; : --output-file merged.csv

This will create an instance of the FileMerger class using the three files.

# Or compile the C++ code to use the C++ version
g++ -o file_merger file_merger.cpp

# Run the compiled executable
./file_merger file1.csv file2.csv file3.csv --key-columns 0 1 2 --separators , ; : --output-file merged.csv

This will compile the code and create an executable called file_merger. You can then run the executable with the desired arguments: the filenames file1.csv, file2.csv, and file3.csv, the key columns 0, 1, and 2 respectively, and the separators ,, ;, and : respectively. The merged rows will be written to the output file merged.csv.

Note that in this example, the file_merger executable takes the same arguments as the Python script. You can adjust the arguments as needed to suit your specific use case.
