import math

class Graph():
    def __init__(self, x, y):
        self.rowSums = []
        self.grouped = [0]
        self.sizeX = x
        self.sizeY = y
    #    self.matrix = [
    #  [0, 0, 0, 3, 0, 0, 2, 3, 0],
    #  [0, 0, 2, 0, 2, 0, 0, 0, 0],
    #  [0, 2, 0, 1, 0, 0, 0, 0, 0],
    #  [3, 0, 1, 0, 0, 5, 0, 0, 0],
    #  [0, 2, 0, 0, 0, 2, 0, 0, 4],
    #  [0, 0, 0, 5, 2, 0, 5, 0, 0],
    #  [2, 0, 0, 0, 0, 5, 0, 6, 2],
    #  [3, 0, 0, 0, 0, 0, 6, 0, 0],
    #  [0, 0, 0, 0, 4, 0, 2, 0, 0]
    #]
        self.matrix = [
      [0, 0, 0, 0, 0, 0, 4, 3, 2, 3, 1, 2, 3, 2, 0, 0, 3, 0, 2, 0, 2, 0, 0, 0, 0, 4, 4, 0, 2, 0],
      [0, 0, 0, 4, 0, 0, 0, 2, 3, 0, 0, 3, 0, 2, 3, 0, 0, 0, 2, 3, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0],
      [0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 3, 0, 0, 1, 3, 0, 1, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0],
      [0, 4, 0, 0, 3, 0, 1, 1, 0, 2, 0, 0, 3, 2, 0, 3, 0, 0, 4, 0, 3, 4, 1, 0, 0, 0, 0, 0, 3, 0],
      [0, 0, 0, 3, 0, 2, 4, 4, 0, 0, 0, 4, 2, 0, 1, 0, 2, 4, 3, 0, 2, 0, 0, 1, 0, 0, 2, 0, 3, 0],
      [0, 0, 1, 0, 2, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1, 2, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0],
      [4, 0, 0, 1, 4, 3, 0, 3, 0, 3, 0, 0, 0, 0, 4, 2, 4, 0, 0, 4, 4, 1, 0, 0, 2, 2, 2, 1, 4, 0],
      [3, 2, 0, 1, 4, 0, 3, 0, 0, 0, 2, 4, 0, 0, 0, 1, 0, 0, 0, 0, 2, 2, 4, 4, 0, 1, 0, 0, 4, 1],
      [2, 3, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 4, 3, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0],
      [3, 0, 0, 2, 0, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 4, 2, 0, 4, 0, 0, 0, 0, 0, 1, 0, 4, 0, 3, 0],
      [1, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 4, 3, 4, 0, 4, 1, 0, 0, 0, 3, 3, 2, 4, 0, 0, 3],
      [2, 3, 3, 0, 4, 0, 0, 4, 0, 0, 0, 0, 4, 2, 0, 2, 3, 0, 0, 0, 3, 3, 0, 0, 0, 4, 0, 3, 3, 3],
      [3, 0, 0, 3, 2, 3, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 4, 0, 0, 0],
      [2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 3, 0, 3, 1, 0, 3, 1, 4, 3, 0, 0, 0, 4, 0, 0],
      [0, 3, 1, 0, 1, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 2, 4, 3, 1, 0, 0, 2, 0, 3, 4, 0, 0, 4],
      [0, 0, 3, 3, 0, 3, 2, 1, 1, 4, 3, 2, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 4, 0, 1, 0, 4, 0, 2, 2],
      [3, 0, 0, 0, 2, 0, 4, 0, 4, 2, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 3, 0, 4, 2, 2, 0, 0],
      [0, 0, 1, 0, 4, 0, 0, 0, 3, 0, 0, 0, 0, 3, 2, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 4, 4, 0],
      [2, 2, 0, 4, 3, 1, 0, 0, 1, 4, 4, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 3, 1, 0, 4],
      [0, 3, 0, 0, 0, 2, 4, 0, 0, 0, 1, 0, 2, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 3, 3, 0, 0, 0, 0, 0],
      [2, 0, 0, 3, 2, 0, 4, 2, 0, 0, 0, 3, 0, 3, 1, 0, 2, 2, 0, 1, 0, 0, 0, 2, 3, 1, 0, 1, 0, 0],
      [0, 0, 0, 4, 0, 1, 1, 2, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 0, 0, 4, 0, 3],
      [0, 0, 3, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 1, 0, 2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4],
      [0, 3, 0, 0, 1, 0, 0, 4, 0, 0, 3, 0, 2, 3, 2, 0, 3, 0, 0, 3, 2, 3, 4, 0, 3, 0, 0, 0, 4, 3],
      [0, 2, 0, 0, 0, 0, 2, 0, 2, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0, 3, 3, 4, 0, 3, 0, 4, 0, 3, 4, 3],
      [4, 0, 3, 0, 0, 0, 2, 1, 0, 0, 2, 4, 0, 0, 3, 0, 4, 2, 1, 0, 1, 0, 0, 0, 4, 0, 0, 0, 2, 3],
      [4, 0, 0, 0, 2, 0, 2, 0, 0, 4, 4, 0, 4, 0, 4, 4, 2, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2],
      [0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 3, 0, 4, 0, 0, 2, 4, 1, 0, 1, 4, 0, 0, 3, 0, 0, 0, 0, 1],
      [2, 0, 3, 3, 3, 0, 4, 4, 0, 3, 0, 3, 0, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0, 4, 4, 2, 1, 0, 0, 1],
      [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 3, 0, 0, 4, 2, 0, 0, 4, 0, 0, 3, 4, 3, 3, 3, 2, 1, 1, 0]
    ]
    def sumRowLength(self):
        for i in range(0,len(self.matrix)):
           self.rowSums.append(sum(self.matrix[i]))  

    def summarizeK(self, i):
        sumGrouped = 0
        for val in self.grouped:
            sumGrouped += self.matrix[i][val]
        return 2*sumGrouped - self.rowSums[i]

    def countAllK(self):
        maxK = -math.inf
        k = {};
        indexes = []

        for val in range(0,len(self.matrix)):
            for item in range(0,len(self.matrix[val])):
                if item not in self.grouped:
                    tmpK = self.summarizeK(item)
                    k[item] = tmpK
                    if tmpK > maxK:
                        maxK = tmpK
                  
        for key in k:
            if(k[key] == maxK):
                indexes.append(key)## key or key + 1???
        return indexes
    def calcDistance(self, i, j):
        if self.sizeX > self.sizeY:
            x1 = math.floor(i % self.sizeX)
            y1 = math.floor(i / self.sizeX)
            x2 = math.floor(j % self.sizeX)
            y2 = math.floor(j / self.sizeX)
        else:
            x1 = math.floor(i%self.sizeY)
            y1 = math.floor(i / self.sizeY)
            x2 = math.floor(j % self.sizeY)
            y2 = math.floor(j / self.sizeY)
        return abs(x1-x2) + abs(y1-y2)

    def calcEl(self, el, i):
        l = 1 / self.rowSums[el]
        acc = 0
        for j in range(0, len(self.matrix)):
            secondIndex = self.grouped.index(j)
            if i == secondIndex:
                secondIndex = self.grouped.index(el)
            acc += self.matrix[el][j]*self.calcDistance(i, secondIndex)
        return l*acc

    def grouping(self):
        self.sumRowLength()
        while len(self.grouped) < len(self.matrix):
            #self.printPlata()
            indexes = self.countAllK()
            self.grouped.extend(indexes)

    def findPretenders(self, row):
        sumx = 0
        sumy = 0
        for i in range(0, len(self.matrix[row])):
            elGroupedIndex = self.grouped.index(i)
            sumx += self.matrix[row][i]*math.floor(elGroupedIndex % self.sizeX)
            sumy += self.matrix[row][i]*math.floor(elGroupedIndex / self.sizeX)
        sumx *= 1 / self.rowSums[row]
        sumy *= 1 / self.rowSums[row]
        xf = math.floor(sumx)
        xc = math.ceil(sumx)
        yf = math.floor(sumy)
        yc = math.ceil(sumy)
        pretenders = set()
        pretenders.add(yf * self.sizeX + xf)
        pretenders.add(yf * self.sizeX + xc)
        pretenders.add(yc * self.sizeX + xf)
        pretenders.add(yc * self.sizeX + xc)
        return list(pretenders)

    def calcDeltaL(self, original,  pretender):
        delta = 0
        originalValue = self.grouped[original]
        pretenderValue = self.grouped[pretender]
        delta += self.calcEl(originalValue, original)
        delta += self.calcEl(pretenderValue, pretender)
        delta -= self.calcEl(originalValue, pretender)
        delta -= self.calcEl(pretenderValue, original)
        return delta

    def switchElement(self, selected, replacer):
        print(replacer%self.sizeX, math.floor(replacer/self.sizeY), 'replace', selected%self.sizeX, math.floor(selected/self.sizeY))
        tmp = self.grouped[selected]
        self.grouped[selected] = self.grouped[replacer]
        self.grouped[replacer] = tmp

    def calcQ(self):
        sum = 0
        for i in range(0, len(self.matrix)):
            first = self.grouped.index(i)
            for j in range(0, len(self.matrix[i])):
                second = self.grouped.index(j)
                sum += self.matrix[i][j]* self.calcDistance(first, second)
        print(sum/2)

    def optimaze(self):
        allL = []
        for i in range(0, len(self.grouped)):
            allL.append(self.calcEl(self.grouped[i],i))
        maxL = max(allL)
        selectedIndex = allL.index(maxL)
        pretenders = self.findPretenders(self.grouped[selectedIndex])
        maxDeltaL = - math.inf
        maxDeltaIndex = 0
        for i in range(0, len(pretenders)):
            curDeltaL = self.calcDeltaL(selectedIndex, pretenders[i])
            if curDeltaL > maxDeltaL:
                maxDeltaL = curDeltaL
                maxDeltaIndex = pretenders[i]
        print('maximal delta = ',maxDeltaL)
        if maxDeltaL >= 0.1:
            self.switchElement(selectedIndex, maxDeltaIndex)
            self.calcQ()
            return True
        return False
    def printPlata(self):
        print('plata:')
        tmp = []
        for i in range(0, self.sizeX):
            for j in range(0, self.sizeY):
                if j*self.sizeX + i in self.grouped:
                    tmp.append(self.grouped[j*self.sizeX + i])
                else:
                    tmp.append('-')
            print(tmp)
            tmp = []


def genPlata(dimension):
    plateSizes = []
    for i in range(1, dimension+1):
        for j in range(1, dimension+1):
            if j*i == dimension:
                tmp = [i,j]
                plateSizes.append(tmp)
    return plateSizes


plateSizes = genPlata(30)
for i in plateSizes:
    print('Splitting for [', i[0],',',i[1],']')
    g = Graph(i[0], i[1])
    g.grouping()
   # g.grouped = [0,2,6,3,7,5,1,4,8]
    print('start splitting:')
    #g.printPlata()
    g.calcQ()
    count = 0
    while g.optimaze():
        print(count, 'optimize iteration:')
        #g.printPlata()
        g.calcQ()
        count = count+1
    print('Itog:')
    g.printPlata()
    g.calcQ()
    print('---------------------------------------')
