class Solution:
    def toHex(self, num: int) -> str:
        #对于大于等于0的转换
        if num >= 0:
            #二进制格式
            bin_format = list(bin(num)[2:])
            lenth = len(bin_format)
            k_4 = lenth // 4
            zero_num = 0
            if lenth % 4 != 0:
                k_4 = lenth // 4 + 1
                zero_num = 4 - lenth % 4
            zero_num_ll_format = ['0'] * zero_num + bin_format
            #处理4位的二进制转化为16进制
            def pending_num(nums):
                s = "0123456789abcdef"
                num = 0
                for i in range(len(nums)):
                    num += int(nums[3 - i]) * (2 ** i) 
                return s[num]
            i = 0
            #结果列表
            result = []
            #循环k_4次
            while i < k_4:
                child_ll = zero_num_ll_format[i * 4 : (i + 1) * 4]
                i += 1
                result.append(pending_num(child_ll))
            return ''.join(result)
        else:
            #负数取反得正
            n_copy = abs(num)
            #二进制格式
            bin_format = list(bin(n_copy)[2:])
            #32位前面补0个数后的格式
            zero_num_ll_format = ['0'] * (32 - len(bin_format)) + bin_format
            #按位取反
            for i in range(len(zero_num_ll_format)):
                if zero_num_ll_format[i] == '0':
                    zero_num_ll_format[i] = '1'
                else:
                    zero_num_ll_format[i] = '0'
            #取反后的格式要+1得到负数补码
            #索引倒序，从后往前， b是进位,初始化为1
            index, b = 31, 1
            while b == 1 and index >= 0:
                #余数
                num = (b + int(zero_num_ll_format[index])) % 2
                #进位
                b = (b + int(zero_num_ll_format[index])) // 2
                if num:
                    zero_num_ll_format[index] = '1'
                else:
                    zero_num_ll_format[index] = '0'
                #索引减1
                index -= 1
            #处理4位的二进制转化为16进制
            def pending_num(nums):
                s = "0123456789abcdef"
                num = 0
                for i in range(len(nums)):
                    num += int(nums[3 - i]) * (2 ** i) 
                return s[num]
            i = 0
            #结果列表
            result = []
            #32位机器的16进制表示一共有8位，循环8次
            while i < 8:
                child_ll = zero_num_ll_format[i * 4 : (i + 1) * 4]
                i += 1
                result.append(pending_num(child_ll))
            return ''.join(result)


#位操作
class Solution2:
    def toHex(self, num: int) -> str:
        #如果是0直接返回"0"
        if num == 0:
            return "0"
        #十六进制字符串
        s = "0123456789abcdef"
        result = []
        #因为是32位机器，所以是8个F
        num = num & 0xFFFFFFFF
        while num > 0:
            #从右至左，每4个bit位进行与操作，得到该十六进制的字符表示
            result.append(s[num & 0XF])
            #每次右移4位
            num = num >> 4
        #结果取反序返回
        return "".join(result[::-1])

