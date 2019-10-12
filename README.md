# DCN Simulator

It is a simulator of reconfigurable data center networks. 

## Programming Language

C/C++

## Development Tools

Windows 10 (64-bit) + Visual Studio 2015 + Gurobi Optimizer 7.5.2

## Data Source

http://pages.cs.wisc.edu/~tbenson/IMC10_Data

## Code Structure

- **main.cpp** : entrance function

- **header.h** : set global parameters

- **class.h / class.cpp** : class declaration

- **topology.h / topology.cpp** : calculate and store the wired topology

- **flow.h / flow.cpp** : flow-related functions

- **link.h / link.cpp** : link-related functions

- **SP.h / SP.cpp** : calculate and store the shortest path for rack pairs

- **KSP.h / KSP.cpp** : calculate and store the top-K shortest paths for rack pairs

- **routing.h/ routing.cpp** : implement different routing algorithms

- **schedule.h / schedule.cpp** : simulate flow transferring

- **run.h / run.cpp** : create operating environment for a solution
