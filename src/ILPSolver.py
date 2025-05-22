from pulp import LpProblem, LpMaximize, LpVariable, lpSum
import sys
import csv



# Read input from file

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

# Setup LP problem
model = LpProblem("Knapsack", LpMaximize)
x = [LpVariable(f"x{i}", cat="Binary") for i in range(n)]

model += lpSum(x[i] * profits[i] for i in range(n))
model += lpSum(x[i] * weights[i] for i in range(n)) <= capacity

# Solve
model.solve()

selected_indices = [i for i in range(n) if x[i].varValue > 0.5]
total_profit = sum(profits[i] for i in selected_indices)
total_weight = sum(weights[i] for i in selected_indices)

# Write result to output file -- with a system call ---- open(sys.argv[2], 'r') as f
with open(sys.argv[3], 'w') as out:
    out.write("index weight value\n")
    for i in selected_indices:
        out.write(f"{i+1} {weights[i]} {profits[i]}\n")

