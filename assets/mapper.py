import sys, json
js = json.loads(open(sys.argv[1], "r").read())
print ("struct map map1 = {")
print ("\t.h = %d," % js["layers"][0]["height"])
print ("\t.w = %d," % js["layers"][0]["width"])
i = 0
for l in js["layers"]:
	print ("\t.layer%d = {" % i)
	for x in l["data"]:
		sys.stdout.write("%d, "% x)
	print ("\t},")
	i += 1
sys.stdout.write ("\t.tilesets = {\n\t\t")
for t in js["tilesets"]:
	sys.stdout.write("\"%s\", " % t["image"])
print ("\n\t},\n};")

