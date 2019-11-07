#coding=utf-8
# -*- coding: utf-8 -*-
import os
import sys
import analysis
import string
reload(sys)
sys.setdefaultencoding('utf-8')

def GetFileList(dir, fileList):
    newDir = dir
    #print(newDir)
    if os.path.isfile(dir):
        #print("file:", dir)
        fileList.append(dir.decode('gbk'))
    elif os.path.isdir(dir):
        for s in os.listdir(dir):
            #print(newDir)
            newDir=os.path.join(dir,s)
            GetFileList(newDir, fileList)
    return fileList

fileList = GetFileList('E:\wechatdocu\WXWork Files\File\\2019-11\d7f7-94f73bc4d61eb1c1761-', [])
iosres = open("iOSres.txt", "w")
androidres = open("android_res.txt", "w")
ioscnt = 0
androidcnt = 0
for filename in fileList:
    reslist  = []
    reslist = analysis.analysisFile(filename, reslist)
    print("handle filename ", filename)
    if filename.find("2019-11-06", int(len(filename)-20), int(len(filename)), ) == -1:
        continue

    filep = None
    if filename.find("iOS") != -1:
        filep = iosres
    else:
        filep = androidres

    #print("i:ssssssssssssss", i)
    if filename.find("iOS") != -1:
        for line in reslist:
            ioscnt = ioscnt + 1
            print("write to ios_res file   :", line)
            filep.write(line)
    else:
        for line in reslist:
            print("write to andorid_res file   :", line)
            androidcnt = androidcnt + 1
            filep.write(line)

iosres.write("总数："+str(ioscnt))
androidres.write("总数："+str(androidcnt))

iosres.close()
androidres.close()