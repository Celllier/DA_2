"""
ILPSolver.py
------------

Solves the generic 0/1 Knapsack problem using Integer Linear Programming (ILP) via the PuLP library
with the default CBC solver.

Input:
    - Truck file (CSV): Contains a single row with the truck's capacity and number of pallets.
    - Pallet file (CSV): Contains pallet information (index, weight, profit).
    - Output file: File to write the selected pallet indices, weights, and profits.

Usage:
    python3 ILPSolver <truck_file> <pallet_file> <output_file> or python ILPSolver <truck_file> <pallet_file> <output_file>

Example:
    python3 ILPSolver.py truck.csv pallets.csv output.txt or python ILPSolver.py truck.csv pallets.csv output.txt
"""

from pulp import LpProblem, LpMaximize, LpVariable, lpSum
import sys
import csv

# --- Read pallet data ---
with open(sys.argv[1], 'r') as f:
    reader = csv.reader(f)
    next(reader)  # skip header
    row = next(reader)
    capacity = int(row[0])
    n = int(row[1])

# Read pallet data: index, weight, profit
weights = []
profits = []

with open(sys.argv[2], 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
            weights.append(int(row['Weight']))
            profits.append(int(row['Profit']))

# --- Setup ILP problem using PuLP ---
model = LpProblem("Knapsack", LpMaximize)

# Binary decision variables: x[i] = 1 if item i is selected
x = [LpVariable(f"x{i}", cat="Binary") for i in range(n)]

# Objective: Maximize total profit
model += lpSum(x[i] * profits[i] for i in range(n))

# Constraint: Total weight must not exceed truck capacity
model += lpSum(x[i] * weights[i] for i in range(n)) <= capacity

# --- Solve the model using CBC ---
model.solve()

# --- Extract results ---
selected_indices = [i for i in range(n) if x[i].varValue > 0.5]
total_profit = sum(profits[i] for i in selected_indices)
total_weight = sum(weights[i] for i in selected_indices)

# --- Write selected pallets to output file ---
with open(sys.argv[3], 'w') as out:
    out.write("index weight value\n")
    for i in selected_indices:
        out.write(f"{i+1} {weights[i]} {profits[i]}\n")

