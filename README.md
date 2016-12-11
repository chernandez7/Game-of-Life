# Distributed Game-of-Life (Open MPI)
High Performance Computing (COMP 364) Final Project built using the [Stampede Supercomputer](https://www.tacc.utexas.edu/stampede/)

[Benchmarks](https://docs.google.com/spreadsheets/d/1OGbCKby30QSt5MJx5Ypo-xjmV5JAo801PvI-AHHN8lw/edit?usp=sharing)

[Analysis](https://docs.google.com/document/d/1OiDdJ-bC00LqDBlMjEbX12TCCbgaLSe8neyPfz70n00/edit?usp=sharing)

[![Build Status](https://travis-ci.org/chernandez7/Game-of-Life.svg?branch=master)](https://travis-ci.org/chernandez7/Game-of-Life)

---

[Example here](http://i.imgur.com/wfy4iMT.gif)
### Example without visuals ###
![Alt Text](http://i.imgur.com/EABazxM.gif)

## Instructions ##
 - build:

    `make`

 - run:

    `./gameOfLife <gridLength> <gridWidth> <# of generations> --no-print (optional)`

- running with MPI:

    `ibrun -n <number of processing nodes> -o 0 ./gameOfLife <gridLength> <gridWidth> <# of generations> --no-print (optional)`

- running slurm script:

    `sbatch slurm.script`

## Results ##
![Alt Text](https://i.imgur.com/cs6eBEK.png)

![Alt Text](https://i.imgur.com/QSCTBt7.png)

## License ##
 - MIT License
