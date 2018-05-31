def gauss_seidel(m, x0=None, eps=1e-5, max_iteration=3):
    """
    m  : list of list of floats : coefficient matrix
    x0 : list of floats : initial guess
    eps: float : error tolerance
    max_iteration: int

    """
    n = len(m)
    x0 = [0.] * n if x0 is None else x0
    x1 = x0[:]

    for __ in range(max_iteration):
        for i in range(n):
            s = sum(-m[i][j] * x1[j] for j in range(n) if i != j)

            # m[i][n] is b[i]
            x1[i] = (m[i][n] + s) / m[i][i]

        print(x1)
        if all(abs(x1[i] - x0[i]) < eps for i in range(n)):
            return x1
        x0 = x1[:]


def jacobi(m, x0=None, eps=1e-5, max_iteration=3):
    n = len(m)
    x0 = [0.] * n if x0 is None else x0
    x1 = x0[:]

    for __ in range(max_iteration):
        for i in range(n):
            s = sum(-m[i][j] * x0[j] for j in range(n) if i != j)
            x1[i] = (m[i][n] + s) / m[i][i]

        print(x1)
        if all(abs(x1[i] - x0[i]) < eps for i in range(n)):
            return x1
        x0 = x1[:]


m = [[ 2., -1.,  0., 7.],
     [-1.,  2., -1., 1.],
     [ 0., -1.,  2., 1.]]
gauss_seidel(m,max_iteration=5)

print("\n")

n = [[4, 1, 1, 2],
     [1, 5, 2, -6],
     [1, 2, 3, -4]]
x0 =[0.5, -0.5, -0.5]
jacobi(n,x0=x0)
