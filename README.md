Median Maintenance
===================

About
------------
The goal of this problem is to implement the "Median Maintenance" algorithm. 
The text file contains a list of *n* integers in unsorted order; you should treat 
this as a stream of numbers, arriving one by one. Letting <i>x<sub>i</sub></i> denote the <i>i</i>th number of the file, 
the <i>k</i>th median <i>m<sub>k</sub></i> is defined as the median of the numbers <i>x<sub>1</sub></i>,…,<i>x<sub>k</sub></i>. 
(So, if *k* is odd, then <i>m<sub>k</sub></i> is <i>((k+1)/2)</i>th smallest number among <i>x<sub>1</i>,…,<i>x<sub>k</sub></i>; 
if *k* is even, then <i>m<sub>k</sub></i> is the <i>(k/2)</i>th smallest number among <i>x<sub>1</sub></i>,…,<i>x<sub>k</sub></i>).
That is, you should compute (<i>m<sub>1</sub></i> + <i>m<sub>2</sub></i> + <i>m<sub>3</sub></i> + . . . + <i>m<sub>n</sub></i>)

Running code examples
------------
**C** implementation:

You should compile the source file first.

    cd C/
    gcc -o MedianMaintenance MedianMaintenance.c (Linux)
    ./MedianMaintenance ../in/inputBig.txt (Linux)
    
    compile with Visual Studio | MinGW | DevC++ (Windows)
    MedianMaintenance.exe ../in/inputBig.txt (Windows)

**Java** implementation:

Contains also two JUnit test files for min / max heap structures.

Used java 1.6.0_33, junit 4.10 to compile source files.

    cd Java/
    java MedianMaintenance ../in/inputBig.txt (Windows & Linux)
    java -cp "<path_to_junit_4.x_jar_file>;./" org.junit.runner.JUnitCore MedianMaintenanceTest (Windows)
    java -cp "<path_to_junit_4.x_jar_file>:./" org.junit.runner.JUnitCore MedianMaintenanceTest (Linux)

To compile yourself the source files:

    cd Java/
    javac MinHeap.java MaxHeap.java MedianMaintenance.java (Windows & Linux)
    javac -cp "<path_to_junit_4.x_jar_file>;./" MinHeapTest.java MaxHeapTest.java (Windows)
    javac -cp "<path_to_junit_4.x_jar_file>:./" MinHeapTest.java MaxHeapTest.java (Linux)

For the input files in *in/* folder the expected results are: for *inputBig.txt* the sum should be *46831213*,
for *inputSmall.txt* the sum should be *23*
