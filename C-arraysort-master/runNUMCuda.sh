#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename

#SBATCH --time=20:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=36   # 12 processor core(s) per node 
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --gres=gpu:1
#SBATCH --job-name="SortingGPU"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE
module load cuda
nvcc -o mainNUMCuda mainNUMCuda.cu -Xptxas -O3,-v

./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt
./mainNUMCuda intputFile1024.txt < inputFile1024.txt > outR1024.txt

./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outA1024.txt
