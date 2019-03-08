# -*- coding:utf-8 -*-

import sys
import json
dic1 ={}
for m in range(0,52):
	dic1[m] ={}
a = 1000000	
b = 0
for line in sys.stdin:
	b=b+1
	if(b%a == 0):
		print b
        try:
                info=line.strip().split("\t")
        except:
                continue
        i=0;
        for x in info:	
        	if dic1[i].has_key(x):
			dic1[i][x] = dic1[i][x] +1
		else:
			dic1[i][x] = 1;
		i=i+1
for a,b in dic1.items():
	print str(a)+'pos:'
	sorted(b.iteritems(), key=lambda d:d[0], reverse=False)
    	for c,d in b.items():
        	print str(c)+":"+str(d),
	print ""
    	for c,d in b.items():
        	print str(c)+":"+str(float(d)/100000000),
	print ""
	print ""

