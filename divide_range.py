import divide_config
import numpy
import pool

if __name__ == '__main__':
	#read the init range
	init_range = numpy.loadtxt("divide_init")

	#init comouting res pool
	pool_res = pool.Pool()
	pool_res.set_pool()

	#divide init range by total computing res
	