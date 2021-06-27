#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename

#SBATCH --time=20:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=36   # 12 processor core(s) per node 
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --gres=gpu:1
#SBATCH --job-name="EEMBCGPU"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --output="mainGPU.txt" # job standard output file (%j replaced by job id)
#SBATCH --error="mainGPU.txt" # job standard error file (%j replaced by job id)

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt
./mainGPU inputFile1024.txt < inputFile1024.txt > outGPUR.txt

./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
./mainGPU ArrangedInput.txt < ArrangedInput.txt > outGPUA.txt
