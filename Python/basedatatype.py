

def numberTest():
    print("Type Show")
    numa = 100
    print(type(numa))
    numb = 200
    numc = numa + numb
    if type(numa) is int:
        print("true")
    else:
        print("false")

    ## complex
    ca = complex(10, 10)
    cb = complex(20, 20)
    cc = ca + cb
    print(cc)# 30+30j

def stringTest():
    stra = "HelloWorld"
    print(stra)
    print(stra[0]) #H
    print(stra[0:])  #HelloWorld
    print(stra[0:-1]) #HelloWorl
    print(stra*2)#HelloWorldHelloWorld

    if stra.find("Hello")!= -1:
        print("found Hello in ", stra)

    print("Hello\nworld")
    print(r"Hello\nworld")## 不转义
    ### 左闭右开
    print(stra[-1:-1])## 不打印
    print(stra[-2:-1])## l

def listTest():
    ## 用中括号表示，和字符串类似
    lista = [1,2,3,"Hello"]
    ## 遍历
    for v in lista:
        print("序号:%s 值:%s"%(lista.index(v)+1, v))

    for idx in range(len(lista)):
        print("序号:%s 值：%s"%(idx+1, lista[idx]))

    for idx, val in enumerate(lista):
        print("序号:%s 值：%s"%(idx +1, val))
    print("-----设置遍历开始初始位置，只改变了起始序号")
    for idx, val in enumerate(lista,2):
        print("序号:%s 值：%s"%(idx +1, val))

def tupleTest():
    tuplempty = ()
    ## 构造一个元素，要在后面加上逗号
    tupleOne = (20,)
    print(len(tupleOne))
    ## 和字符串一样进行索引
    
def setTest():
    setEmpty = set()
    seta = ("a", "b")
    if "a" in seta:
        print("a in seta")

    ## 集合运算


def mapTest():
    mapEmpty = {}


if __name__ == '__main__':
    numberTest()
    stringTest()
    ##中括号
    listTest()
    ## 小括号
    tupleTest()
    ##
    setTest()
    mapTest()