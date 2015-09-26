def sa():
    T = 1.0
    k = 0.0
    x_e = entry_point()
    x = dec.decode(x_e, dec.decode_norm)
    b = ac.ackley(x)
    stat = []
    while True:
        i = 0
        while True:
            i = i + 1 
            z_e = mut.mutate_single(x_e)
            z = dec.decode(z_e, dec.decode_norm)
            n = ac.ackley(z)
            if RM(b, n, ac.ackley, T):
                if i == n2:
                k = k + n2
            if (k % 100 == 0):
                stat.append(b);
            T = a * T
            if k == n1:
                break
            x_e = z_e
            b = n
            break