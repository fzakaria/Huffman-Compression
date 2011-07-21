This is the basic huffman encoding algorith.

Steps are:

ENCODING:

1 - Generate ASCII count for input file (rather than use a known count, so it's somewhat adaptive)

2 - Build Huffman Tree to generate unique huffman keys
	2.1 The huffman codes are currently stored as a string! Since the max height for the tree can only be 8 if we are only evaluating ASCII (byte) characters, I should really change it to just be a simple char as well.

3 - Write header for encoded file which enclodes the codes for each ascii value as well as the padding at the end

DECODING:

1 - Read ASCII counts
2- Regenerate Huffman Tree along with codes using same method as in encoding
3- Use BitStream to read each bit and determine code (which again, is used by a string)
4- Lookup code and output appropriate ASCII


Results:

On a 71KB file, it was encoded to a 39KB file, which is a 45% reduction.
