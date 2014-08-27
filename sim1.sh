#!/bin/bash
for N in {0..9}; do
	mkdir mut-gen-$N
	mkdir paths-$N
	mkdir log-dir-$N
	mkdir fitness-gen-$N
	mkdir gen-$((N+1))
	./dirmut gen-$N mut-gen-$N

	for i in {0..9}; do
		( # need to call a separate node for each part of this loop #	
		sed -e 's/mut-gen-0-seq-0/mut-gen-'$N'-seq-'$i'/g;s/mut-gen-0/mut-gen-'$N'/g' fullN-0.gd > /home/rcf-40/jsschiff/evoSim/paths-$N/fullN-$N-$i.gd;
		# creates the necessary paths so that the phenotype function can run #
		/home/rcf-40/jsschiff/opteron/bin/gcdm_printscore -D -O hes -x input -X dbmrna -H -i 1.0 -s dde21d -a 1e-2 -g n -Z -A Xtr /home/rcf-40/jsschiff/evoSim/paths-$N/fullN-$N-$i.gd ee.202-noann.ini-out-m 2>/dev/null 1> /home/rcf-40/jsschiff/evoSim/log-dir-$N/log-N-$N-$i;
		grep -o 'rms = [0.0-9.0]*' /home/rcf-40/jsschiff/evoSim/log-dir-$N/log-N-$N-$i > /home/rcf-40/jsschiff/evoSim/fitness-gen-$N/fit-gen-$N-seq-$i.txt ) &
	done
	 wait

	./dirp3 fitness-gen-$N mut-gen-$N gen-$((N+1))
done