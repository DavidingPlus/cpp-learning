# with open("test.txt", "r") as f:


# x1是字符串
def getnum(x1):
    t2 = ''
    for i in x1:
        if '0' <= i <= '9':
            t2 = t2+i
    return t2


ls = []
ls2 = []
with open("input.txt ", "r") as f:
    ls = list(f)
for ls1 in ls:
    # ls1是字符串,getnum返回字符串
    if ls1 == '\n':
        break
    ls2.append(getnum(ls1))
with open("output.txt ", "w") as f:
    for l1 in ls2:
        f.write("{0}-{1}".format(l1[:3], l1[3:6]))
        f.write("-{}\n".format(l1[6:9]))