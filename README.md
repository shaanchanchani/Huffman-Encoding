# Huffman Encoding
This repository contains a C implementation of a widely used file compression technique called Huffman Encoding. It was completed as an assignment for an advanced C computing course at Purdue University.

Given an input text file (containing any character in the ASCII table), this program generates three output files titled 'sorted', 'huffman', and 'header'.

### sorted
Contains all characters that appear in the input file with their respective frequency. Characters are sorted in ascending order by frequency. If two characters have equivalent frequencies, the character with the smaller ASCII value appears first.

### huffman
Contains characters and stream of 0 and 1 corresponding to the Huffman code of the character.

### header
Contains the header information. This is the representation of the encoding binary tree using pre-order traversal.


## Example:
Assuming the input text file contains the string "go go gophers"

`sorted`
```

:1
e:1
h:1
p:1
r:1
s:1
 :2
g:3
o:3
```

`huffman`
```
g:00
o:01
 :100

:1010
e:1011
h:1100
p:1101
r:1110
s:1111
```

`header`
```
,��@�YKE�r��
```
