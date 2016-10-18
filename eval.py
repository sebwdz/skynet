#!/usr/bin/python

import json
import io
import random

file = io.open("./result.json", "r", encoding='ISO-8859-1')

opinions = json.loads(file.read())

show = float(0)
good = float(0)
wait = float(0)
no = float(0)
error = 0
nball = 0

for k, op in opinions.items():
	total = 0
	total2 = 0
	t = 0
	for i in range(0, len(op)):
		total += ((op[i][1] - 3.0)) if op[i][1] < 3 else op[i][1]
		if op[i][1] > 3.7:
			total2 += 1
		if op[i][1] != 0:
			if op[i][1] < 3.8:
				total2 -= 1
			t += 1
		else:
			total2 += 0.5
	if (t):
		total = (total + total2) / t
		limit = 4
		rate = 3
		rateerr = 3
		op += {total}
		if total > limit:
			show += 1
		if (total > limit and op[0][0] < rateerr):
			error += 1
		if total > limit and op[0][0] > rate:
			good += 1
	if op[0][0] < rateerr:
		no += 1
	nball += 1
	if op[0][0] > rate:
		wait += 1

file = open("./result3.json", "w")
file.write(json.dumps(opinions))

if (show):
	print "result => " + str(good) + " / " + str(wait) + " " + str(good / wait * 100) +  "%"
	print "error => " + str(error) + " / " + str(no) + " " + str(error / no * 100) + " %"
	print "total => " + str(good / show * 100) + " % " + str(error / show * 100) + " %" 
	print "show total => " + str(show) + " " + str(nball) + " " + str(show / nball * 100) + " %"
	print "opinions:"
	print "positiv : " + str(wait / len(opinions.items()) * 100) + " % " + str(good / len(opinions.items()) * 100) + " %"
	print "negative : " + str(no / len(opinions.items()) * 100) + " % " + str(error / float(len(opinions.items())) * 100) + " %"