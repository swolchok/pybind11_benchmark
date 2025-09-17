import timeit

iterations = 5_000_000
pybind_collatz_time = timeit.repeat('collatz(4)', 'from pybind11_benchmark import collatz', number=iterations)
pybind_myint_time = timeit.repeat('x.get()', 'from pybind11_benchmark import MyInt; x = MyInt()', number=iterations)
python_int_time = timeit.repeat('pynoop(4)', 'def pynoop(n): return n', number=iterations)

def ns_per_op(sec_for_all_iterations):
    ns_per_sec = 1_000_000_000
    return sec_for_all_iterations * ns_per_sec / iterations

print(f"pybind collatz time: {ns_per_op(min(pybind_collatz_time)):.3} ns/op")
print(f"pybind MyInt time: {ns_per_op(min(pybind_myint_time)):.3} ns/op")
print(f"python noop int: {ns_per_op(min(python_int_time)):.3} ns/op")
