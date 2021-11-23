state = 0b10000001
while True:
    print(state & 1,end = '')
    newbit = (state^(state>>1))&1
    state = (state>>1)| (newbit<<7)
