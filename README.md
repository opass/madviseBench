madviseBench
============

## Intro
This Project is inspired and modified from [Yutao Liu's note](http://ytliu.info/blog/2014/05/27/note-about-madvice/). We want to verify that system call `madvise` can improve memory access performance.

 

## Usage

$ cd _projectDir_

$ make

it will compile program and generate a 1GB files for memory mapping.

Then run following command to testing

$ ./test.sh


