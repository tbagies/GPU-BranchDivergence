#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --time=24:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=1   # 36 processor core(s) per node 
#SBATCH --job-name="runGraphCPU"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --mem=370G
#SBATCH --output="rungraphCPU.out"
# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt
./graphalgsCPU inputFile1024.txt < inputFile1024.txt > outCPU.txt

echo "DONE CPU"
