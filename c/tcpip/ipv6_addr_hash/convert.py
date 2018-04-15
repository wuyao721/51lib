for line in open('77.txt'):
    b = line.strip().split('.')
    c = '0x%s, 0x%s, 0x%s, 0x%s,' % (b[0], b[1], b[2], b[3])
    print c
