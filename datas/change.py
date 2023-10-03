import sqlite3
#ftr=2 prs=1 PST=0 BYD=3
# 连接数据库
conn = sqlite3.connect('datas\\st3')
f=open("datas\\playdata.txt","w")
cursor = conn.execute("SELECT songId, songDifficulty, score from scores")
for row in cursor:
	if row[1]==0 : continue	
	if row[1]==1 : continue
	if row[1]==2 : x="FTR"
	if row[1]==3 : x="BYD"
	print("<"+str(row[0])+"> "+"<"+str(x)+"> "+"<"+str(row[2])+">",file=f)
conn.close()
f.close()