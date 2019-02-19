import copy
import queue
class LR:
    def __init__(self):
        self.Vn = []
        self.Vt = []
        self.start = None  # 开始符号
        self.production = []  # 产生式
        self.project = []  # 项目
        self.status = {}  # 存放状态编号及对应的项目集
        self.goto = {}  # 存放goto表  {0:{E:'1',A:'error',B:'error'}}
        self.action = {}  # 存放action表  {0:{a:'S2',b:'S3'}}
    def setVn(self):
        Vn = input('输入非终结符(以空格区分, 回车结束):')
        self.Vn = Vn.split(' ')

    def setVt(self):
        Vt = input('输入终结符(以空格区分, 回车结束):')
        self.Vt = Vt.split(' ')

    def setS(self):
        S = input('输入开始符号(以回车结束):')
        self.start = S

    def setf(self):  # 生成产生式
        n = int(input('输入产生式数目:'))
        print('输入产生式(以回车区分):')
        for i in range(n):
            f = input()
            self.production.append(f)

    def Project(self):  # 建立项目
        for f in self.production:
            temporary = copy.deepcopy(f)  # temporary与f相同
            temporary = temporary.split('->')
            l = temporary[0]  # 产生式左部
            r = list(temporary[1])  # 产生式右部
            for i in range(len(r)+1):  # 对产生式右部处理
                temporary1 = copy.deepcopy(r)
                temporary1.insert(i,'·')
                newf = l+'->'+''.join(temporary1)
                self.project.append(newf)

    def closure(self, pro):  # 求一个项目pro的闭包  E->· E->·b E->b·B  返回列表
        temporary = []  # 最终返回的结果
        temporary.append(pro)  # 将pro自身加入
        l1 = pro.split('->')[0]  # 左部
        r1 = pro.split('->')[1]  # 右部
        x = list(r1)  # 存放右部的列表
        index = x.index('·')  # 得到圆点位置
        if len(x) == 1:  # S->·
            return temporary
        else:
            if index == len(r1)-1 or x[index+1] in self.Vt:  #E->·a
                return temporary
            else:  # E->b·B
                for elem in range(len(self.project)):
                    l = self.project[elem].split('->')[0]  # 左部
                    r = self.project[elem].split('->')[1]  # 右部
                    if l == x[index+1] and r.startswith('·'):  # 继续求B->·r闭包
                        conlist = self.closure(self.project[elem])
                        if len(conlist) == 0:
                            pass
                        else:
                            temporary.extend(conlist)
                return temporary

    def GO(self, project):  # 计算一个项目集的GO(I,x),返回字典形式
        go = {}  # 存放Go(I,x)结果，形式为{a:[],b:[]}
        for elem in project:
            l = elem.split('->')[0]  # 项目左部
            r = elem.split('->')[1]  # 项目右部
            index = list(r).index('·')  # 返回·的位置
            if not r.endswith('·'):   # 不是S->a·形式
                if go.get(list(r)[index+1]) == None:  # 说明x所对应的go中没有项目
                    temporary = list(r)
                    temporary.insert(index+2, '·')
                    temporary.remove('·')   # 将·后移一位
                    x = l+'->'+''.join(temporary)  # 产生一个完整的项目
                    go[list(r)[index+1]] = self.closure(x)  # 将该项目对应的项目集加入x的go中
                else:  # 说明x所对应的go中已有项目
                    temporary = list(r)
                    temporary.insert(index+2,'·')
                    temporary.remove('·')   # 将·后移一位
                    x = l+'->'+''.join(temporary)  # 产生一个完整的项目
                    go[list(r)[index+1]].extend(self.closure(x))
        return go

    def createDFA(self):  # 建立识别活前缀的DFA
        number = 0  # 初始状态编号为0
        first = 'S->·'+self.start  # 初态
        x = self.closure(first)  # 初态闭包
        self.status[number] = x
        qu = queue.Queue()  # 构造队列，用于存放得到的状态
        qu.put({number:self.status[number]})  # 把初始状态加入队列中
        number = number+1
        while not qu.empty():   # 队列不为空，说明状态没有遍历完毕
            temporary = qu.get()  # 队列中取出一个状态
            for k, v in temporary.items():
                y = self.GO(v)  # 求项目集的Go(I,x)
                for key, value in y.items():
                    flag = -1  # 标志位，判断value是否是新的状态
                    for ke, va in self.status.items():
                        if set(va) == set(value):
                            flag = ke  # 状态已存在，返回状态编号
                            break
                    if flag == -1:  # 新的状态，加入状态集中
                        self.status[number] = value
                        qu.put({number:self.status[number]})
                    else:  # 已有状态
                        pass  # 不作处理

    def GOTO(self):  # goto表
        for i in range(len(self.status)):
            self.goto[i] = {}
            temp = self.GO(self.status[i])  # 每个状态的GO
            for vn in self.Vn:   # 对非终结符遍历
                if vn in temp.keys():  # 非终结符存在于状态的Go中
                    for key, value in  self.status.items():
                        if set(value) == set(temp[vn]):
                            number = key  # 记录编号
                            break
                    self.goto[i][vn] = number
                else:
                    self.goto[i][vn] = 'error'

    def ACTION(self):
        vtx = copy.deepcopy(self.Vt)
        vtx.append('#')  # 终结符加‘#’
        for i in range(len(self.status)):
            self.action[i] = {}
            if len(self.status[i]) == 1:  # 项目集只有一个项目
                if self.status[i][0].startswith('S'):  # S->E·
                    for vt in self.Vt:
                        self.action[i][vt] = 'error'
                    self.action[i]['#'] = 'acc'
                else:  #  填写rj的项目  E->aA·
                    temp = self.status[i][0].rstrip('·')  # 删去项目的·  E->aA
                    for n in range(len(self.production)):
                        if self.production[n] == temp:
                            m = n+1   # 产生式在G'中下标从1开始
                            break
                    for vt in vtx:
                        self.action[i][vt] = 'r'+str(m)
            else:  # 填写Sj的项目
                temp = self.GO(self.status[i])  # 字典形式{a:[],b:[]}
                for vt in vtx:
                    if vt in temp.keys():
                        for key, value in self.status.items():  # 确定到哪一个状态
                            if set(value) == set(temp[vt]):
                                number = key  # 返回状态编号
                                break
                        self.action[i][vt] = 'S'+str(number)
                    else:
                        self.action[i][vt] = 'error'
    def output(self):   # 输出LR(0)分析表 表格形式
        print('LR(0)分析表'.center(85))
        print('状态'.center(5), 'ACTION'.center(50), 'GOTO'.center(30))
        print('  '.center(10),end='')
        for vt in self.Vt:  # action
            print(vt.center(10),end='')
        print('#'.center(10),end='')
        for vn in self.Vn:  # goto
            print(vn.center(10),end='')
        print() # 换行
        vtx = copy.deepcopy(self.Vt)
        vtx.append('#')
        for i in range(len(self.status)):  # 输出每一行
            print(str(i).center(10),end='')
            for vt in vtx:
                for key in self.action[i]:  # {0:{'b':'S1'}}
                    if vt == key:
                        print(self.action[i][key].center(10),end='')
                        break
            for vn in self.Vn:
                for key in self.goto[i]:
                    if vn == key:
                        print(str(self.goto[i][key]).center(10),end='')
                        break
            print() # 换行

    def show(self):  # 显示各个状态及对应的项目集
        print('所有状态及对应的项目集:')
        for key, value in self.status.items():
            print(key, value)


if __name__ == '__main__':
	print('E21414020 陈国柱')
    a = LR()
    a.setVn()
    a.setVt()
    a.setS()
    a.setf()
    a.Project()
    a.createDFA()
    a.ACTION()
    a.GOTO()
    a.show()
    a.output()