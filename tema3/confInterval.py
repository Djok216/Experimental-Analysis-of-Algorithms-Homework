from scipy.stats import sem, t
from scipy import mean


def getIntervals(data):
  confidence = 0.95
  n = len(data)
  m = mean(data)
  std_err = sem(data)
  h = std_err * t.ppf((1 + confidence) / 2, n - 1)
  start = m - h
  end = m + h
  print("start: ", start, " end: ", end)
  

eec3 = [276, 276, 277, 276, 277, 277, 276, 276, 276, 276, 277, 277, 276, 276, 277, 277, 276, 276, 276, 276, 276, 277, 277, 276, 276, 276, 276, 277, 276, 277]
fb3 = [918, 913, 922, 914, 904, 907, 905, 916, 912, 905, 921, 908, 907, 907, 907, 915, 906, 908, 918, 911, 921, 915, 911, 913, 912, 916, 918, 911, 908, 905]
gnu3 = [3482, 3487, 3477, 3476, 3483, 3480, 3478, 3473, 3482, 3478, 3474, 3477, 3476, 3479, 3483, 3474, 3484, 3484, 3473, 3472, 3483, 3478, 3472, 3479, 3479, 3474, 3473, 3477, 3474, 3476]

getIntervals(eec3)
getIntervals(fb3)
getIntervals(gnu3)