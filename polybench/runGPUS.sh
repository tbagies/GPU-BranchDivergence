#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename

#SBATCH --time=20:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=12   # 12 processor core(s) per node 
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --gres=gpu:1
#SBATCH --job-name="testGPU"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

module load cuda

nvcc -o testGPU testGPU.cu -Xptxas -O3,-v

./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt
./testGPU inputFile1024.txt < inputFile1024.txt > outGPURandom.txt

./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
./testGPU ArrangedInput.txt < ArrangedInput.txt > outGPUArranged.txt
