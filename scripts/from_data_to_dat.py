import os


def normalize_nodes(x, y):
  M = dict()
  S = set()
  for i in x + y:
    S.add(i)
  S = sorted(list(S))
  for i, it in enumerate(S):
    M[it] = i
  x = [M[it] for it in x]
  y = [M[it] for it in y]
  return x, y


dataSets = os.listdir('../data')
for dset in dataSets:
  with open('../data/' + dset, 'r') as fInput:
    xEdges, yEdges = [], []
    for line in fInput.readlines():
      x, y = map(int, line.split())
      xEdges.append(x)
      yEdges.append(y)
#    xEdges = xEdges[:100]
#    yEdges = yEdges[:100]
#    xEdges, yEdges = normalize_nodes(xEdges, yEdges)
    print(dset, min(xEdges + yEdges), max(xEdges + yEdges), len(xEdges))
    with open('../dat_files/' + dset + '.dat', 'w') as fOutput:
      fOutput.write("NrNodes = %d;\n" % (max(xEdges + yEdges) + 1))
      fOutput.write("NrEdges = %d;\n" % len(xEdges))
      
      fOutput.write("uEdge = [%s];\n" % ', '.join(map(str, xEdges)));
      fOutput.write("vEdge = [%s];\n" % ', '.join(map(str, yEdges)));

