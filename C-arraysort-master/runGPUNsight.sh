#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename

#SBATCH --time=20:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=12   # 12 processor core(s) per node 
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --gres=gpu:1
#SBATCH --job-name="SortingGPUProf"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

salloc -N 1 -n 36 -t 1:00:00 -p gpu --gres=gpu:2 --mem=350GB -w novagpu001
module load nsight

nv-nsight-cu-cli --metrics "regex:.*" ./mainNUMCuda ArrangedInput.txt < ArrangedInput.txt > outANSight.txt

nv-nsight-cu-cli --metrics "regex:.*" ./mainNUMCuda inputFile1024.txt < inputFile1024.txt > outRNSight.txt

   

