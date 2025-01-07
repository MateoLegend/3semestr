#!/bin/bash
cd /tmp/data/
mkdir empty/
cd empty/
dd if=/dev/zero of=nazwapliku1 bs=10M count=1
dd if=/dev/zero of=nazwapliku2 bs=10M count=1
dd if=/dev/zero of=nazwapliku3 bs=10M count=1
dd if=/dev/zero of=nazwapliku4 bs=10M count=1
dd if=/dev/zero of=nazwapliku5 bs=10M count=1