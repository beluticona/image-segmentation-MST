CC = g++ -g -O3
CCFLAGS = -std=c++11
RM = rm -f

TARGET1 = segmentation_ds_pc
TARGET2 = segmentation_ds_tree
TARGET3 = segmentation_ds_naive

TARGET = segmentation_ds_pc segmentation_ds_tree segmentation_ds_naive
SOURCE1 = segmentation.cpp structs/path-compression-disjoint-set.h
SOURCE2 = segmentation.cpp structs/disjoint-set.h
SOURCE3 = segmentation.cpp structs/naive-disjoint-set.h

all: $(TARGET)

segmentation_ds_pc:
	$(CC) $(CCFLAGS) -o $(TARGET1) $(SOURCE1)

segmentation_ds_tree:
	$(CC) $(CCFLAGS) -o $(TARGET2) $(SOURCE2)

segmentation_ds_naive:
	$(CC) $(CCFLAGS) -o $(TARGET3) $(SOURCE3)

clean:
	$(RM) *.o
	$(RM) $(TARGET)
