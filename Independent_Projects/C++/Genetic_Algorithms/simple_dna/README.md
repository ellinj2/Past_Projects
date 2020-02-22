# simple_dna

This program takes in the size of each generation, the probability of a purine base mutating, and the percentage of overall best score that's trying to be reached. It then creates generations of dna sequences, each of which have 20 genomes with 8 purine bases. Each generation, the 5 highest scoring sequences are chosen to breed the next generation with mutation (each genome is restricted to one mutation). Once the percent-score threshhold has been crossed, the program prints how many generations it took to reach the best dna sequence and terminates. 


Usage: executable.exe generation_size(int) mutation_rate(int 0-100) percent_perfection(int 0-100)

## Files

- **classes.hpp**: This file contains the dna and genome classes. The dna class can return its score, access a speficic genome, and print each genome and the overall score of the sequence. The genome class can mutate a purine base, return its score, and return its purine base sequence. Relies on time.h

- **simple_dna.cpp**: The main file for the program. Parses CLAs and runs the evolutionary simulation. Relies on std::list and classes.hpp

