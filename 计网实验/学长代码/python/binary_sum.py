#  传入字符串类型返回int类型的数字（二进制变十进制）
def to_ten(two):
    i1 = 0
    num = 0

    for j in range(-1, -len(two)-1, -1):
        num = (int(two[j])*(2**i1))+num
        i1 += 1
    return num


#  传入int类型的数字返回int类型的数字（十进制变二进制）
def to_two(ten):
    num1 = 0
    while ten != 0:
        num1 = num1 * 10 + ten % 2
        ten = ten // 2
    num1 = str(num1)
    num1 = num1[-1::-1]
    num1 = int(num1)
    return num1


a = input().split()
n = len(a)
sum1 = 0
for i in range(n):
    sum1 = sum1 + to_ten(a[i])
    #  a[i]字符串类型
b = int(to_two(sum1))
print(b)

