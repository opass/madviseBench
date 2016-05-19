#!/bin/bash

echo "====== test begin ======"
echo "====== We need sudo permission to clear cache before each testing ======"

bigFile='./bigFile'

sudo bash -c "sync && echo 3 > /proc/sys/vm/drop_caches"
echo "test mmap without madvice"
sleep 1
./madvise $bigFile 0

sudo bash -c "sync && echo 3 > /proc/sys/vm/drop_caches"
echo "test mmap with madvice"
sleep 1
./madvise $bigFile 1

sudo bash -c "sync && echo 3 > /proc/sys/vm/drop_caches"
echo "test mmap without madvice again"
sleep 1
./madvise $bigFile 0

sudo bash -c "sync && echo 3 > /proc/sys/vm/drop_caches"
echo "test mmap with madvice again"
sleep 1
./madvise $bigFile 1

echo "====== test end ======"
