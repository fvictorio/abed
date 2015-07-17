from random import gauss, randrange
from pprint import pprint

def generate_datapoint(f, N):
    result = []
    x = -(N / 2.0)

    for i in xrange(N):
        result.append( (x, f(x)) )
        delta = gauss(1, 0.1)
        if delta < 0: delta = 0
        x += delta

    return result

def generate_dataset(f, Ns):
    result = []

    for N in Ns:
        data_point = generate_datapoint(f, N)
        result.append(data_point)

    return result

def print_dataset(fh, dataset, c):
    for datapoint in dataset:
        fh.write("%i\n" % c)
        for features in datapoint:
            fh.write(' '.join(str(feature) for feature in features))
            fh.write('\n')
        fh.write(";\n")

def generate_file(S, filename):
    fh = open(filename, 'w')
    fh.write("%i %i\n" % (2, 4))

    # Generate dataset for y = x
    Ns = [30 + 2 * randrange(1, 11) for i in xrange(S)]
    dataset = generate_dataset(lambda x: x, Ns)
    print_dataset(fh, dataset, 0)

    # Generate dataset for y = -x
    Ns = [30 + 2 * randrange(1, 11) for i in xrange(S)]
    dataset = generate_dataset(lambda x: -x, Ns)
    print_dataset(fh, dataset, 1)

    # Generate dataset for y = abs(x)
    Ns = [30 + 2 * randrange(1, 11) for i in xrange(S)]
    dataset = generate_dataset(lambda x: abs(x), Ns)
    print_dataset(fh, dataset, 2)

    # Generate dataset for y = -abs(x)
    Ns = [30 + 2 * randrange(1, 11) for i in xrange(S)]
    dataset = generate_dataset(lambda x: -abs(x), Ns)
    print_dataset(fh, dataset, 3)

    fh.close()
