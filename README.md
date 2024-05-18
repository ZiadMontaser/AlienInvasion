
---

# Alien Invasion Simulation

## Data Structures and Algorithms Project
**Spring 2024**

---

## Table of Contents

- [Introduction](#introduction)
- [Project Objectives](#project-objectives)
- [Project Phases](#project-phases)
- [Battle Rules and Attack Logic](#battle-rules-and-attack-logic)
- [Input/Output File Formats](#inputoutput-file-formats)
- [Program Interface](#program-interface)
- [Team Members](#team-members)

---

## Introduction

The whispers have become shouts, and the blurry figures in the night sky are confirmed spaceships. An alien invasion is no longer science fiction! The world needs to act quickly to prepare for the expected invasion. Using observed information about alien armies, the Global Defense Unit has decided to make the world ready by simulating Earth's power against the aliens' power. 

Your mission is to develop a program that simulates the battle against alien armies and calculates some related statistics to help decision-makers around the world. The future of Earth rests on your code!

---

## Project Objectives

By the end of this project, you should be able to:
- Understand unstructured natural language problem descriptions and derive appropriate designs.
- Intuitively modularize a design into independent components and divide these components among team members.
- Build and use data structures to implement the proposed design.
- Write a complete object-oriented C++ program that performs a non-trivial task.

---

## Project Phases

The project is divided into two main phases:

### Phase 1: Data Structures
- **Phase 1.1 (10%)**: Selecting the appropriate data structures to store different lists in the project. (Deadline: Week 6)
- **Phase 1.2 (30%)**: Implementing and testing the selected data structures to ensure they work as required for Phase 2. (Deadline: Week 9)

### Phase 2: Algorithms and Battle Logic (60%)
- Implementing the algorithms related to the battle fight logic to simulate army battles and generate output files containing statistics about the battle. (Deadline: Week 14)

---

## Battle Rules and Attack Logic

### Army Units
- Earth army units: Soldiers, Tanks, Gunnery
- Alien army units: Soldiers, Monsters, Drones

### Battle Rules
- Any army unit can join the battle at any time.
- At each timestep, Earth units attack alien units, then alien units attack Earth units.
- Units with health <= 0 are dismissed from the battle.
- The battle winner is the army that destroys all units of the other army and has at least one remaining alive unit.

### Attack Logic
- **Earth Soldiers (ES) & Alien Soldiers (AS)**: Attack each other in order of joining the battle.
- **Earth Tanks (ET)**: Attack monsters randomly, prioritize fresh tanks. Can attack alien soldiers if Earth soldiers fall below 30% of alien soldiers.
- **Earth Gunnery (EG)**: Attack monsters and drones, with the highest power and health EG attacking first.
- **Alien Monsters (AM)**: Attack tanks and Earth soldiers randomly.
- **Alien Drones (AD)**: Attack in pairs, targeting tanks and gunnery.

### Unit Random Generator
- Generates units based on parameters from an input file.
- Parameters include the number of units (N), unit distributions (percentages for each type), and thresholds (Thr).
- Units have ranges for health, power, and attack capacity.

---

## Input/Output File Formats

### Input File
- Contains data for unit generation parameters.
- formate:
  ```
  NumOfUnits
  ES EG ET HU
  AS AM AD
  GenProb
  InfectionProb
  AliedArmyThreshold
  EpowerLowwer-EpowerUnpper EhealthLowwer-EhealthUnpper EhealthLowwer-EhealthUnpper
  ApowerLowwer-ApowerUnpper AhealthLowwer-AhealthUnpper AhealthLowwer-AhealthUnpper
  SpowerLowwer-SpowerUnpper ShealthLowwer-ShealthUnpper ShealthLowwer-ShealthUnpper
  ```
- Example:
  ```
  3
  25 25 25 25
  40 40 20
  40
  10
  10
  30-50 20-30 8-12
  35-50 20-30 7-12
  5-20 10-15 2-5

  ```

### Output File
- Contains battle statistics and the details of destructed units.
- Example:
  ```
  Td  ID  Tj  Df  Dd  Db
  99  7   5   15  34  94
  ```

---

## Program Interface

The program can run in two modes:

### Interactive Mode
- Allows the user to monitor the battle step-by-step.
- Displays current timestep, alive units, fighting units, and destructed units.

### Silent Mode
- Produces an output file without printing simulation steps on the console.
- Displays "Silent Mode\nSimulation Starts...\nSimulation ends Output file created".

---

## Team Members
### Members' Info:
| Member Name | GitHub Handle | Email |
|-------------|---------------| ----- |
| Ziad Montaser  | ZiadMontaser    | ziad.mohamed05@eng-st.cu.edu.eg |
| Farouk Mohamed  | faroukmohamed2     | farouk.hussien03@eng-st.cu.edu.eg |
| Mohamed Yaser  | mohamed-yasser23   | mphamed.mostafa04@eng-st.cu.edu.eg |

---

## License

MIT License 

---