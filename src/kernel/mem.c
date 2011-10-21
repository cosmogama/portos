
unsigned long dataSegmentBaseAddress = 0x40000000L;  // 2 ^ 30
unsigned long segmentSize = 1048576L;								 // 2 ^ 20

unsigned long getDataSegmentBaseAddress(){
	return dataSegmentBaseAddress;
}

unsigned long getDataSegmentSize(){
	return segmentSize;
}
