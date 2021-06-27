#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --time=24:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=36   # 36 processor core(s) per node 
#SBATCH --gres=gpu:1
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --job-name="GraphAlgsCuda"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --output="runGraphCuda.out"
#SBATCH --mem=370G

module load cuda
cd /work/LAS/jannesar-lab/tbagies/BranchDiv/GraphAlgorithms-master/
nvcc -Xptxas -O3,-v -o graphalgsNUMCuda graphalgsNUMCuda.cu

./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt
./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outCudaRandom.txt

echo "DONE INPUTFILE1024"

./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt
./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outCudaArranged.txt

echo "DONE Arranged"

