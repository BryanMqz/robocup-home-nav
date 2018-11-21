#!/usr/bin/env python

import rospy
from home_main_sys.srv import *
import time


# @@@@@@@@@@@@@@@@@@@@@@@@

# SERVICE PKG DEFINITION
# 	works struct-like

# int8 debugMode					|
# string newFaceName				| Request params
# string textCommand				|
# ---
# int8 success	(1) TRUE (2) FALSE	|
# string[] facesDetected			| Response params
# int8 actionID						|

# @@@@@@@@@@@@@@@@@@@@@@@@

###################################
# Funcionality is implemented here
###################################

def handle_face_detection_service(request_package):
	# Service has to return a response of the following class only.
	# meaningless values have been used to initialize objt. 
	# Modify only those filds that have a purpose on your service.
	response_package = home_std_srvResponse(1,[],0)
	
	print "Atending a request..."

	"""FUNCTIONALITY GOES HERE"""
	##########################################################################
	time.sleep(5)



	##########################################################################
	
	print "returing now"

	# This handle MUST return a Service Response 
	return response_package

def atomic2_face_detection():
	rospy.init_node('atomic2_face_detection_service_node')
	s = rospy.Service('atomic2_face_detection', home_std_srv, handle_face_detection_service)
	
	print "########################################"
	print "Face Detection Service is up and running."
	print "########################################"
	rospy.spin()

if __name__ == "__main__":
	atomic2_face_detection()