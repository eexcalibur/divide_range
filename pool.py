import divide_config

class Pool(object):
	"""docstring for Pool"""
	def __init__(self):
		self.pool_nodes = {}
		self.avail_res = []
		self.ass_jobs_num = 0
		self.total_res = 0
	
	def set_pool(self):
		#input_str = ""
		with open(divide_config.hosts_file) as f:
			input_str = f.read()

		hosts_list = input_str.split('\n')
		
		#remove null element
		while '' in hosts_list:
			hosts_list.remove('')

		for host in hosts_list:
			self.pool_nodes[host] = divide_config.Cores_per_host

		self.total_res = len(self.pool_nodes) * divide_config.Cores_per_host
	
		del hosts_list
		print self.pool_nodes

	def get_avail_nodes(self):
		find_nodes=[]
		find_nodes_num=0
		self.avail_res=[]

		for k,v in self.pool_nodes.items():
			if (v == True):
				find_nodes.append(k)
				find_nodes_num += 1
    			if (find_nodes_num == config.nodes_per_case):
    				self.avail_res = find_nodes
    				for x in range(len(find_nodes)):
    					self.pool_nodes[find_nodes[x]] = False
    				#print self.pool_nodes
    				return True
		return False

	def reset_nodes(self, nodes_list):
		for x in range(len(nodes_list)):
			self.pool_nodes[nodes_list[x]] = True 

