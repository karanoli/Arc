import sqlite3
#ftr=2 prs=1 PST=0 BYD=3
# 连接数据库
conn = sqlite3.connect('st3')
f=open("datas\\playdata.txt","w")
cursor = conn.execute("SELECT songId, songDifficulty, score from scores")
for row in cursor:
	if row[1]==0 : x="PST"	
	if row[1]==1 : x="PRS"
	if row[1]==2 : x="FTR"
	if row[1]==3 : x="BYD"
	if row[1]==4 : x="ETR"
	print("<"+str(row[0])+"> "+"<"+str(x)+"> "+"<"+str(row[2])+">",file=f)
conn.close()
f.close()