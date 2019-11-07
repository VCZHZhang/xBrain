#coding=utf-8
def analysisFile(filename, reslist):
    #reslist = []
    if filename.find(".log") == -1:
        return reslist
    #print("filename:", filename)
    f = open(filename, "r")
    while True:
        line = f.readline()
        if (line.find("超时") != -1) or (line.find(".java:")) != -1:#
            reslist.append(filename + " " + line)
            #reslist.append(line)
            #print("filename:", filename)
            print(line)
        if not line:
            break
    return reslist
def doMain():
    print("do main.")
if __name__ == '__main__':
    doMain()
