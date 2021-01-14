# MTM_EX3_TESTS


HELLO DEAR STUDENTS!!!

These are tests for the 3rd hw for MATAM!
to be able to run the tests, i'll provide a few simple steps to ensure that the tests run smoothly on your computer.

First, i'd like to talk about the directory hierarchy:
in a named whatever you like (doesn't really matter), there should be 4 directoeries:

1) part1, which consists of date_wrap.c and date_wrap.h (if you linked the date library from hw1 then all good, if not then be sure to add date.c to your cmake in add_executable)

2) part2: which consists of all the files you used to implement the said part.

3) part3: as said in part2 directory.

4) provided: which has the following files:
                I) the test files I provided in the repository.
                II) the files the segel provided (such as date.h).
                III) 3 directories, for partA, partB and partC, each containing two directories, expected and your_outputs.
                
the test files i provided are named exactly as the test files of the segel, so be sure to overwrite them :)


IMPORTANT!!!
if the directory cmake_build_debug is in your main directory, (which consists of all the directories stated above), you need to change the test files:
in OPEN_FILE and ASSERT macros in each test, you need to change the first ../ in each one.
