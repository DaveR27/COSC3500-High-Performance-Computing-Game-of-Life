#!/bin/bash
#SBATCH --partition=gpu
#SBATCH --gres=gpu:1
#SBATCH --mem=16GB
#SBATCH --cpus-per-task=1

module load cuda gnu/7.2.0 gnutools

make gpu

./main PatternFiles/Frothing_puffer.txt 1000 1000 1000 NoVis
