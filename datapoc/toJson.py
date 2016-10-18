#!/usr/bin/python

import	sys
import	json
import	io
import	time
import	datetime

occupation = [
				"administrator", "artist", "doctor", "educator",
				"engineer", "entertainment", "executive", "healthcare",
				"homemaker", "lawyer", "librarian", "marketing", "none",
				"other", "programmer", "retired", "salesman", "scientist",				
				"student", "technician", "writer"
			]

def toJson(file, data, split):
	jsons = {}
	count = 1
	for line in file:
		tmp = {}
		words = line.split("\n")[0].split(split)
		try:
			for it in range(0, len(words)):
				if len(data[it]) > 0:
					if data[it] == "date":
						tmp["time"] = time.mktime(datetime.datetime.strptime(words[it], "%d-%b-%Y").timetuple())
					else:
						tmp[data[it]] = int(words[it]) if words[it].isdigit() else words[it]
			if data[0] == "id":
				id_ = words[0]
			else:
				id_ = count
			count += 1
			jsons[id_] = tmp
		except:
			pass
	return (jsons)

def dataToJson(directorie, t):
	data = ["user_id", "item_id", "rate", "time"]
	file = io.open(directorie + "/1." + t, "r", encoding='ISO-8859-1')
	return (toJson(file, data, "	"))

def userToJson(directorie):
	data = ["id", "age", "gender", "zipcode"]
	file = io.open(directorie + "/u.user", "r", encoding='ISO-8859-1')
	tmp = toJson(file, data, "::")
	for it, v in tmp.items():
		print it
		tmp[it]["gender"] = 0 if (tmp[it]["gender"] == "M") else 1
		tmp[it]["job"] = occupation.index(tmp[it]["job"])
	return (tmp)

def itemToJson(directorie):
	data = ["id", "name", "date", "", "", "Unknown", "Action", "Adventure",
		"Animation", "Children's", "Comedy", "Crime", "Documentary" ,"Drama",
		"Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance",
		"Sci-Fi", "Thriller", "War", "Western"]
	file = io.open(directorie + "/u.item", "r", encoding='ISO-8859-1')
	return (toJson(file, data, "|"))

if sys.argv[2] == "item":
	jsons = itemToJson(sys.argv[1])
elif sys.argv[2] == "user":
	jsons = userToJson(sys.argv[1])
elif sys.argv[2] == "data":
	jsons = dataToJson(sys.argv[1], "base")
elif sys.argv[2] == "test":
	jsons = dataToJson(sys.argv[1], "test")
file = open(sys.argv[3], "w")
file.write(json.dumps(jsons, indent=4));