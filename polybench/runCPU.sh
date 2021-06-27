#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename

#SBATCH --time=20:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=1   # 1 processor core(s) per node 
#SBATCH --job-name="testCPU"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./testCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt

