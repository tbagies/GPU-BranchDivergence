#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --time=24:00:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=36   # 36 processor core(s) per node 
#SBATCH --gres=gpu:2
#SBATCH --partition=gpu    # gpu node(s)
#SBATCH --job-name="GraphPrfiler"
#SBATCH --mail-user=tbagies@iastate.edu   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --output="ProfilerResults.out"
#SBATCH --mem=370G

module load nsight
nv-nsight-cu-cli --metrics "regex:smsp__thread_inst_executed_per_inst_executed.ratio" ./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outAWE.txt

nv-nsight-cu-cli --metrics "regex:smsp__thread_inst_executed_per_inst_executed.pct" ./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outAWNPE.txt

nv-nsight-cu-cli --metrics "regex:smsp__cycles_active.avg.pct_of_peak_sustained_elapsed" ./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outASE.txt

nv-nsight-cu-cli --metrics "regex:smsp__warp_issue_stalled_long_scoreboard_per_warp_active.pct" ./graphalgsNUMCuda ArrangedInput.txt < ArrangedInput.txt > outAMSD.txt

echo "DONE Arranged"

nv-nsight-cu-cli --metrics "regex:smsp__thread_inst_executed_per_inst_executed.ratio" ./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outRWE.txt
 
nv-nsight-cu-cli --metrics "regex:smsp__thread_inst_executed_per_inst_executed.pct" ./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outRWNPE.txt
 
nv-nsight-cu-cli --metrics "regex:smsp__cycles_active.avg.pct_of_peak_sustained_elapsed" ./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outRSE.txt
 
nv-nsight-cu-cli --metrics "regex:smsp__warp_issue_stalled_long_scoreboard_per_warp_active.pct" ./graphalgsNUMCuda inputFile1024.txt < inputFile1024.txt > outRMSD.txt

echo "DONE INPUTFILE1024"

