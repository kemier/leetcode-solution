class Solution:
    def integerReplacement(self, n: int) -> int:
        count = 0
        while n != 1:
            # 偶数(0bXX0)直接右移
            if (n & 1) == 0:
                n >>= 1
            else:
                #大于1的奇数格式为XX01或者XX11，对于前一种格式直接-1，对于后一种格式直接+1
                #单且仅当只有两位时候0b01(十进制的1)和0b11（十进制的3）时候，对于3，最少的步数应该是-1，因为3 - 1 = 2 / 2 = 1（三步）                #如果+1的话是3 + 1= 4 /2 =  2 / 2 = 1（四步），造成3这个数字比较特殊的原因是因为3的二进制只有2bit(0b11)
                n += -1 if (n & 2) == 0 or n == 3 else 1  
            count += 1
        return count


