# DNA Operations Program

**A C++ program that performs crossover, mutation, and other operations on genetic data using linked lists.**

This project processes chromosome data read from the **Dna.txt** file to perform operations based on genetic algorithms. The program supports crossover, mutation, and automated operations and is designed to handle large files efficiently. All code is compatible with the **MinGW C++ Compiler**.

## Features

- **Crossover**  
  Combines the genes of two chromosomes to create new chromosomes, which are then added to the population.
  
- **Mutation**  
  Applies a mutation to a specified chromosome and gene, transforming the gene into the character "X."

- **Automated Operations**  
  Executes crossover and mutation commands sequentially based on instructions from the `Islemler.txt` file.

- **Print to Screen**  
  Filters and displays chromosomes based on specific rules.

## Requirements

- **MinGW C++ Compiler**
- `Dna.txt` and `Islemler.txt` files:
  - `Dna.txt`: Contains chromosome data.
  - `Islemler.txt`: Contains commands for automated operations.

## Usage

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/bedirhancan/cpp-dna-operations-data-structure.git
   cd cpp-dna-operations-data-structure
   ```

2. Compile and run the program:
   ```bash
   mingw32-make
   ```

3. Select an option from the menu:
   ```bash
   Crossover (1)
   Mutation (2)
   Automated Operations (3)
   Print to Screen (4)
   Exit (5)
   ```

## Author
- Bedirhan CAN
