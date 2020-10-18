#!/bin/bash
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=10
#SBATCH --mem-per-cpu=6G  # memory
#SBATCH --partition=cosc

module load gnu

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./main PatternFiles/Frothing_puffer.txt 10000 10000 10000 NoVis
