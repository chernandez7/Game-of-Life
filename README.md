# Game-of-Life (Open MPI)
High Performance Computing (COMP 364) Final Project built using the [Stampede Supercomputer](https://www.tacc.utexas.edu/stampede/)
[![Build Status](https://travis-ci.org/chernandez7/Game-of-Life.svg?branch=master)](https://travis-ci.org/chernandez7/Game-of-Life)

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
## License ##
 - MIT License
