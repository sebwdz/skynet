#!/usr/bin/python

import json
import io

filem = io.open("../data100k/item.json", "r", encoding='ISO-8859-1')
filer = io.open("../data100k/data.json", "r", encoding='ISO-8859-1')

movies = json.loads(filem.read())
rate = json.loads(filer.read())

for key, movie in movies.iteritems():
	print movie["name"].encode('utf8')