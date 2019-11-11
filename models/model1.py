from gurobipy import *
import os


data = os.listdir('../data/')[1]
print "Data: %s" % data
u, v = [], []
with open('../data/' + data, 'r') as fInput:
  for line in fInput.readlines():
    x, y = map(int, line.split())
    u.append(x)
    v.append(y)

model = Model('MaxIndependentSet')

selected = model.addVars(range(max(u + v) + 1), vtype = GRB.BINARY, name = "selected")
model.addConstrs((selected[u[i]] + selected[v[i]] <= 1 for i in range(len(u))), name = 'independence')
model.addConstrs((selected[i] <= 1 for i in range(max(u + v))), name = 'limit1')
model.setObjective(sum(selected[i] for i in range(max(u + v) + 1)), GRB.MAXIMIZE)
model.optimize()

print "Max Independent Set Size: %d" % int(model.objVal)
