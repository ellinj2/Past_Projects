# MutliVerse_Sim

This project takes in a file with information about a "multiverse", including universes, entities in each universe, rewards, and portals to other universes. During the simulation, entities will move based on their personal speeds. If an entity lands on a reward, they collect it and slow down. If two entities collide, they drop their most recent reward, speed up, and reverse direction. If an entity enters a portal, they get moved to the target universe.

## Files

- **Person.py**: Defines Person class which can print information about entities, including position, speed, rewards, name, home universe, and current universe. The Person class can also move an entity and return the entity's score

- **Universe.py**: Defines Universe class which can print information about a universe including name, rewards, and portals

- **hw8.py**: Main file that parses the data file and runs the simulation and prints information whenever something notable happends (e.g. an entity collects a reward, collides, or enters a portal). The simulation ends after 100 iterations, or when all entities have stopped moving and prints information about the entities with the highest end score

- **output0, output1, output2, output3**: Expected results for relative input files

- **Other txt and json files**: Input data files that contain information about the multiverse

