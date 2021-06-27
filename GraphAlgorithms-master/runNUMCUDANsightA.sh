#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --time=24:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=36   # 36 processor core(s) per node 
#SBATCH --gres=gpu:2
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --job-name="GraphAlgsCudaPrfilerA"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --output="runProfilerA.out"
#SBATCH --mem=370G

module load nsight
nv-nsight-cu-cli --metrics "regex:.*" ./graphalgsNUMCudaProfiler ArrangedInput.txt < ArrangedInput.txt > outAProfiler.txt

echo "DONE Arranged"


