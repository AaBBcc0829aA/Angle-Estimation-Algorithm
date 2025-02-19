def func_list(a):
    a[0] = 11
    a[-1] = -44
def func_int(a):
    a[0] = 55

x=[1, 2, 3, 4]
print('before', x)
func_list(x)
print('after', x)

x = [5,]
print('before', x)
func_int(x)
print('after', x)
