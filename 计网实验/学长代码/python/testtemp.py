i1 = 0
num = 0
two="101"
for j in range(-1, -len(two)-1, -1):
    num = (int(two[j])*(2**i1))+num
    i1 += 1
    print(i1)

print(num)
