#!/bin/bash

/home/rcf-40/jsschiff/opteron/bin/gcdm_printscore -D -O hes -x input -X dbmrna -H -i 1.0 -s dde21d -a 1e-2 -g n -Z -A Xtr fullN-$i.gd ee.202-noann.ini-out-m 2>/dev/null 1> log-dir-0/log-N-$i
