import re


def output(obj):
    import json
    print(json.dumps(obj))


my_dict0 = {}
my_list0 = []
with open("input1.txt", "r") as f:
    my_list0 = re.split('[.!? \n ]', f.read())
for str1 in my_list0:
    if str1 =='':
        continue
    if str1.lower() in my_dict0 :
        my_dict0[str1.lower()] += 1
    else:
        my_dict0[str1.lower()] = 1
output(my_dict0)
