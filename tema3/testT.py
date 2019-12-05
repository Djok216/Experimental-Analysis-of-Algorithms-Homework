from scipy import stats


# Tema 3 resuls
eec3 = [276, 276, 277, 276, 277, 277, 276, 276, 276, 276, 277, 277, 276, 276, 277, 277, 276, 276, 276, 276, 276, 277, 277, 276, 276, 276, 276, 277, 276, 277]
fb3 = [918, 913, 922, 914, 904, 907, 905, 916, 912, 905, 921, 908, 907, 907, 907, 915, 906, 908, 918, 911, 921, 915, 911, 913, 912, 916, 918, 911, 908, 905]
gnu3 = [3482, 3487, 3477, 3476, 3483, 3480, 3478, 3473, 3482, 3478, 3474, 3477, 3476, 3479, 3483, 3474, 3484, 3484, 3473, 3472, 3483, 3478, 3472, 3479, 3479, 3474, 3473, 3477, 3474, 3476]

# Tema 2 results
eec2 = [226, 226, 226, 226, 225, 225, 226, 225, 225, 226, 226, 225, 226, 226, 226, 225, 226, 226, 226, 225, 226, 226, 226, 226, 225, 225, 226, 226, 226, 225]
fb2 = [538, 537, 552, 551, 547, 547, 536, 536, 544, 545, 538, 539, 533, 536, 542, 543, 543, 545, 549, 547, 532, 549, 546, 545, 549, 545, 538, 542, 545, 546]
gnu2 = [1900, 1901, 1898, 1900, 1898, 1901, 1896, 1897, 1900, 1897, 1897, 1900, 1901, 1901, 1901, 1896, 1900, 1900, 1901, 1902, 1899, 1898, 1896, 1898, 1897, 1901, 1900, 1897, 1900, 1897]

# Test t
# null hyp: there are no statistically difference in the means
print(stats.ttest_ind(eec2, eec3))
pval = stats.ttest_ind(eec2, eec3).pvalue
if pval < 0.01:
  print("EEC: Rejected null hyp")
else:
  print("EEC: Accepted Null Hyp")
print(stats.ttest_ind(fb2, fb3))
pval = stats.ttest_ind(fb2, fb3).pvalue
if pval < 0.01:
  print("fb: Rejected null hyp")
else:
  print("fb: Accepted Null Hyp")
print(stats.ttest_ind(gnu2, gnu3))
pval = stats.ttest_ind(gnu2, gnu3).pvalue
if pval < 0.01:
  print("gnu: Rejected null hyp")
else:
  print("gnu: Accepted Null Hyp")

