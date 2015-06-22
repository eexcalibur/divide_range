import os
import pool
import config

class Scheduler(object):
	"""docstring for Scheduler"""
	def __init__(self):
		self.job_reg = {}

	def run_model(self, work_id, used_res):
		print "work"+str(work_id)+" running on "+str(used_res)
		run_model_str="./run-model.sh CSM_work"+str(work_id)+" "+str(work_id)
		for x in range(len(used_res)):
			run_model_str += " "+used_res[x]
		run_model_str += " &"
		print run_model_str
		os.system(run_model_str)
		self.job_reg[work_id] = used_res

	def check_run_model(self, pool_nodes):
		for k, v in self.job_reg.items():
			cmd_status="ps -ef |grep CSM_work%d| grep -v grep" % k
			run_status=os.popen(cmd_status).readlines()
			if (len(run_status) == 0):
				# release nodes
				pool_nodes.reset_nodes(v)
				# delete job_reg
				del self.job_reg[k]
				pool_nodes.ass_jobs_num = pool_nodes.ass_jobs_num - 1



