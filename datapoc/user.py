#!/usr/bin/python

import	sys
import	json
import	io
import	time
import	datetime

uses = ["Sci-Fi", "Unknown", "Crime", "Romance", "Animation", 
        	"Comedy", "War", "Horror", "Film-Noir", "Western", "Thriller", 
        	"Adventure", "Mystery", "Drama", "Children's", "Action", 
        	"Documentary", "Musical", "Fantasy"]

with open(sys.argv[2] + 'data.json') as data_file:    
    data = json.load(data_file)

with open(sys.argv[2] + 'user.json') as data_file:    
	users = json.load(data_file)

with open(sys.argv[2] + 'item.json') as data_file:    
	movies = json.load(data_file)

views = {}
for k, item in data.items():
	userid = str(item["user_id"])
	if str(item["item_id"]) in movies:
		movie = movies[str(item["item_id"])]
		if userid in views:
			for x in uses:
				if sys.argv[3] == "views":
					views[userid][x] += movie[x]
				else:
					views[userid][x][0] += movie[x] * item["rate"]
					views[userid][x][1] += movie[x]

		else:
			views[userid] = {}
			for x in uses:
				if sys.argv[3] == "views":
					views[userid][x] = float(movie[x])
				else:
					views[userid][x] = [float(item["rate"]), 1]

for k, item in views.items():
	if sys.argv[3] == "views":
		total = 0
		for k2, val in item.items():
			total += val
		for k2, val in item.items():
			item[k2] /= total;
	else:
		for k2, val in item.items():
			item[k2][0] /= item[k2][1]
			item[k2] = item[k2][0]

file = open(sys.argv[1], "w")
file.write(json.dumps(views, indent=4))