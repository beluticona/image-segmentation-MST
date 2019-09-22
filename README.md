# image-segmentation-MST
Image segmentation implemented by Kruskal's algorithms in Minimum Spanning Tree. 

## Table of contents
* [General info](#general-info)
* [Setup](#setup)

## General info
Graph-based image segmentation by implementing Kruskal's Algorithm. There are three type of Disjoint-Set Data Structure according to its representation:
- Array of Representatives
- Tree of Representatives applying union-by-rank heuristic.
- Tree of Representatives applying union-by-rank & path-compression heuristics

Presented as part of a project for Algorithms and Data Structures III.
A image is represented by n rows and m columns.
Input:
```
n m
p11 p12...pm
...
pn1 pn2...pnm
```
Output:
```
p11 p12...pm
...
pn1 pn2...pnm
```

## Setup
To run this project, choose a posible representation rep in {segmentation_ds_pc, segmentation_ds_tree, segmentation_ds_naive} and a image in specified format:

```
$ make rep
$ ./rep < sample.in > sample.out
```
