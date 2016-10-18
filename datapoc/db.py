#!/usr/bin/python

import	psycopg2
import	sys
import	json
import	io

con = None

try:
     
	con = psycopg2.connect(database='pocdata', user='sebastien', password='passpass') 
	cur = con.cursor()

	if sys.argv[2] == "users":

		rq = "DELETE FROM users;"
		cur.execute(rq)

		with io.open(sys.argv[1] + 'user.json', 'r', encoding='ISO-8859-1') as data_file:    
			data = json.load(data_file)

		for k, item in data.items():
			rq = "INSERT INTO users (id, fk_job_id, age, zipcode, gender) VALUES("
			rq += str(item['id']) + ", " + str(item['job']) + ", "
			rq += str(item['age']) + ", "
			rq += "'" + str(item['zipcode']) + "', " + str(bool(item["gender"]))
			rq += ");"
			cur.execute(rq)

	if sys.argv[2] == "movies":
		

		rq = "DELETE FROM movies;"
		cur.execute(rq)

		with io.open(sys.argv[1] + 'item.json', 'r', encoding='ISO-8859-1') as data_file:    
			data = json.load(data_file)

		for k, item in data.items():
			rq = "INSERT INTO movies (id, name, time, category) VALUES("
			rq += str(item['id']) + ", '" + item['name'].replace("'", "") + "', "
			rq += str(item['time']) + ", "
			item.pop('id')
			item.pop('time')
			item.pop('name')
			rq += "'" + json.dumps(item).replace("'", "") + "'"
			rq += ");"
			cur.execute(rq)

	if sys.argv[2] == "opinions":

		rq = "DELETE FROM opinions;"
		cur.execute(rq)
		
		with io.open(sys.argv[1] + 'data.json', 'r', encoding='ISO-8859-1') as data_file:    
			data = json.load(data_file)

		for k, item in data.items():
			rq = "INSERT INTO opinions (id, fk_movie_id, fk_user_id, rate, time) VALUES("
			rq += str(k) + ", '" + str(item['item_id']) + "', " + str(item["user_id"]) + ", "
			rq += str(item["rate"]) + ", " + str(item["time"])
			rq += ");"
			cur.execute(rq)

	if sys.argv[2] == "tests":

		rq = "DELETE FROM opinions_test;"
		cur.execute(rq)
		
		with io.open(sys.argv[1] + 'tests.json', 'r', encoding='ISO-8859-1') as data_file:    
			data = json.load(data_file)

		for k, item in data.items():
			rq = "INSERT INTO opinions_test (id, fk_movie_id, fk_user_id, rate, time) VALUES("
			rq += str(k) + ", '" + str(item['item_id']) + "', " + str(item["user_id"]) + ", "
			rq += str(item["rate"]) + ", " + str(item["time"])
			rq += ");"
			cur.execute(rq)

	if sys.argv[2] == "preferences":
		rq = "DELETE FROM preferences;"
		cur.execute(rq)
		with io.open(sys.argv[1] + 'view.json', 'r', encoding='ISO-8859-1') as data_file:    
			data = json.load(data_file)

		with io.open(sys.argv[1] + 'like.json', 'r', encoding='ISO-8859-1') as data_file:    
			datal = json.load(data_file)

		for k, item in data.items():
			rq = "INSERT INTO preferences (fk_user_id, views, likes) VALUES("
			rq += str(k) + ", '"
			rq += json.dumps(item).replace("'", "") + "','"
			rq += json.dumps(datal[k]).replace("'", "")
			rq += "');"
			print rq
			cur.execute(rq)

	con.commit()

except psycopg2.DatabaseError, e:
    print 'Error %s' % e    
    sys.exit(1)
    
    
finally:
    
    if con:
        con.close()