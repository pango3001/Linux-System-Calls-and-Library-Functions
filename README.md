# mydu

This exercise deals with the implementation of the Unix application known as du. The command du displays the size of
subdirectories of the tree rooted at the directories/files specified on the command-line arguments. If called with no argument,
the du utility uses the current working directory.

#The solution will be invoked using the following command:\
mydu [-h]\
mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\
-a Write count for all files, not just directories.\
-B M Scale sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\
-b Print size in bytes.\
-c Print a grand total.\
-d N Print the total for a directory only if it is N or fewer levels below the command line argument.\
-h Print a help message or usage, and exit\
-H Human readable; print size in human readable format, for example, 1K, 234M, 2G.\
-L Dereference all symbolic links. By default, you will not dereference symbolic links.\
-m Same as -B 1048576.\
-s Display only a total for each argument.

Known issues:


----GIT LOG----

