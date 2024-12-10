#!/bin/bash
cd /tmp/data/
mkdir random/
cd random/
dd if=/dev/urandom of=nazwapliku1 bs=10M count=1
dd if=/dev/urandom of=nazwapliku2 bs=10M count=1
dd if=/dev/urandom of=nazwapliku3 bs=10M count=1
dd if=/dev/urandom of=nazwapliku4 bs=10M count=1
dd if=/dev/urandom of=nazwapliku5 bs=10M count=1